                            //***************************************************************************
                            //                          Punoi: Orges Kreka
                            //
                            // Programi: Afishimi i procesve aktive ne menyre nderrendore.
                            //
                            //                       17 / 12 / 2016
                            //
                            //***************************************************************************

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

/**
    Funksioni rekursiv qe kryen bredhjen nderrendore te pemes
    se proceseve...
    @*task procesi aktual qe do afishohet
**/
void DFS( struct task_struct *init_task )
{
    struct task_struct *next_task;/// pointeri qe do te sherbeje si nyje aktuale
    struct list_head *list;



    list_for_each( list, &init_task->children )
    {
        next_task = list_entry( list, struct task_struct, sibling );

        printk( KERN_INFO "Emri: %-20s Gjendja: %-12ld PID: %-12d \n", next_task->comm, next_task->state, next_task->pid );

        DFS( next_task );

    }


}


/// Funksioni qe do te therritet kur moduli te ngarkohet
int simple_init( void )
{
    printk( KERN_INFO "\n\n\t\t\tTEST: Duke ngarkuar proceset. \n\n");

    DFS( &init_task ); /// therritja e funksionit.

    printk( KERN_INFO "\n\n\t\t --- Proceset Mbaruan --- \n");
    return 0;
} ///FUND simple_init


/// Funksioni qe di te therritet kur moduli te hiqet nga kerneli
void simple_exit( void )
{
    printk( KERN_INFO "\n\t\tTEST: Duke hequr modulin. \n" );
}/// FUND simple_exit


module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE( "GPL" );
MODULE_DESCRIPTION( "Iterating over Task with Depth-First Search Tree" );
MODULE_AUTHOR( "ORGES" );



