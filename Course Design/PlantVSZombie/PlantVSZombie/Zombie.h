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
	int speed;												//�ٶ�
	int attackPower;                                        //������
	Color color;											//������ɫ
	int score;												//���ܵĵ÷�
	int remainBlood;                                        //ʣ��Ѫ��
};

extern map<ZombieType, ZombieInfo> zombieMap;

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
	Zombie(ZombieType zombieType, Point* point);
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
