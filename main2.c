#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void * print(void * arg){
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	int i = 0;
	while (1){
		printf("Child: Iteration %d.\n", i);
		sleep(1);
		i++;
	}
}

int main(int argc, char **argv){
	if (argc == 1){
		printf("Error argv...\n");
		printf("Enter argv.\n");
	}else{
		pthread_t th;
		if (pthread_create(&th, NULL, &print, NULL) != 0) {
				fprintf(stderr, "Error (thread1)\n");
				return 1;
		}
		sleep(atoi(argv[1]));
		pthread_cancel(th);
		void *result;
		if (!pthread_equal(pthread_self(), th))
				pthread_join(th, &result) ;
		if (result == PTHREAD_CANCELED)
			fprintf(stderr, "Canceled\n");
		else fprintf(stderr, "Succesful exit\n");
	}
	return 0;
}
