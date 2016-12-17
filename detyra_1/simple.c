                            //***************************************************************************
                            //                          Punoi: Orges Kreka
                            //
                            // Programi: Deklarimi i nje liste, bredhja dhe ngarkimi ne kernel.
                            //  
                            //                       19 / 11 / 2016
                            //
                            //***************************************************************************

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h> /// libraria per te perdorur funksionet kmalloc dhe kfree.


/// Deklarimi i struktures
struct ditelindje
{
    int dita;
    int muaji;
    int viti;
    struct list_head list; /// koka e listes
};


static LIST_HEAD( liste_ditelindjesh ); /// variabli liste_ditelindjesh do te jete lista.


/**
  *  Funksioni qe do te do te therritet gjate ngarkimit te modulit ne kernel.
  *  Krijon dhe shton 6 nyje ne liste.
  *  Bredh listen dhe afishon vlerat e cdo nyjeje ne terminal.
  *
*/
int simple_init( void )
{
        printk( KERN_INFO "\t\tTEST: Duke krijuar modulin. \n\n" );



        struct ditelindje *person;

        unsigned int i;

        for( i = 1; i <= 6; i++ )
        {
            person = kmalloc( sizeof(*person), GFP_KERNEL );
            person->dita = i;
            person->muaji = i + 7;
            person->viti = 1995;
            INIT_LIST_HEAD(&person->list );

            list_add_tail( &person->list, &liste_ditelindjesh );
        }


        /// bredhja e listes
        struct ditelindje *ptr;

        unsigned int p = 0;

        list_for_each_entry( ptr, &liste_ditelindjesh, list )
        {
            p++;

            printk( KERN_INFO "Personi %d: ka lindur me  %d : %d : %d \n", p, ptr->dita, ptr->muaji, ptr->viti );
        }
    return 0;
} ///FUND simple_init


/**
  *  Funksioni qe do te do te therritet gjate heqjes se modulit nga kerneli.
  *  Bredh listen dhe afishon vlerat e cdo nyjeje ne terminal.
  *  Fshin cdo nyje nga lista.
  *
*/
void simple_exit( void )
{
    printk( KERN_INFO "\t\tTEST: Duke hequr modulin. \n\n" );

    struct ditelindje *ptr, *pas;

    unsigned int p = 0;

    list_for_each_entry_safe(ptr, pas, &liste_ditelindjesh, list )
    {
        p++;

        printk( KERN_INFO "Duke fshire personin %d\n", p );

        list_del(&ptr->list);

        kfree(ptr);
    }


}/// FUND simple_exit


module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE( "GPL" );
MODULE_DESCRIPTION( "Modul i thjeshte" );
MODULE_AUTHOR( "ORGES" );


