//
// Created by rinko on 2019/11/14.
//

#include "IceBullet.h"
#include "Paint.h"
extern vector<Zombie* > zombieList;										//存在的僵尸列表
extern mutex zombieListMutex;											//僵尸列表互斥锁
extern unordered_set<Bullet* > bulletList;								//存在的子弹列表
extern Map map;															//地图
extern Paint paint;														//画笔

IceBullet::IceBullet(int speed, int attackPower, const Point &point, Color color, int remainBlood) :
	Bullet(speed, attackPower, point, color, remainBlood){
}

void IceBullet::start() {
	interval++;
	if (interval >= 8 / speed) {
		interval = 0;
		paint.paintBlankBullet(point.x, point.y);				//走一步
		point.y += 1;
		isModified = true;

		// cout << "(" << point.x << ", " << point.y << ")" << endl;
		int yPos = point.y / 16;
		int xPos = point.x / 9;

		if (map.isZombie(xPos, yPos)) {								//前方为僵尸
			unsigned int time = 0x7fffffff;
			Zombie* zombie = nullptr;
			int index = 0;												//需要删除的僵尸
			for (int i = 0; i < (int)zombieList.size(); ++i) {
				if (zombieList[i]->getPoint().x == xPos && zombieList[i]->getPoint().y == yPos) {
					if (time >(unsigned)zombieList[i]->getArriveTime()) {
						index = i;
						zombie = zombieList[i];
						time = zombieList[i]->getArriveTime();
					}
				}
			}
			if (zombie != nullptr) {										//子弹命中
				if (zombie->attacked(attackPower)) {						//杀死
					zombieListMutex.lock();
					zombieList.erase(zombieList.begin() + index);
					zombieListMutex.unlock();
					paint.paintBlank(xPos, yPos);
					map.reset(xPos, yPos);
				} else{														//未杀死，缓速
					zombie->slowDown();
				}
				//子弹命中，则子弹消失
				isDead = true;
			}
		}
		else {																//前方为空
			//到达底端，消失
			if (point.y > MAP_COL * 16) {
				isDead = true;
			}
		}
	}

}

void IceBullet::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handleOut, { (short)point.y, (short)point.x });
	cout << "●";
	resetTextColor();
}
