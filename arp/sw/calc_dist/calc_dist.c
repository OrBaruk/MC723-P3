#include <stdio.h>
#include <stdlib.h>

#define MUTEX_ADDR 	 0x500000
#define OFFLOAD_ADDR 0x500004
#define NUM_PROC 8
#define OFFLOAD_ATIVO True

#define LOCK while(*lock)
#define UNLOCK *lock=0

// Variaveis de acesso aos modulos
volatile unsigned int *offload = (unsigned int*) OFFLOAD_ADDR;
volatile unsigned int *lock 	 = (unsigned int*) MUTEX_ADDR;

volatile int total_cpu  = 0;
volatile int read_input = 0;
volatile int need_calc  = NUM_PROC;
volatile int finished   = 0;

unsigned int offload_function(unsigned int x){
	unsigned int local_result;

	LOCK;
	*offload = x; 
	local_result = *offload;
	UNLOCK;
	
	return local_result;
}

void reentrant_print(char* str){
	LOCK;
	puts(str);
	UNLOCK;
	return;
}

int n;
int *x1,*x2;
unsigned int ans = 0;
char *to_print;

int main(int argc, char *argv[]) {
	int i;
	unsigned int aux;
	FILE *fin;
	int my_id;
	
	LOCK;
	my_id = total_cpu++;
	UNLOCK;
	
	if(my_id == 0){		
			LOCK;
			fin = fopen("/home/ec2008/ra081994/MC723/MC723-P3/arp/sw/calc_dist/calc_dist.in", "r");			
			fscanf(fin, " %d", &n);			
			x1 =  (int *) malloc(n * sizeof(int));
			x2 =  (int *) malloc(n * sizeof(int));

			for(i = 0; i < n; i++) {
				fscanf(fin, " %d %d", &x1[i],&x2[i]);			
			}
			
			fclose(fin);
			read_input = 1;
			UNLOCK;
			
	}	
	while(!read_input);
	
	// Caso o offload seja utilizado
	#ifdef OFFLOAD_ATIVO
	for(i = 0; i < n/NUM_PROC; i++) {	
		aux = x1[(n*my_id)/NUM_PROC + i] - x2[(n*my_id)/NUM_PROC + i];
		LOCK;
			*offload = aux; 		
		UNLOCK;				 
	}
	LOCK;
	need_calc--;
	UNLOCK;
	while(need_calc);

	if(my_id == 0){		
		LOCK;
			*offload = 0; 
			ans = *offload;
		UNLOCK;
	}
	#endif

	// Caso sem o offload
	#ifndef OFFLOAD_ATIVO
	for(i = 0; i < n/NUM_PROC; i++) {		
		aux = (x1[(n*my_id)/NUM_PROC + i] - x2[(n*my_id)/NUM_PROC + i])*(x1[(n*my_id)/NUM_PROC + i] - x2[(n*my_id)/NUM_PROC + i]);
		LOCK;
			ans += aux;
		UNLOCK;
	}
	LOCK;
	need_calc--;
	UNLOCK;
	while(need_calc);
	#endif
	
	if(my_id == 0){
			LOCK;
			sprintf(to_print,"\t >> Distancia entre os vetores: %u << \n",ans);
			UNLOCK;
			reentrant_print(to_print);
			LOCK;
			free(x1);
			free(x2);	
			finished = 1;
			UNLOCK;			
	}	
	
	while(!finished);
			
	exit(0); // To avoid cross-compiler exit routine
	return 0; // Never executed, just for compatibility
}
