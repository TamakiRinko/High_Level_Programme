//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_PLANT_H
#define PLANTSVSZOMBIES_PLANT_H

#include "Object.h"
#include "Bullet.h"


enum PlantType{
	NONETYPE, SUNFLOWER, PEASHOOTER, NUT, GARLIC, ICEPEASHOOTER, HIGHNUT
};

class Plant : public Object {
public:
	Plant(int attackPower, const Point &point, Color color, int remainBlood = 100);
	virtual bool attacked(int damage);
};


#endif //PLANTSVSZOMBIES_PLANT_H
