#include <stdio.h>

#define MUTEX_ADDR 0x10000000
#define LOCK while(*lock == 1)
#define UNLOCK *lock=0

volatile int *lock = (int*) MUTEX_ADDR;
volatile int total_cpu = 0;

void reentrant_print(char* str){
	LOCK;
	puts(str);
	fflush(stdout);
	UNLOCK;
	return;
}

int main(int argc, char *argv[]){
	int my_id = 0;

	LOCK;
	my_id  = total_cpu++;
	printf("-=>%d<=-\n", my_id);
	UNLOCK;

	char* str;
	sprintf(str, "Proc %d -> Hello world!!!\n", my_id);
	reentrant_print(str);

	exit(0); // To avoid cross-compiler exit routine
	return 0; // Never executed, just for compatibility
}

