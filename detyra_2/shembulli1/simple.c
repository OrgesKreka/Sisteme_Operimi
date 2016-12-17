                            //***************************************************************************
                            //                          Punoi: Orges Kreka
                            //
                            // Programi: Ngarkimi i gjithe proceseve aktive si module kerneli.
                            //
                            //                       17 / 12 / 2016
                            //
                            //***************************************************************************


#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>


/**
  *  Funksioni qe do te do te therritet gjate ngarkimit te modulit ne kernel.
  *  Deklaron nje variabel te tipit struct_task.
  *  Duke perdorur funksionin for_each_process afishon emrin, gjendjen dhe pid e cdo procesi.
  *
*/
int simple_init( void )
{
    struct task_struct *task;

    printk( KERN_INFO "\n\n\t\t\tTEST: Duke ngarkuar proceset. \n\n");

    for_each_process( task )
    {
        printk( KERN_INFO "Emri: %-20s Gjendja: %-12ld PID: %-12d \n", task->comm, task->state, task->pid );
    }
    return 0;
} ///FUND simple_init


void simple_exit( void )
{
    printk( KERN_INFO "TEST: Duke hequr modulin. \n" );
}/// FUND simple_exit


module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE( "GPL" );
MODULE_DESCRIPTION( "Afishimi i gjithe taskeve aktive ne konsole" );
MODULE_AUTHOR( "ORGES" );
