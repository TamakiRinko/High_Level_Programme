//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_OBJECT_H
#define PLANTSVSZOMBIES_OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <windows.h>
#include <unordered_set>
#include <conio.h>
#include "Map.h"
using namespace std;

const int ZOMBIE_TYPE_NUM = 4;
const int MAP_ROW = 5;
const int MAP_COL = 8;
const int SHOP_ROW = 3;
const int SHOP_COL = 2;


/**
* ��ͼ�ϵĶ�ά����
*/
class Point{
public:
	int x;
	int y;
	Point(int xPos, int yPos){
		x = xPos;
		y = yPos;
	}
	Point(const Point& point){
		x = point.x;
		y = point.y;
	}
	bool operator==(const Point& p){
		return p.x == x && p.y == y;
	}
	Point& operator=(const Point& p){
		x = p.x;
		y = p.y;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Point& point);
};

enum Color{
	BLUE = 1, GREEN = 2, RED = 4, PINK = 5, YELLOW = 6, ORIGIN = 7, LITEBLUE = 9, LITEGREEN = 0xa, LITEPINK = 0xd, LITEYELLOW = 0xe
};

class Object {
protected:
	int remainBlood;                                        //ʣ��Ѫ��
	int attackPower;                                        //������
	Point point;                                            //λ��
	Color color;											//������ɫ
	// bool isRunning;											//�����Ƿ񻹴���
	bool isModified;										//�Ƿ�ı��
	int interval;											//�����ļ��
public:
	Object(int attackPower, const Point &point, Color color, int remainBlood);

	void setTextColor();
	void resetTextColor();

	virtual ~Object();
	// virtual void stop();									//��������
	virtual void start() = 0;								//���������߼�����
	virtual void draw() = 0;								//�����Լ�

	virtual COORD& getCoord();
	virtual COORD& getNextLineCoord();

	int getRemainBlood() const;
	void setRemainBlood(int remainBlood);
	int getAttackPower() const;
	void setAttackPower(int attackPower);
	const Point &getPoint() const;
	void setPoint(const Point &point);
	bool getIsModified();
	void resetIsModified();
};


#endif //PLANTSVSZOMBIES_OBJECT_H
