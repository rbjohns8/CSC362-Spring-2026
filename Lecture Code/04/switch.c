#include <stdio.h>

int main(void) {
	switch(1) {
	  case 1: /* Goes to this switch */
		puts("1");
		break; /* Jumps to the end of the block */
	  case 2: /* Ignores this program */
		puts("2");
		break;
	  default:
	} /* Continues here */
}


