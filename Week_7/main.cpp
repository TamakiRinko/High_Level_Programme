#include "port.h"
#include "vintageport.h"


int main(){
	VintagePort vp("ABC", 20, "XYZ", 1980);
	VintagePort vp2 = vp;
	vp -= 10;
	vp += 12;
	cout << vp << endl;
	cout << vp2 << endl;

	Port* p;
	p = new Port("abc", "def", 34);
	(*p) += 3;
	p->Show();
	cout << endl << *(p) << endl << endl;//abc, def, 37

	p = new VintagePort("WWW", 12, "QQQ", 1934);
	p->Show();
	cout << endl << *(p) << endl << endl;//WWW, vintage, 12
	return 0;
}