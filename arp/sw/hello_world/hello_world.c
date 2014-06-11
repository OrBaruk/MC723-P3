#include <stdio.h>

#define MUTEX_ADDR 			0x10000000
#define OFFLOAD_STATUS_ADDR 0x10000004
#define OFFLOAD_INPUT_ADDR  0x10000008
#define OFFLOAD_OUTPUT_ADDR 0x10000012
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

double offload(double x){
	double local_result;
	double *offload_input= (double*) OFFLOAD_INPUT_ADDR;
	double *offload_output= (double*) OFFLOAD_OUTPUT_ADDR;
	int *offload_status= (int*) OFFLOAD_STATUS_ADDR;

	// Entrando em regiao critica
	// LOCK;
	printf("chegou em offload1\n");
	*offload_input = x; // Envia para o offload o valor a ser calculado
	printf("chegou em offload2\n");
	while(offload_status != 0); // Espera pelo computacao do offload
	printf("chegou em offload3\n");
	local_result = *offload_output; // Recebe o resultado do offload
	printf("chegou em offload4\n");
	
	// UNLOCK;
	// Saindo da regiao critica

	return local_result;
}

void test_offload(){

	// UNLOCK;

	char* str;
	double x = 3.0;
	double x2;
	x2 = offload(x);
	sprintf(str, "Entrada: %lf  ||  Saida: %lf", x, x2);
	reentrant_print(str);
	
}

int main(int argc, char *argv[]){
	int my_id = 0;

	LOCK;
	my_id  = total_cpu++;
	printf("-=>%d<=-\n", my_id);
	barrier++;
	if (my_id == 0){
		test_offload();
	}
	// UNLOCK;	

	// while(barrier != 4);

	char* str;
	sprintf(str, "Proc %d -> Hellow World!!!", my_id);
	reentrant_print(str);


	return 0;
}

