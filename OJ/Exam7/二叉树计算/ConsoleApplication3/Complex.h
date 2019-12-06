#pragma once

#include <iostream>
#include <math.h>
using namespace std;

class Complex {
private:
	double real;
	double image;
public:
	Complex();
	Complex(double real, double image);
	friend ostream& operator<<(ostream& out, const Complex& c){
		if (c.real == 0 && c.image == 0){
			out << "0";
		} else if (c.real == 0){				//TODO:ÔõÃ´´òÓ¡?
			out << c.image << "i";
		} else if (c.image == 0){
			out << c.real;
		} else{
			out << c.real;
			if (c.image > 0){
				out << "+";
			}
			out << c.image << "i";
		}
		return out;
	}

	Complex operator+(const Complex& c){
		Complex result(real + c.real, image + c.image);
		return result;
	}

	Complex operator-(const Complex& c) {
		Complex result(real - c.real, image - c.image);
		return result;
	}

	Complex& operator=(const Complex& c) {
		real = c.real;
		image = c.image;
		return *this;
	}

	Complex operator*(const Complex& c) {
		Complex result(real * c.real - image * c.image, image * c.real + real * c.image);
		return result;
	}

	Complex operator/(const Complex& c) {
		double m = c.real * c.real + c.image * c.image;
		double x = (real * c.real + image * c.image) / m;
		double y = (image * c.real - real * c.image) / m;
		Complex result(x, y);
		return result;
	}

	bool operator==(const Complex& c) {
		return (real == c.real&& image == c.image);
	}
};