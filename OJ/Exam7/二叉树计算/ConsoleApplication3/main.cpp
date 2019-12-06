#include "Tree.h"
#include "Complex.h"
#include <iomanip>

int main() {
	Complex c(2, -1);
	cout << c << endl;

	Tree<Complex> tree1(1, c);
	tree1.preorder_show();

	tree1.accumulate(Complex(1, 0));
	tree1.preorder_show();

	cout << tree1.count(Complex(3,-1)) << endl;

	cout << tree1.accumulate([](Complex x, Complex y) {return x * y - x - y; }, Complex()) << endl;
	tree1.preorder_show();

	Tree<int> tree2(2, 1);
	tree2.preorder_show();
	cout << tree2.accumulate([](int x, int y) {return x + y; }, 0) << endl;
	tree2.preorder_show();
}
