#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#define NTHREADS 8
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
uint32_t i = 2;
uint64_t n = 1;
bool done;

int nDivisors(uint64_t n) {
	uint64_t i;
	uint32_t c = 0;
	for (i = 1; i <= n; i++) {
		if (n%i == 0) {
			c++;
		}
	}
	return c;
}
void* thread(void * args) {
	uint64_t temp;
	
	while (!done) {
		pthread_mutex_lock(&mutex);
		temp = n;
		n = n + i++;
		pthread_mutex_unlock(&mutex);
		
		if (nDivisors(temp) > 500) {
			printf("%lld\n", temp);
			done = true;
		}
	}
	return NULL;
}
int main(int argc, const char *argv[]) {
	pthread_t thread_id[NTHREADS];
	int j;

	done = false;

	for (j = 0; j < NTHREADS; j++) {
		pthread_create(&thread_id[j], NULL, &thread, NULL);
	}

	for (j = 0; j < NTHREADS; j++) {
		pthread_join(thread_id[j], NULL);
	}
	return 0;
}
