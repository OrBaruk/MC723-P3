#include <stdio.h>

#define MUTEX_ADDR 0x10000000
#define LOCK while(*lock)
#define UNLOCK *lock=0


volatile int barrier = 0;
volatile unsigned int *lock = (unsigned int*) MUTEX_ADDR;
volatile int total_cpu = 0;


void reentrant_print(char* str){
	LOCK;
	puts(str);
	UNLOCK;
	return;
}

int main(int argc, char *argv[]){
	int my_id = 0;

	LOCK;
	my_id  = total_cpu++;
	printf("-=>%d<=-\n", my_id);
	barrier++;
	UNLOCK;	

	while(barrier != 4);

	char* str;
	sprintf(str, "Proc %d -> Hello world!!!", my_id);
	reentrant_print(str);

	return 0;
}

