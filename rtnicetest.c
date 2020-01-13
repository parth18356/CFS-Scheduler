#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void func()
{
	struct timespec start, finish; 
	clock_gettime(CLOCK_REALTIME, &start); 
	
	printf("Computation started\n");
	int i,j; 
	for (i=0,j=0; i<100000000; i++) 
	{ 
		j+=i*i; 
	}     
	printf("Computation finished\n");
	
	clock_gettime(CLOCK_REALTIME, &finish); 

	long seconds = finish.tv_sec - start.tv_sec; 
	long ns = finish.tv_nsec - start.tv_nsec; 

	if (start.tv_nsec > finish.tv_nsec) 
	{ 
		--seconds; 
		ns += 1000000000; 
	} 
	printf("Seconds without ns: %ld\n", seconds); 
	printf("nanoseconds: %ld\n", ns); 
	printf("Total seconds: %e\n", (double)seconds + (double)ns/(double)1000000000); 
}
int main(int argc, char** argv)
{  
	printf("\n-------Starting func()-------\n");
	int pid = getpid();
	func();
	printf("---------Done: func()---------\n\n");
	unsigned long timeslice = 10000000000;
	int pid1 = getpid();
	if (pid != pid1)
		return 0;
	printf("--------Starting SRT func()------\n");
	int pid2 = getpid();
	printf("PID of this task = %d\n", pid2);
	long int status = syscall(323, pid2, timeslice); 
	if(status == 0) 
	{
		func();
		printf("--------Ending SRT func()-------\n\n");
	}
	else 
	{
		printf("System call rtnice did not execute as expected\n");
		perror("Error ");
		printf("Error No.: %d\n\n", errno);
	}
	return 0;
}
