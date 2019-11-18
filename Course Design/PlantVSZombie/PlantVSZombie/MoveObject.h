//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_MOVEOBJECT_H
#define PLANTSVSZOMBIES_MOVEOBJECT_H

#include "Object.h"

class MoveObject : public Object {
protected:
	int speed;
public:
	MoveObject(int speed, int attackPower, const Point &point, Color color, int remainBlood);
};


#endif //PLANTSVSZOMBIES_MOVEOBJECT_H
