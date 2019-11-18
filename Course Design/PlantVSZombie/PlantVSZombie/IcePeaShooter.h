#ifndef PLANTSVSZOMBIES_ICEPEASHOOTER_H
#define PLANTSVSZOMBIES_ICEPEASHOOTER_H

#include "Plant.h"

class IcePeaShooter : public Plant {
public:
	IcePeaShooter(int attackPower, const Point& point, Color color, int remainBlood);
	void start() override;

	void draw() override;
};


#endif //PLANTSVSZOMBIES_ICEPEASHOOTER_H
