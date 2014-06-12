#include <stdio.h>

#define MUTEX_ADDR 	 0x500000
#define OFFLOAD_ADDR 0x500004

#define LOCK while(*lock)
#define UNLOCK *lock=0

// Variaveis de acesso aos modulos
volatile unsigned int *offload = (unsigned int*) OFFLOAD_ADDR;
volatile unsigned int *lock = (unsigned int*) MUTEX_ADDR;

volatile int total_cpu = 0;

void reentrant_print(char* str){
	LOCK;
	puts(str);
	UNLOCK;
	return;
}

unsigned int offload_function(unsigned int x){
	unsigned int local_result;

	LOCK;
	*offload = x; 
	local_result = *offload;
	UNLOCK;
	
	return local_result;
}

void test_offload(){

	unsigned int x = 3;
	unsigned int x2;
	x2 = offload_function(x);
	if (x2 == 9){
		reentrant_print("x2 = 9");
	}
	else{
		reentrant_print("x2 != 9");
	}
}

int main(int argc, char *argv[]){
	int my_id = 0;

	LOCK;
	my_id  = total_cpu++;
	UNLOCK;	

	switch(my_id){
		case 0:
			reentrant_print("Proc 0 -> É o lider, e está testando o offload!");
			test_offload();
		break;

		case 1:
			reentrant_print("Proc 1 -> Hello World!!!");
		break;

		case 2:
			reentrant_print("Proc 2 -> Hello World!!!");
		break;

		case 3:
			reentrant_print("Proc 3 -> Hello World!!!");
		break;

		default:
			reentrant_print("Erro em my_id");
		break;
	}

	return 0;
}

