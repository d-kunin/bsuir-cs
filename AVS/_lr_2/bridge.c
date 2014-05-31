#include <stdio.h>

void task2(int argc, char * args[]);

void myflush ( FILE *in )
{
  int ch;

  do
    ch = fgetc ( in ); 
  while ( ch != EOF && ch != '\n' ); 

  clearerr ( in );
}

void mypause ( void ) 
{ 
  printf ( "Press [Enter] to continue . . ." );
  fflush ( stdout );
  getchar();
} 

int main(int argc, char * args[])
{
	task2(argc, args);
	myflush(stdin);
	mypause();
}