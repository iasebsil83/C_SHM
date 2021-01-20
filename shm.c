// -------------------------------- IMPORTATIONS --------------------------------

//standard
#include <stdio.h>
#include <stdlib.h>



//shared memory
#include <sys/shm.h>
#include <sys/stat.h>



//own header
#include "shm.h"




















/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SHM [0.1.1] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                 SHM by I.A.

        SHM is just an utility program that allows you to manipulate
    linux shared memory a little bit more simply than sys/shm.h does.

    This program adds 6 functions :
     - shm_create()
     - shm_delete()

     - shm_open()  // join   | an existing shm segment
     - shm_close() // unjoin |

     - shm_read()
     - shm_write()

    12/01/2021 > [0.1.0] :
    - Created shm.c/.h.
    - Added the demonstration programs.

    20/01/2021 > [0.1.1] :
    - Fixed a little thing in shm_write/read().
    - Added shm info (which is shm id written on 8 characters in hexadecimal).
    - Added a required FATAL ERROR in shm_open().

    BUGS : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A..
******************************************************************************************

    LICENCE :

    C_SHM
    Copyright (C) 2021  Sebastien SILVANO
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.

    If not, see <https://www.gnu.org/licenses/>.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




















// -------------------------------- SHM --------------------------------

//create - delete
shm* shm_create(unsigned int length){
	if(length == 0){
		printf("RUNTIME ERROR > shm.c : shm_create() : Cannot allocate 0 bytes.\n");
		return NULL;
	}

	//create new shm instance
	shm* shared = malloc(sizeof(shm));
	if(shared == NULL){
		printf("FATAL ERROR > shm.c : shm_create() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}

	//set id
	shared->id = shmget(
		IPC_PRIVATE,
		length,
		IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR
	);

	//set info
	shared->info = malloc(9);
	if(shared->info == NULL){
		printf("FATAL ERROR > shm.c : shm_create() : Computer refuses to give more shared memory.\n");
		exit(EXIT_FAILURE);
	}
	sprintf(shared->info, "%08x", (unsigned int)shared->id);

	//set length
	shared->length = length;

	//set data
	shared->data = shmat(shared->id, 0, 0);
	if(shared->data == NULL){
		printf("FATAL ERROR > shm.c : shm_create() : Computer refuses to give more shared memory.\n");
		exit(EXIT_FAILURE);
	}

	return shared;
}

void shm_delete(shm* shared){
	if(shared == NULL){
		printf("RUNTIME ERROR > shm.c : shm_delete() : SHM instance is NULL.\n");
		return;
	}

	//free shm
	shmctl(shared->id, IPC_RMID, 0);
	free(shared->info);
	shmdt(shared->data);
	free(shared);
}



//open - close
shm* shm_open(size_t id, unsigned int length){
	if(length == 0){
		printf("RUNTIME ERROR > shm.c : shm_open() : Cannot allocate 0 bytes.\n");
		return NULL;
	}

	//create new shm instance
	shm* shared = malloc(sizeof(shm));
	if(shared == NULL){
		printf("FATAL ERROR > shm.c : shm_open() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}

	//set id
	shared->id = id;

	//set info
	shared->info = malloc(9);
	if(shared->info == NULL){
		printf("FATAL ERROR > shm.c : shm_open() : Computer refuses to give more shared memory.\n");
		exit(EXIT_FAILURE);
	}
	sprintf(shared->info, "%08x", (unsigned int)shared->id);

	//set length
	shared->length = length;

	//set data
	shared->data = shmat(shared->id, 0, 0);
	if(shared->data == NULL){
		printf("FATAL ERROR > shm.c : shm_open() : Computer refuses to give more shared memory.\n");
		exit(EXIT_FAILURE);
	}

	return shared;
}

void shm_close(shm* shared){
	if(shared == NULL){
		printf("RUNTIME ERROR > shm.c : shm_close() : SHM instance is NULL.\n");
		return;
	}

	//free structure (and not the shm segment)
	shmdt(shared->data);
	free(shared->info);
	free(shared);
}



//read - write
char* shm_read(shm* shared){ //returned data is NOT a copy but the SHM segment itself
	if(shared == NULL){
		printf("RUNTIME ERROR > shm.c : shm_read() : SHM instance is NULL.\n");
		return NULL;
	}

	return shared->data;
}

void shm_write(shm* shared, char* data){ // data will not be free after use
                                         //WARNING ! data MUST HAVE length >= shared->length ('\0' IS NOT DETERMINATIVE)
	//error cases
	if(shared == NULL){
		printf("RUNTIME ERROR > shm.c : shm_write() : SHM instance is NULL.\n");
		return;
	}
	if(data == NULL){
		printf("RUNTIME ERROR > shm.c : shm_write() : Given data is NULL.\n");
		return;
	}

	//set data
	for(unsigned int u=0; u < shared->length; u++)
		shared->data[u] = data[u];
}
