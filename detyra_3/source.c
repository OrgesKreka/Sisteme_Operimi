
                            //***************************************************************************
                            //                          Punoi: Orges Kreka
                            //
                            // Programi: Llogaritja e faktorialit te vleres se kaluar nga procesi prind
                            //          tek procesi femije, duke perdorur metoden me pipe
                            //
                            //                       2 / 2 / 2017
                            //
                            //***************************************************************************

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg; /// numri qe do te shkruhet ne pipe
	char read_msg; /// numri qe do te lexohet ne pipe

	pid_t pid; /// femija

	int fd_numrit[ 2 ]; /// pipa ku do te shkruhet dhe lexohet numri
	int fd_faktorialit[ 2 ]; /// pipa ku do te shkruhet dhe lexohet faktoriali
    int fakt;/// faktoriali qe do te lexohet nga pipa fd_faktorialit

	///Krijimi i pipes se pare( shkrim, lexim te numrit )
	if (pipe( fd_numrit ) == -1)
	{
		fprintf(stderr,"Pipa e numrit deshtoi te krijohet!");
		return 1;
	}

    ///Krijimi i pipes se dyte( shkrim, lexim te faktorialit )
	if( pipe( fd_faktorialit ) == -1 )
	{
        fprintf(stderr,"Pipa e faktorialit deshtoi te krijohet!");
		return 1;
	}

	///Krijimi i procesit femije
	pid = fork();

    ///Nese procesi nuk mund te krijohet
	if (pid < 0)
	{
		fprintf(stderr, "Nuk mund te krijohet fork!");
		return 1;
	}

	if (pid > 0)
	{
        ///Procesi prind
        /// Mbyll anen e leximit te pipes
		close(fd_numrit[ READ_END ]);

        int vlera;

        ///Lexoj nje numer pozitiv
        do
        {
            printf( "\nPrindi: Jep numrin qe do ti gjesh faktorialin tek procesi bir( numri > 0 ): "  );
            scanf( "%d", &vlera );
        }
        while( vlera <= 0 );

        ///Konvertoj numrin ne karakter char
        write_msg = vlera + '0';

		///Shkruan numrin ne pipe
		write(fd_numrit[ WRITE_END ], &write_msg, sizeof( write_msg ));

		///Mbyll anen per shkrim te pipes
		close(fd_numrit[ WRITE_END ]);


        ///Mbyll anen per shkrim te pipes se faktorialit
        ///Pasi vetem do te lexoj ne te
		close( fd_faktorialit[ WRITE_END ] );

        ///Lexoj faktorialin e llogaritur
        read(fd_faktorialit[ READ_END ], &fakt, sizeof( int )  );


        printf( "Prindi: Faktoriali i %c eshte %d.\n", write_msg, fakt );

        close( fd_faktorialit[ READ_END ]);

	}
	else ///Procesi femije
	{
		///Mbyll anen e shkrimit te pipes1
		close(fd_numrit[ WRITE_END ] );

		///Lexoj nga pipa1
		read(fd_numrit[ READ_END ], &read_msg, sizeof( char ) );

        ///E konvertoj numrin e lexuar nga karakter ne int
        int numri = read_msg - '0';

        int faktoriali = 1;
        int i;
        ///Llogaris faktorialin
        for( i = 1; i <= numri; i++ )
            faktoriali *= i;

        printf( "\n\nFemija: Faktoriali u llogarit!" );

		close(fd_numrit[ READ_END ]);


        ///Shkruaj ne pipen2 vleren e llogaritur
		close( fd_faktorialit[ READ_END ] );
            write( fd_faktorialit[ WRITE_END ], &faktoriali, sizeof( int ) );
		close( fd_faktorialit[ WRITE_END ] );
	}

	return 0;
}
