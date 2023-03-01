/*
 * router.h
 *
 *  Created on: 26 July 2020
 *      Author: Guy BOIS
 */

#ifndef SRC_ROUTEUR_H_EXT_
#define SRC_ROUTEUR_H_EXT_


#include  <cpu.h>
#include  <lib_mem.h>

#include <os.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include <app_cfg.h>
#include <cpu.h>
#include <ucos_bsp.h>
#include <ucos_int.h>
#include <xparameters.h>
#include <KAL/kal.h>

#include <xil_printf.h>

#include  <stdio.h>
#include  <ucos_bsp.h>

#include <Source/os.h>
#include <os_cfg_app.h>

#include <xgpio.h>
#include <xintc.h>
#include <xil_exception.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define TASK_STK_SIZE 8192

/* ************************************************
 *                TASK PRIOS
 **************************************************/

#define          TaskGeneratePRIO   		15
#define			 TaskStatsPRIO 				12
#define          TaskComputingPRIO  		21
#define          TaskForwardingPRIO 		22
#define          TaskOutputPortPRIO     	20
#define          TaskResetPRIO     			14
#define          TaskStopPRIO     			13

#define			 WAITFORComputing			6


// Routing info.

#define NB_OUTPUT_PORTS 3
#define NB_FIFO 3

#define INT1_LOW      0x00000000
#define INT1_HIGH     0x3FFFFFFF
#define INT2_LOW      0x40000000
#define INT2_HIGH     0x7FFFFFFF
#define INT3_LOW      0x80000000
#define INT3_HIGH     0xBFFFFFFF
#define INT_BC_LOW    0xC0000000
#define INT_BC_HIGH   0xFFFFFFFF

// Reject source info.
#define REJECT_LOW1   0x10000000
#define REJECT_HIGH1  0x17FFFFFF
#define REJECT_LOW2   0x50000000
#define REJECT_HIGH2  0x57FFFFFF
#define REJECT_LOW3   0xD0000000
#define REJECT_HIGH3  0xD7FFFFFF

// Evenements lies aux taches
#define TASK_GENERATE_RDY  		0x01
#define TASK_COMPUTING_RDY  	0x02
#define TASK_FORWARDING_RDY  	0x04
#define TASK_OUTPUTPORT_RDY  	0x08

// Mask
#define TASKS_ROUTER				0x1F     // Permet de demarrer ou stopper toutes les taches au meme moment
#define TASK_RESET_RDY  			0x20	 // Permet le rendez vous unilat�ral entre gpio_isr et TaskReset quand on d�marre le systeme
#define TASK_SHUTDOWN				0x40     // Permet le rendez vous unilat�ral entre gpio_isr et StartupTask quand on arr�te le systeme
#define TASK_STOP_RDY  				0x80	 // Permet le rendez vous unilat�ral entre fittimer et TaskStop apr�s 20 sec
#define TASK_STATS_PRINT			0x100    // Permet le rendez vous unilat�ral entre TaskStop et TaskStats pour imprimer



OS_FLAG_GRP RouterStatus;

OS_SEM	Sem;

typedef struct{
	int id;
	char* name;
} Info_Port;

Info_Port  Port[NB_OUTPUT_PORTS];

typedef struct{
	int id;
	char* name;
} Info_FIFO;

Info_FIFO 	FIFO[NB_FIFO];

typedef enum {
	PACKET_VIDEO,
	PACKET_AUDIO,
	PACKET_AUTRE,
	NB_PACKET_TYPE
} PACKET_TYPE;

typedef struct {
    unsigned int src;
    unsigned int dst;
    PACKET_TYPE type;
    unsigned int data[13];
} Packet;

// Stacks
static CPU_STK TaskGenerateSTK[TASK_STK_SIZE];
static CPU_STK TaskComputingSTK[TASK_STK_SIZE];
static CPU_STK TaskForwardingSTK[NB_FIFO][TASK_STK_SIZE];
static CPU_STK TaskOutputPortSTK[NB_OUTPUT_PORTS][TASK_STK_SIZE];
static CPU_STK TaskStatsSTK[TASK_STK_SIZE];
static CPU_STK TaskResetSTK[TASK_STK_SIZE];
static CPU_STK TaskStopSTK[TASK_STK_SIZE];
static CPU_STK StartupTaskStk[TASK_STK_SIZE];

static OS_TCB TaskGenerateTCB;
static OS_TCB TaskStatsTCB;
static OS_TCB TaskComputingTCB;
static OS_TCB TaskForwardingTCB[NB_FIFO];
static OS_TCB TaskOutputPortTCB[NB_OUTPUT_PORTS];
static OS_TCB TaskResetTCB;
static OS_TCB TaskStopTCB;
static OS_TCB StartupTaskTCB;


/* ************************************************
 *                  Queues
 **************************************************/

OS_Q lowQ;
OS_Q mediumQ;
OS_Q highQ;

/* ************************************************
 *                  Semaphores
 **************************************************/

// Pas de sémaphore pour la partie 1 

/* ************************************************
 *                  Mutexes
 **************************************************/
OS_MUTEX mutRejete;
OS_MUTEX mutPrint;
OS_MUTEX mutAlloc;
OS_MUTEX mutPrint;

/* ************************************************
 *              TASK PROTOTYPES
 **************************************************/

void TaskGenerate(void *data); 
void TaskComputing(void *data);
void TaskForwarding(void *data);
void TaskOutputPort(void *data);
void TaskStats(void* data);
void StartupTask(void *data);

void dispatch_packet (Packet* packet);

void create_application();
int create_tasks();
int create_events();
void err_msg(char* ,uint8_t);
void Suspend_Delay_Resume_All(int nb_sec);

#endif /* SRC_ROUTEUR_H_EXT_ */
