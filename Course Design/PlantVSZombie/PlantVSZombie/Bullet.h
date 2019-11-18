//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_BULLET_H
#define PLANTSVSZOMBIES_BULLET_H

#include "MoveObject.h"
#include "Zombie.h"


class Bullet : public MoveObject{
protected:
	bool isDead;
public:
	//Bullet������ʹ��С���꣬���Ǵ��������
	Bullet(int speed, int attackPower, const Point &point, Color color, int remainBlood = 100);
	void start() override;
	void draw() override;
	COORD& getCoord() override;
	bool getIsDead();
};


#endif //PLANTSVSZOMBIES_BULLET_H
