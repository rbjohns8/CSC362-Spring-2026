#include <stdio.h>
#include <string.h>

struct Person {
	char name[50];
	int age;
	float height;
};

int main(void) {
	struct Person person1;
	
	strcpy(person1.name, "John Doe");
	person1.age = 25;
	person1.height = 175.5;
	
	printf("Person's name: %s\n", person1.name);
	printf("Person's age: %d\n", person1.age);
	printf("Person's height: %f\n", person1.height);

	return 0;
}

