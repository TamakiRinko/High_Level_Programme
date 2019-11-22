//
// Created by rinko on 2019/11/11.
//

#include "Zombie.h"
#include "Paint.h"
#include "Garlic.h"

extern Plant* plantList[MAP_ROW][MAP_COL];									//���ڵ�ֲ���б�
extern mutex plantListMutex;												//ֲ���б�����
extern bool gameOver;														//��Ϸ����
extern Map gameMap;															//��ͼ
extern int arriveSequence[MAP_ROW][MAP_COL];								//��ʬ����ĳ��Ĵ���
extern Paint paint;															//����
extern int curScore;														//�÷�

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
 * ���٣��ܵ��������ֵĹ���
 */
void Zombie::slowDown(){
	slowDownInterval = 0;
	if (!isSlowDown){												//���٣���Ϊ��ɫ
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
	paint.paintBlank(point.x, point.y);									//ԭλ����Ϊ�հ�
	point.y = point.y - k;
	isModified = true;

	//���õ���ʱ��
	arriveTime = arriveSequence[point.x][point.y];
	arriveSequenceAdd(point.x, point.y);
}

bool Zombie::attacked(int damage){
	isModified = true;
	remainBlood = remainBlood - damage;
	if (remainBlood <= 0) {											//����
		remainBlood = 0;
		curScore = curScore + score;
		paint.paintScore();
		return true;
	}
	return false;													//δ����
}

void Zombie::start(){
	if (isSlowDown){
		slowDownInterval++;
		if (slowDownInterval >= 40){								//ʱ�䵽�ˣ��ָ��ٶȣ���ɫ
			isSlowDown = false;
			speed = preSpeed;
			color = preColor;
		}
	}
	if (speed == 0){
		return;
	}
	
	interval++;
	if (interval >= 30 / speed && gameMap.isPlant(point.x, point.y - 1)) {				//��ֲ���
		interval = 0;
		if (plantList[point.x][point.y - 1] != nullptr && plantList[point.x][point.y - 1]->attacked(attackPower)) {
			removePlant(point.x, point.y - 1);
		}
		else if (dynamic_cast<Garlic*>(plantList[point.x][point.y - 1])) {		//��������
			gameMap.reset(point.x, point.y);
			paint.paintBlank(point.x, point.y);									//ԭλ����Ϊ�հ�

			//�ƶ�
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

			//���õ���ʱ��
			arriveTime = arriveSequence[point.x][point.y];
			arriveSequenceAdd(point.x, point.y);
		}
	}//TODO: �ӵ��뽩ʬ��ײ����
	else if (interval >= 240 / speed && gameMap.isNotOccupied(point.x, point.y - 1)) {	//�޶�����ǰ��
		interval = 0;
		move(1);
		if (point.y == 0) {									//TODO: ��ʱ���
			paint.paintGameOver();
			gameOver = true;
		}
	}
}
    