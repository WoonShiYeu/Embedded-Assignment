#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/////////////////////////////////////////////////////////////////////////////////////////
//Pragama Applied

int fib(int64_t n) {

int64_t x, y;
  if (n<2)
    return n;
  else {
    #pragma omp task shared(x)
     x=fib(n-1);
    #pragma omp task shared(y)
     y=fib(n-2);
	int iNum = omp_get_num_procs();
	printf("No. of Procs : %d\t",iNum);

	int nTC = omp_get_num_threads();
	printf("No. of Threads : %d\t",nTC);

	int nID = omp_get_thread_num();
	printf("Thread Num : %d\n",nID);
    #pragma omp taskwait
    return (x+y);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Without Pragma Applied

int fib2(int64_t n) {

int64_t x, y;
  if (n<2)
    return n;
  else {
     x=fib2(n-1);
     y=fib2(n-2);
	int iNum = omp_get_num_procs();
	printf("No. of Procs : %d\t",iNum);

	int nTC = omp_get_num_threads();
	printf("No. of Threads : %d\t",nTC);

	int nID = omp_get_thread_num();
	printf("Thread Num : %d\n",nID);
    return (x+y);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////
//Self written function With Pragma Applied
int fib3(int64_t n) {

int f[n];
int i;
f[0]=0;
f[1]=1;
omp_set_dynamic (0);
omp_set_num_threads(4);
#pragma omp parallel for
	for (i=2; i<n+1; i++) {
	f[i]=f[i-1]+f[i-2];
	int iNum = omp_get_num_procs();
	printf("No. of Procs : %d\t",iNum);

	int nTC = omp_get_num_threads();
	printf("No. of Threads : %d\t",nTC);

	int nID = omp_get_thread_num();
	printf("Thread Num : %d\n",nID);
  }
return f[n];
}

/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]){

	//int64_t n = atoi(argv[10]);
	int64_t n = 8;
	int64_t result = fib3 (n);  
	//Alter the function fib() or fib2() or fib3(), compile and see the difference

	printf("\nFibonacci of %" PRId64 " is %" PRId64 ".\n\n",n,result);
	return 0;

}
