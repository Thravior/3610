

// Evenements (masques) lies aux ISRs
#define TASK_RESET_RDY  			0x20	 // Permet le rendez vous unilat�ral entre gpio_isr et TaskReset quand on d�marre le systeme
#define TASK_SHUTDOWN				0x40     // Permet le rendez vous unilat�ral entre gpio_isr et StartupTask quand on arr�te le systeme
#define TASK_STOP_RDY  				0x80	 // Permet le rendez vous unilat�ral entre fittimer et TaskStop apr�s 20 sec
#define TASK_STATS_PRINT			0x100    // Permet le rendez vous unilat�ral entre TaskStop et TaskStats pour imprimer



