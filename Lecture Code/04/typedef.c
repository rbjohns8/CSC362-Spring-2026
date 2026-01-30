#include <stdio.h>

struct Point2D {
	float x;
	float y;
};

typedef struct {
	float width;
	float height;
} Rectangle2D;

typedef double Temperature;

int main(void) {
	struct Point2D p1 = {10.0, 20.0};
	Rectangle2D r1 = {30.0, 40.0};
	Temperature temperature = 25.52309234823402;
	
	printf("Point (%.2f, %.2f)\n", p1.x, p1.y);
	printf("Rectangle (%.2f, %.2f)\n", r1.width, r1.height);
	printf("Temperature: %.1f\n", temperature);

	return 0;
}
