//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_ZOMBIE_H
#define PLANTSVSZOMBIES_ZOMBIE_H

#include "MoveObject.h"
#include "Plant.h"
#include <map>

enum ZombieType{
	NORMAL, ROADBLOCK, CLOWN, POLE
};

class ZombieInfo{
public:
	ZombieInfo() {}
	ZombieInfo(int speed, int attackPower, Color color, int score, int remainBlood):
		speed(speed), attackPower(attackPower), color(color), score(score), remainBlood(remainBlood) {}
	friend ifstream& operator>>(ifstream& fin, ZombieInfo& z){
		int colorNum;
		fin >> z.speed >> z.attackPower >> colorNum >> z.score >> z.remainBlood;
		z.color = Color(colorNum);
		return fin;
	}


	int getSpeed() const{ return speed; }
	int getAttackPower() const{ return attackPower; }
	Color getColor() const{ return color; }
	int getScore() const{ return score; }
	int getRemainBlood() const{ return remainBlood; }
private:
	int speed;												//速度
	int attackPower;                                        //攻击力
	Color color;											//物体颜色
	int score;												//击败的得分
	int remainBlood;                                        //剩余血量
};

extern map<ZombieType, ZombieInfo> zombieMap;

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
	Zombie(ZombieType zombieType, Point* point);
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
