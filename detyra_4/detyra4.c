
                            //***************************************************************************
                            //                          Punoi: Orges Kreka
                            //
                            // Programi: Gjetja e shumes, numrit te elementeve cift dhe tek te nje matrice
                            //           duke perdorur tre thread-e per te kryer secilin veprim
                            //
                            //                       14 / 4 / 2017
                            //
                            //***************************************************************************

#include <pthread.h>
#include <stdio.h>

#define RRESHTA 3
#define KOLONA  2

int shuma_matrices;
int nr_elementeve_tek;
int nr_elementeve_cift;




///Funksioni qe do te gjej shumen e elementeve te matrices
///@param matrica - pointeri tek matrica
void *gjejShumen( void *matrica )
{	
	int (*array)[ RRESHTA ][ KOLONA ] = matrica; ///konvertimi i pointerit ne nje vektor 2-d i tipit int

	 shuma_matrices = 0;
	 int i, j;

	for( i = 0; i < RRESHTA; i++ )
	{
		for( j = 0; j < KOLONA; j++ )
		{
			shuma_matrices += (*array)[ i ][ j ];
		}
	}

	pthread_exit( 0 );
}///FUND gjejShumen


///Funksioni qe numeron elementet tek te matrices
///@param matrica 
void *numriElementeveTek( void *matrica )
{
	int( *array )[ RRESHTA ][ KOLONA ] = matrica;

	nr_elementeve_tek = 0;

	int i, j;

	for(  i = 0; i < RRESHTA; i++ )
	{
		for( j = 0; j < KOLONA; j++ )
		{
			if( ( *array )[ i ][ j ] % 2  != 0  )
			{
				nr_elementeve_tek += 1;
			}///FUND if
		} ///FUND for2
	}///FUND for1

	pthread_exit( 0 );

} ///FUND numriElementeveTek


///Funksioni qe numeron elementet cift te matrices
///@param matrica 
void *numriElementeveCift( void *matrica )
{
	int( *array )[ RRESHTA ][ KOLONA ] = matrica;

	nr_elementeve_cift = 0;

	int i, j;

	for(  i = 0; i < RRESHTA; i++ )
	{
		for( j = 0; j < KOLONA; j++ )
		{
			if( ( *array )[ i ][ j ] % 2  == 0  )
			{
				nr_elementeve_cift += 1;
			}///FUND if
		} ///FUND for 2 
	} ///FUND for 1 

	pthread_exit( 0 );

} ///FUND numriElementeveCift



int main()
{	
	///Matrica me vlera statike
	int Matrice[ RRESHTA ][ KOLONA ] ={{1,2},{3, 4}, {1, 1}};

	///Deklarimi i thread-it te pare
	pthread_t id_1;
	pthread_attr_t attr_1;


	///Deklarimi i thread-it te dyte
	pthread_t id_2;
	pthread_attr_t attr_2;


	///Deklarimi i thread-it te trete
	pthread_t id_3;
	pthread_attr_t attr_3;


	///Thread-i i pare
	pthread_attr_init( &attr_1 );
	pthread_create( &id_1, &attr_1, gjejShumen, Matrice );
	pthread_join( id_1, NULL );

	///Thread-i  i dyte
	pthread_attr_init( &attr_2 );
	pthread_create( &id_2, &attr_2, numriElementeveTek, Matrice );
	pthread_join( id_2, NULL );


	///Thread-i i trete
	pthread_attr_init( &attr_3 );
	pthread_create( &id_3, &attr_3, numriElementeveCift, Matrice );
	pthread_join( id_3, NULL );

	printf( "Shuma = %d \n", shuma_matrices );
	printf( "Numri i elementeve tek = %d \n", nr_elementeve_tek );
	printf( "Numri i elementeve cift = %d \n\n", nr_elementeve_cift );
}