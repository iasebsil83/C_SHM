// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>



//shm utility
#include "shm.h"




















/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            shm.h demonstration program

        Blablabla about the subject.

    DD/MM/YYYY > [V.V.V] :
    - Added something.
    - Added something else.

    DD/MM/YYYY > [V.V.V] :
    - Added something that wasn't before.
    - Fixed a bug.
    - Added something else.
    - Added something else again.

    BUGS : Active bugs in last version.
    NOTES : Notes.

    Contact     : 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




















// ---------------- EXECUTION ----------------

//main
int main(){
	//presentation
	printf("Prog2 > Be sure to run Prog1 before running this one.\n\n");






	//get shm segment id
	printf("Prog2 > Please give the SHM segment id of Prog1 :\n");
	int id;
	int temp = scanf(" %i", &id);

	//open SHM segment
	#define SEGMENT_LENGTH 50
	shm* s2 = shm_open(id, SEGMENT_LENGTH);

	//shm segment opened
	printf("Prog1 > SHM segment opened.\n");



	//prepare main loop data
	char c;
	char* data;
	printf("\nProg2 > Entering in main loop...\n");
	int stand = 1;

	//main loop
	while(stand){
		printf("Prog2 > Main-Loop : Please enter 'h' to get some help.\n");
		printf("You > \n");
		temp = scanf(" %c", &c);
		switch(c){

			//help menu
			case 'h':
				printf("Prog2 > Here is some help on available commands in this main loop.\n");
				printf("Prog2 >  - 'h' : Shows this help section.\n");
				printf("Prog2 >  - 'q' : Quit Prog1.\n");
				printf("Prog2 >  - 'r' : Read content of SHM segment.\n");
				printf("Prog2 >  - 'w' : Write on SHM segment.\n\n");
			break;

			//quit
			case 'q':
				stand = 0;
			break;

			//read
			case 'r':
				printf("Prog2 > Reading data from SHM segment...");

				data = shm_read(s2);

				printf("Prog2 > SHM segment contains data : \"");
				for(int i=0; i < SEGMENT_LENGTH; i++)
					printf("%c", data[i]);
				printf("\".\n\n");
			break;

			//write
			case 'w':
				printf("Prog2 > Enter a text to write inside shm (length limit : %i) : \n", SEGMENT_LENGTH);

				data = malloc(SEGMENT_LENGTH);
				if(data == NULL){
					printf("FATAL ERROR > prog2.c : main() : Computer refuses to give more memory.\n");
					exit(EXIT_FAILURE);
				}
				temp += scanf(" %[^\n]s", data);

				shm_write(s2, data);

				printf("Prog2 > Wrote in SHM segment.\n\n");
				free(data);
			break;
		}
	}



	//close shm segment
	printf("Prog2 > Exited main loop.\n");
	printf("Prog2 > Closing SHM segment.\n");
	shm_close(s2);






	return EXIT_SUCCESS;
}
