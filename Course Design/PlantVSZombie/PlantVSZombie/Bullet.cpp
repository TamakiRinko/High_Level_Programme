//
// Created by rinko on 2019/11/11.
//

#include "Bullet.h"
#include "Paint.h"
extern vector<Zombie* > zombieList;										//���ڵĽ�ʬ�б�
extern mutex zombieListMutex;											//��ʬ�б�����
extern unordered_set<Bullet* > bulletList;								//���ڵ��ӵ��б�
extern Map gameMap;															//��ͼ
extern Paint paint;														//����

Bullet::Bullet(int speed, int attackPower, const Point &point, Color color, int remainBlood) :
	MoveObject(speed, attackPower, point, color, remainBlood), isDead(false) {}

void Bullet::start(){
	interval++;
	if (interval >= 8 / speed){
		interval = 0;
		paint.paintBlankBullet(point.x, point.y);				//��һ��
		point.y += 1;
		isModified = true;
		
		// cout << "(" << point.x << ", " << point.y << ")" << endl;
		int yPos = point.y / 16;
		int xPos = point.x / 9;

		if (gameMap.isZombie(xPos, yPos)) {								//ǰ��Ϊ��ʬ
			unsigned int time = 0x7fffffff;
			Zombie* zombie = nullptr;
			int index = 0;												//��Ҫɾ���Ľ�ʬ
			for (int i = 0; i < (int)zombieList.size(); ++i) {
				if (zombieList[i]->getPoint().x == xPos && zombieList[i]->getPoint().y == yPos) {
					if (time >(unsigned)zombieList[i]->getArriveTime()) {
						index = i;
						zombie = zombieList[i];
						time = zombieList[i]->getArriveTime();
					}
				}
			}
			if (zombie != nullptr) {										//�ӵ�����
				if (zombie->attacked(attackPower)) {
					zombieListMutex.lock();
					zombieList.erase(zombieList.begin() + index);
					zombieListMutex.unlock();
					paint.paintBlank(xPos, yPos);
					gameMap.reset(xPos, yPos);
				}
				//�ӵ����У����ӵ���ʧ
				isDead = true;
			}
		} else{															//ǰ��Ϊ��
			//����׶ˣ���ʧ
			if (point.y > MAP_COL * 16) {
				isDead = true;
			}
		}
	}
	
}

void Bullet::draw(){
	// if (gameMap.isPlant(point.x / 9, point.y / 16) || gameMap.isZombie(point.x / 9, point.y / 16)) {
	// 	return; 
	// }
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handleOut, { (short)point.y, (short)point.x });
	cout << "��";
	resetTextColor();
}

COORD& Bullet::getCoord(){
	COORD* coord = new COORD();
	coord->X = point.y;
	coord->Y = point.x;
	return *coord;
}

bool Bullet::getIsDead(){
	return isDead;
}
