#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  static int j = 1;
  for(i=0;i<j;i++)
    printf("Hi from processor MIPS!\n");
    printf("%d\n", j);
  j++;
  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

