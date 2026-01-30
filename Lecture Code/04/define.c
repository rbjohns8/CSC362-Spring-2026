#include <stdio.h>

#define PI 3.1459

#define SUNDAY    0
#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6

int main(void) {
	float radius = 2.0;
	
	printf("PI: %f\n", PI);
	printf("Circumference: %f\n", 2 * PI * radius);
	
	return 0;
}

