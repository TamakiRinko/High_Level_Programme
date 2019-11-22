//
// Created by rinko on 2019/11/11.
//

#include "Zombie.h"
#include "Paint.h"
#include "Garlic.h"

extern Plant* plantList[MAP_ROW][MAP_COL];									//存在的植物列表
extern mutex plantListMutex;												//植物列表互斥锁
extern bool gameOver;														//游戏结束
extern Map gameMap;															//地图
extern int arriveSequence[MAP_ROW][MAP_COL];								//僵尸到达某点的次序
extern Paint paint;															//画笔
extern int curScore;														//得分

extern void arriveSequenceAdd(int x, int y);
extern void removePlant(int x, int y);

Zombie::Zombie(ZombieType zombieType, Point* point) : arriveTime(0), slowDownInterval(0), isSlowDown(false), isDead(false) {
	speed = zombieMap[zombieType].getSpeed();
	attackPower = zombieMap[zombieType].getAttackPower();
	color = zombieMap[zombieType].getColor();
	score = zombieMap[zombieType].getScore();
	remainBlood = zombieMap[zombieType].getRemainBlood();
	this->point = *point;
}

Zombie::Zombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood) :
MoveObject(speed, attackPower, point, color, remainBlood), arriveTime(0), score(score), slowDownInterval(0), isSlowDown(false), isDead(false){}

void Zombie::setArriveTime(int a){
	arriveTime = a;
}

int Zombie::getArriveTime(){
	return arriveTime;
}

bool Zombie::getIsDead(){
	return isDead;
}

/**
 * 减速，受到寒冰射手的攻击
 */
void Zombie::slowDown(){
	slowDownInterval = 0;
	if (!isSlowDown){												//缓速，变为蓝色
		isSlowDown = true;
		preSpeed = speed;
		preColor = color;
		speed = speed / 2;
		color = BLUE;
	}
}

void Zombie::move(int k){
	gameMap.reset(point.x, point.y);
	gameMap.setZombie(point.x, point.y - k);
	paint.paintBlank(point.x, point.y);									//原位置置为空白
	point.y = point.y - k;
	isModified = true;

	//设置到达时间
	arriveTime = arriveSequence[point.x][point.y];
	arriveSequenceAdd(point.x, point.y);
}

bool Zombie::attacked(int damage){
	isModified = true;
	remainBlood = remainBlood - damage;
	if (remainBlood <= 0) {											//死亡
		remainBlood = 0;
		curScore = curScore + score;
		paint.paintScore();
		return true;
	}
	return false;													//未死亡
}

void Zombie::start(){
	if (isSlowDown){
		slowDownInterval++;
		if (slowDownInterval >= 40){								//时间到了，恢复速度，颜色
			isSlowDown = false;
			speed = preSpeed;
			color = preColor;
		}
	}
	if (speed == 0){
		return;
	}
	
	interval++;
	if (interval >= 30 / speed && gameMap.isPlant(point.x, point.y - 1)) {				//是植物，吃
		interval = 0;
		if (plantList[point.x][point.y - 1] != nullptr && plantList[point.x][point.y - 1]->attacked(attackPower)) {
			removePlant(point.x, point.y - 1);
		}
		else if (dynamic_cast<Garlic*>(plantList[point.x][point.y - 1])) {		//大蒜类型
			gameMap.reset(point.x, point.y);
			paint.paintBlank(point.x, point.y);									//原位置置为空白

			//移动
			if (point.x == 0 && !gameMap.isPlant(point.x + 1, point.y)) {
				point.x = point.x + 1;
			}
			else if (point.x == MAP_ROW - 1 && !gameMap.isPlant(point.x - 1, point.y)) {
				point.x = point.x - 1;
			}
			else if (point.x > 0 && !gameMap.isPlant(point.x - 1, point.y)) {
				point.x = point.x - 1;
			}
			else if (point.x > 0 && !gameMap.isPlant(point.x + 1, point.y)) {
				point.x = point.x + 1;
			}
			gameMap.setZombie(point.x, point.y);
			isModified = true;

			//设置到达时间
			arriveTime = arriveSequence[point.x][point.y];
			arriveSequenceAdd(point.x, point.y);
		}
	}//TODO: 子弹与僵尸碰撞过程
	else if (interval >= 240 / speed && gameMap.isNotOccupied(point.x, point.y - 1)) {	//无东西，前进
		interval = 0;
		move(1);
		if (point.y == 0) {									//TODO: 暂时如此
			paint.paintGameOver();
			gameOver = true;
		}
	}
}
    