//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_SUNFLOWER_H
#define PLANTSVSZOMBIES_SUNFLOWER_H

#include "Plant.h"
extern mutex curSunNumMutex;												//ȫ���������Ļ�����
extern int curSunNum;														//ȫ��������

class SunFlower : public Plant {
public:
	SunFlower(int attackPower, const Point& point, Color color, int remainBlood);

	void start() override;
	void draw() override;
};


#endif //PLANTSVSZOMBIES_SUNFLOWER_H
