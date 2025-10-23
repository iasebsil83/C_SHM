// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//shm utility
#include "../lib/shm.h"






/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            shm.h demonstration program 2

        Blablabla about the subject.

    Contact: .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */






// ---------------- EXECUTION ----------------

//main
int main(){

	//presentation
	printf("Prog2 > Be sure to run Prog1 (./run1) before running this one.\n\n");



	//get shm segment id
	printf("Prog2 > Please give the SHM segment id of Prog1 : ");
	int id;
	int temp = scanf(" %i", &id);

	//open SHM segment
	shm* s2 = shm_open(id, 50);

	//shm segment opened
	printf("Prog1 > SHM segment opened.\n");



	//prepare main loop data
	char c;
	char* data;
	printf("\nProg2 > Entering in main loop...\n");
	int stand = 1;

	//main loop
	while(stand){
		printf("\n\n\n\nProg2 > Main-Loop : Please enter 'h' to get some help.\n");
		printf("You > ");
		temp = scanf(" %c", &c);
		switch(c){

			//help menu
			case 'h':
				printf("\nProg2 > Here is some help on available commands in this main loop.\n");
				printf("Prog2 >  - 'h' : Shows this help section.\n");
				printf("Prog2 >  - 'q' : Quit Prog2.\n");
				printf("Prog2 >  - 'r' : Read content of SHM segment.\n");
				printf("Prog2 >  - 'w' : Write in SHM segment.\n\n");
			break;

			//quit
			case 'q':
				stand = 0;
			break;

			//read
			case 'r':
				printf("Prog2 > Reading data from SHM segment...\n");

				data = shm_read(s2);

				printf("Prog2 > SHM segment contains data : \"");
				for(int i=0; i < s2->length; i++)
					printf("%c", data[i]);
				printf("\".\n\n");
			break;

			//write
			case 'w':
				printf("Prog2 > Enter a text to write inside shm (length limit : %u) : ", s2->length);

				data = malloc(s2->length);
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
