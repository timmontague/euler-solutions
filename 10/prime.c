/*
 * Find the sum of all primes below 2 million
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#define NTHREADS 8
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
uint32_t i = 2;

bool isPrime(unsigned int i) {
	uint32_t n;
	for (n = 2; n <= i/2; n++) {
		if (i%n == 0)
			return false;
	}
	return true;
}
void* thread(void *arguments) {
	uint32_t temp;
	uint64_t sum = 0;
	
	while (true) {
		pthread_mutex_lock(&mutex);
		temp = i++;
		pthread_mutex_unlock(&mutex);
		
		if (temp > 2000000) {
			pthread_exit((void*)sum);
		}

		if (isPrime(temp)) {
			sum+=temp;
		}
	}
	return NULL;
}
int main(int argc, const char *argv[]) {
	pthread_t thread_id[NTHREADS];
	uint64_t temp;
	uint64_t sum = 0;
	int n;

	for (n = 0; n < NTHREADS; n++) {
		pthread_create(&thread_id[n], NULL, &thread, NULL);
	}

	for (n = 0; n < NTHREADS; n++) {
		pthread_join(thread_id[n], (void*)&temp);
		sum += temp;
	}

	printf("%lld\n", sum);
	return 0;
}
