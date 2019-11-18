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
	int arriveTime;											//���ﵱǰ���ӵ�ʱ��
	int score;												//���ܵĵ÷�
	int slowDownInterval;									//���ٵļ��
	bool isSlowDown;										//�Ƿ񱻻���
	int preSpeed;											//����ǰ���ٶ�
	Color preColor;											//����ǰ����ɫ
	bool isDead;											//�Ƿ�����
public:
	Zombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood = 100);
	void setArriveTime(int a);
	int getArriveTime();
	bool getIsDead();
	void slowDown();
	void move(int k);										//��ǰ�ƶ�k������
	virtual bool attacked(int damage);
	void start() override;
};


#endif //PLANTSVSZOMBIES_ZOMBIE_H
