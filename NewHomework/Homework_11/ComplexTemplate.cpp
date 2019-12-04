#include<iostream>
#include<string>
using namespace std;

template<class T1>
class Complex;

// template<class T>
// Complex<T> operator+(const Complex<T>& c1, const Complex<T>& c2){
// 	Complex<T> result(c1.real + c2.real, c1.imaginary + c2.imaginary);
// 	return result;
// }

template<class T1>
class Complex {
private:
	T1 real;
	T1 imaginary;
public:
	Complex(T1 real, T1 imaginary) : real(real), imaginary(imaginary) {}
	Complex(const Complex& c) {						//拷贝构造
		real = c.real;
		imaginary = c.imaginary;
	}
	Complex<T1>& operator=(const Complex<T1>& c);	//赋值重载
	Complex<T1> operator+(const Complex<T1>& c);	//加法重载
	Complex<T1> operator-(const Complex<T1>& c);
	Complex<T1> operator*(const Complex<T1>& c);
	Complex<T1> operator/(const Complex<T1>& c);
	Complex<T1> operator-();						//取反运算
	bool operator==(const Complex<T1>& c);
	bool operator!=(const Complex<T1>& c);
	// friend Complex<T1> operator+<T1>(const Complex<T1>& c1, const Complex<T1>& c2);
	friend ostream& operator << (ostream& out, const Complex<T1>& c) {		//友元
		out << c.real << ", " << c.imaginary;
		return out;
	}
};

template <class T1>
Complex<T1>& Complex<T1>::operator=(const Complex<T1>& c) {
	real = c.real;
	imaginary = c.imaginary;
	return *this;
}

template<class T1>
Complex<T1> Complex<T1>::operator+(const Complex<T1>& c) {
	Complex<T1> result(real + c.real, imaginary + c.imaginary);
	return result;
}

template<class T1>
Complex<T1> Complex<T1>::operator-(const Complex<T1>& c) {
	Complex<T1> result(real - c.real, imaginary - c.imaginary);
	return result;
}

template<class T1>
Complex<T1> Complex<T1>::operator*(const Complex<T1>& c) {
	Complex<T1> result(real * c.real - imaginary * c.imaginary, imaginary * c.real + real * c.imaginary);
	return result;
}

template<class T1>
Complex<T1> Complex<T1>::operator/(const Complex<T1>& c) {
	T1 m = c.real * c.real + c.imaginary * c.imaginary;
	T1 x = (real * c.real + imaginary * c.imaginary) / m;
	T1 y = (imaginary * c.real - real * c.imaginary) / m;
	Complex<T1> result(x, y);
	return result;
}

template <class T1>
Complex<T1> Complex<T1>::operator-(){
	Complex<T1> result(-real, -imaginary);
	return result;
}

template <class T1>
bool Complex<T1>::operator==(const Complex<T1>& c) {
	return (real == c.real && imaginary == c.imaginary);
}

template <class T1>
bool Complex<T1>::operator!=(const Complex<T1>& c){
	return (real != c.real || imaginary != c.imaginary);
}

int main(int argc, char const *argv[]) {
	Complex<int> a(3, 4);
	Complex<int> b(5, 6);
	Complex<int> c(a + b);
	Complex<int> d = a - b;
	Complex<int> e = a * b;
	Complex<int> f(a / b);
	Complex<int> m(3, 4);
	Complex<int> p = -a;
	cout << c << endl << d << endl << e << endl << f << endl << (a == m) << endl << (a != f) << endl << p << endl;
	cout << endl;
	Complex<double> a2(3, 4);
	Complex<double> b2(5, 6);
	Complex<double> c2(a2 + b2);
	Complex<double> d2 = a2 - b2;
	Complex<double> e2 = a2 * b2;
	Complex<double> f2(a2 / b2);
	Complex<double> m2(3, 4);
	Complex<double> p2 = -a2;
	cout << c2 << endl << d2 << endl << e2 << endl << f2 << endl << (a2 == m2) << endl << (a2 != f2) << endl << p2 << endl;
	return 0;
}
