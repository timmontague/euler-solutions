#include <stdio.h>
#include <stdbool.h>

#define GOAL 0.99

bool is_bouncy(int n) {
    bool up = false, down = false;
    int lasti = n % 10;
    n = n/10;
    while(n) {
	int i = n % 10;
	n = n/10;
	if (i > lasti)
	    up = true;
	if (i < lasti)
	    down = true;
	if (up && down)
	    return true;
	lasti = i;
    }
    return false;
}

int main(void) {
    int i = 0;
    int n = 0;
    while (true) {
	if (is_bouncy(i))
	    n++;
	if ((float)n/(float)i >= GOAL)
	    break;
	i++;
    }
    printf("number of bouncy numbers from 0 to %d: %d\n", i, n);
    printf("percentage of bouncy numbers from 0 to %d: %f\n", i, (float)n/(float)i);
    return 0;
}
