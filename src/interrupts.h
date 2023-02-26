
/* ************************************************
 *                INTERRUPTIONS
 **************************************************/

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "routeur.h"

// Devices ID
#define GIC_DEVICE_ID	        	XPAR_PS7_SCUGIC_0_DEVICE_ID
#define GPIO_BUTTON_DEVICE_ID		XPAR_AXI_GPIO_0_DEVICE_ID
#define INTC_DEVICE_ID				XPAR_AXI_INTC_0_DEVICE_ID
#define GPIO_SWITCH_DEVICE_ID		XPAR_AXI_GPIO_1_DEVICE_ID

// Is a pointer to the device instance
XIntc axi_intc;
XGpio gpButton;
XGpio gpSwitch;

// Priorite de IRQs -
#define PL_INTC_IRQ_ID          	XPS_IRQ_INT_ID
#define FIT_IRQ0_ID          		XPAR_AXI_INTC_0_FIT_TIMER_0_INTERRUPT_INTR
#define FIT_IRQ1_ID          		XPAR_AXI_INTC_0_FIT_TIMER_1_INTERRUPT_INTR
#define GPIO_BUTTON_IRQ_ID			XPAR_AXI_INTC_0_AXI_GPIO_0_IP2INTC_IRPT_INTR
#define GPIO_SWITCH_IRQ_ID			XPAR_AXI_INTC_0_AXI_GPIO_1_IP2INTC_IRPT_INTR


#define XGPIO_IR_MASK				0x3 	/* Mask of all bits */

#define GPIO_BUTTONS_CHANNEL 		1
#define GPIO_LEDS_CHANNEL 			2

#define COLOR_DOUBLE_BLUE 			0b100100
#define COLOR_DOUBLE_RED 			0b001001
#define COLOR_DOUBLE_GREEN 			0b010010
#define COLOR_DOUBLE_PURPLE			0b101101
#define COLOR_DOUBLE_YELLOW			0b011011

#define TurnLEDButton(color) XGpio_DiscreteWrite(&gpButton, GPIO_LEDS_CHANNEL, color)
#define TurnLEDSwitch(color) XGpio_DiscreteWrite(&gpSwitch, GPIO_LEDS_CHANNEL, color)

#define BP3 						0b1000		// Bouton pressoir pour le demarrage
#define BP2 						0b0100		// Bouton pressoir pour l arret

#define NO_STAT						0b00		// No stat
#define SWITCH1						0b01		// Stat every 10.000005 sec
#define SWITCH2						0b10		// Stat every 20 sec
#define SWITCH1and2					0b11		// No Stat



/* ************************************************
 *              INTERRUPTION PROTOTYPES
 **************************************************/

void fit_timer_isr0(void *p_int_arg, CPU_INT32U source_cpu);
void fit_timer_isr1(void *p_int_arg, CPU_INT32U source_cpu);

void gpio_isr0(void *p_int_arg, CPU_INT32U source_cpu);
void gpio_isr1(void *p_int_arg, CPU_INT32U source_cpu);

void initialize_gpio0();
void initialize_gpio1();

int initialize_axi_intc();

int connect_fit_timer_irq0();
int connect_fit_timer_irq1();

int connect_gpio_irq0();
int connect_gpio_irq1();

void connect_axi();

void cleanup();

void disconnect_intc_irq();

void disconnect_fit_timer_irq0();
void disconnect_fit_timer_irq1();


#endif /* INTERRUPTS_H */
