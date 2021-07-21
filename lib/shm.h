#ifndef SHM_H
#define SHM_H




















// -------------------------------- DEFINITIONS --------------------------------

//structures
struct SHM{
	unsigned int length;
	char* data;
	char* info;
	unsigned int id;
};
typedef struct SHM shm;




















// -------------------------------- SHM --------------------------------

//create - delete
shm* shm_create(unsigned int length);
void shm_delete(shm* shared);

//open - close
shm* shm_open(unsigned int id, unsigned int length);
void shm_close(shm* shared);

//read - write
char* shm_read(shm* shared);             //returned data is NOT a copy but the SHM segment itself
void shm_write(shm* shared, char* data); // data will not be free after use
                                         //WARNING ! data MUST HAVE length >= shared->length ('\0' IS NOT DETERMINATIVE)



















#endif
