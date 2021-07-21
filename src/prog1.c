// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>



//shm utility
#include "../lib/shm.h"












/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                            shm.h demonstration program 1

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

    Contact     : ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */












// ---------------- EXECUTION ----------------

//main
int main(){
	//presentation
	printf("Prog1 > This is a basic example of SHM manipulation using \"shm.c/.h\".\n\n");



	//create a new shm segment
	printf("Prog1 > Creating new SHM segment.\n");
	shm* s1 = shm_create(50);

	//shm segment created
	printf("Prog1 > SHM segment created with id [%i].\n", (int)s1->id);
	printf("Prog1 > You can now run Prog2 (./run2) on another terminal.\n");



	//prepare main loop data
	char c;
	int temp;
	char* data;
	printf("\nProg1 > Entering in main loop...\n");
	int stand = 1;

	//main loop
	while(stand){
		printf("\n\n\n\nProg1 > Main-Loop : Please enter 'h' to get some help.\n");
		printf("You > ");
		temp = scanf(" %c", &c);
		switch(c){

			//help menu
			case 'h':
				printf("\nProg1 > Here is some help on available commands in this main loop.\n");
				printf("Prog1 >  - 'h' : Shows this help section.\n");
				printf("Prog1 >  - 'q' : Quit Prog1.\n");
				printf("Prog1 >  - 'r' : Read content of SHM segment.\n");
				printf("Prog1 >  - 'w' : Write in SHM segment.\n\n");
			break;

			//quit
			case 'q':
				stand = 0;
			break;

			//read
			case 'r':
				printf("Prog1 > Reading data from SHM segment...\n");

				data = shm_read(s1);

				printf("Prog1 > SHM segment contains data : \"");
				for(int i=0; i < s1->length; i++)
					printf("%c", data[i]);
				printf("\".\n\n");
			break;

			//write
			case 'w':
				printf("Prog1 > Enter a text to write inside shm (length limit : %u) : ", s1->length);

				data = malloc(s1->length);
				if(data == NULL){
					printf("FATAL ERROR > prog1.c : main() : Computer refuses to give more memory.\n");
					exit(EXIT_FAILURE);
				}
				temp += scanf(" %[^\n]s", data);

				shm_write(s1, data);

				printf("Prog1 > Wrote in SHM segment.\n\n");
				free(data);
			break;
		}
	}



	//free shm segment
	printf("Prog1 > Exited main loop.\n");
	printf("Prog1 > Deleting SHM segment.\n");
	shm_delete(s1);



	return EXIT_SUCCESS;
}
