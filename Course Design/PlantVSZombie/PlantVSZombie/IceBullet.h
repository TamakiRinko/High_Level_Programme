//
// Created by rinko on 2019/11/14.
//

#ifndef PLANTSVSZOMBIES_ICEBULLET_H
#define PLANTSVSZOMBIES_ICEBULLET_H

#include "MoveObject.h"
#include "Zombie.h"


class IceBullet : public Bullet {
public:
	//Bullet的坐标使用小坐标，而非大格子坐标
	IceBullet(int speed, int attackPower, const Point &point, Color color = LITEBLUE, int remainBlood = 100);
	void start() override;
	void draw() override;
};


#endif //PLANTSVSZOMBIES_ICEBULLET_H
