
/* ************************************************
 *                INTERRUPTIONS
 **************************************************/

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "routeur.h"


// Devices ID -  À completer
#define GIC_DEVICE_ID	        	XPAR_PS7_SCUGIC_0_DEVICE_ID
#define GPIO_BUTTON_DEVICE_ID		XPAR_AXI_GPIO_0_DEVICE_ID
#define INTC_DEVICE_ID			XPAR_AXI_INTC_0_DEVICE_ID
#define GPIO_BUTTON_DEVICE_ID		XPAR_AXI_GPIO_0_DEVICE_ID

// Is a pointer to the device instance
XIntc axi_intc;
XGpio gpButton;

// Priorité de IRQs - à compléter
#define PL_INTC_IRQ_ID          	XPS_IRQ_INT_ID
#define FIT_IRQ1_ID          		XPAR_AXI_INTC_0_FIT_TIMER_1_INTERRUPT_INTR
#define GPIO_BUTTON_IRQ_ID		XPAR_AXI_INTC_0_AXI_GPIO_1_IP2INTC_IRPT_INTR


#define XGPIO_IR_MASK				0x3 	/**< Mask of all bits */

#define GPIO_BUTTONS_CHANNEL 		1
#define GPIO_LEDS_CHANNEL 			2

#define COLOR_DOUBLE_BLUE 			0b100100
#define COLOR_DOUBLE_RED 			0b001001
#define COLOR_DOUBLE_GREEN 			0b010010
#define COLOR_DOUBLE_PURPLE			0b101101
#define COLOR_DOUBLE_YELLOW			0b011011

#define BUTTON_START				// a compléter
#define BUTTON_STOP					// a compléter 

#define COLOR_SYSTEM_ON				0b1000
#define COLOR_SYSTEM_OFF			0b0100




/* ************************************************
 *              INTERRUPTION PROTOTYPES
 **************************************************/

void fit_timer_isr1(void *p_int_arg, CPU_INT32U source_cpu);
void gpio_isr0(void *p_int_arg, CPU_INT32U source_cpu);
void initialize_gpio0();
int initialize_axi_intc();
int connect_fit_timer_irq1();
int connect_gpio_irq0();
void connect_axi();
void cleanup();
void disconnect_intc_irq();
void disconnect_fit_timer_irq1();

#define TurnLED(color) XGpio_DiscreteWrite(&gpButton, GPIO_LEDS_CHANNEL, color)

#endif /* INTERRUPTS_H */
