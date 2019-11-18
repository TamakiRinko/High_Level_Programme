//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_ZOMBIE_H
#define PLANTSVSZOMBIES_ZOMBIE_H

#include "MoveObject.h"
#include "Plant.h"

enum ZombieType{
	NORMAL, ROADBLOCK
};

class Zombie : public MoveObject {
protected:
	int arriveTime;											//到达当前格子的时间
	int score;												//击败的得分
	int slowDownInterval;									//缓速的间隔
	bool isSlowDown;										//是否被缓速
	int preSpeed;											//缓速前的速度
	Color preColor;											//缓速前的颜色
	bool isDead;											//是否死亡
public:
	Zombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood = 100);
	void setArriveTime(int a);
	int getArriveTime();
	bool getIsDead();
	void slowDown();
	void move(int k);										//向前移动k个格子
	virtual bool attacked(int damage);
	void start() override;
};


#endif //PLANTSVSZOMBIES_ZOMBIE_H
