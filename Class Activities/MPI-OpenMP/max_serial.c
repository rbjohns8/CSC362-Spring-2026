#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int data[16] = {12, 45, 7, 89, 32, 54, 21, 66, 102, 3, 56, 77, 91, 14, 28, 40};
    int total_elements = 16;
    int max_value = -1;
	int i;
	
	for(i = 0; i < total_elements; i++) {
		if (max_value < data[i])
			max_value = data[i];
	}
	
	printf("Max Value is: %d\n", max_value);
	
	return 0;
}
