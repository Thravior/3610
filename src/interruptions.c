/*
 *********************************************************************************************************
 *											  Interrupts
 
 *											  
 *********************************************************************************************************
 */
#include "interrupts.h"

#include "routeur.h"

void initialize_gpio0()
{
	if (XST_DEVICE_NOT_FOUND == XGpio_Initialize(&gpButton, GPIO_BUTTON_DEVICE_ID))
		UCOS_Print("Erreur init gpio\n");
	XGpio_SetDataDirection(&gpButton, GPIO_LEDS_CHANNEL, 0x00);      // On indique que le LED est output
	XGpio_SetDataDirection(&gpButton, GPIO_BUTTONS_CHANNEL, 0x01);   // On indique que le BUTTONS  est intput
	XGpio_InterruptGlobalEnable(&gpButton);
	XGpio_InterruptEnable(&gpButton, XGPIO_IR_MASK);
}

int initialize_axi_intc() {
	int status;

	status = XIntc_Initialize(&axi_intc, XPAR_AXI_INTC_0_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	return XST_SUCCESS;
}

int connect_fit_timer_irq1() {
	int status;

	status = XIntc_Connect(&axi_intc, FIT_IRQ1_ID, fit_timer_isr1, NULL);
		if (status != XST_SUCCESS)
			return status;

	XIntc_Enable(&axi_intc, FIT_IRQ1_ID);

	return XST_SUCCESS;
}

int connect_gpio_irq0()
{
	int status = XIntc_Connect(&axi_intc, GPIO_BUTTON_IRQ_ID, gpio_isr0, &gpButton);
	if (status == XST_SUCCESS)
		XIntc_Enable(&axi_intc, GPIO_BUTTON_IRQ_ID);
	return status;
}

void connect_axi() {

	// La connexion est sur IRQ ID#31
	CPU_BOOLEAN succes = UCOS_IntVectSet (PL_INTC_IRQ_ID,
			                             1,
			                             0,
										 (UCOS_INT_FNCT_PTR)XIntc_DeviceInterruptHandler,
										 (void*)(uint32_t)axi_intc.CfgPtr->DeviceId);
	if (succes != DEF_OK)
		UCOS_Print ("connect axi : FAIL \n");
	succes = UCOS_IntSrcEn(PL_INTC_IRQ_ID);
	if (succes != DEF_OK)
		UCOS_Print ("enable axi : FAIL \n");

	connect_gpio_irq();
	connect_fit_timer_irq1();
	XIntc_Start(&axi_intc, XIN_REAL_MODE);


}

void cleanup() {
	/*
	 * Disconnect and disable the interrupt
	 */

	disconnect_intc_irq();
	disconnect_fit_timer_irq1();
}

void disconnect_intc_irq() {
	UCOS_IntSrcDis(PL_INTC_IRQ_ID);
}

void disconnect_fit_timer_irq1() {
	/*
	 * Disconnect and disable the interrupt
	 */
	XIntc_Disable(&axi_intc, FIT_IRQ1_ID);
	XIntc_Disconnect(&axi_intc, FIT_IRQ1_ID);

}


