#include "Complex.h"


Complex::Complex() {
	real = 0;
	image = 0;
}

Complex::Complex(double real, double image): real(real), image(image){}
