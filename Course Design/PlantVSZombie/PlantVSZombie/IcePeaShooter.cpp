#include "IcePeaShooter.h"
#include "IceBullet.h"
extern unordered_set<Bullet* > bulletList;										//���ڵ��ӵ��б�

IcePeaShooter::IcePeaShooter(int attackPower, const Point& point, Color color, int remainBlood)
	: Plant(attackPower, point, color, remainBlood) {}

void IcePeaShooter::start(){
	interval++;
	if (interval >= 100) {
		interval = 0;
		Point* bulletPoint = new Point(this->point.x * 9 + 4, this->point.y * 16 + 12);
		Bullet* bullet = new IceBullet(8, attackPower, *bulletPoint, BLUE, 100);
		bulletList.insert(bullet);
	}
}

void IcePeaShooter::draw(){
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "��������";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << remainBlood << "% ";
	resetTextColor();
}
