//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_SHOP_H
#define PLANTSVSZOMBIES_SHOP_H

#include "Plant.h"

class Shop {
private:
	vector< pair<PlantType, int>* > plants;
	int row;
	int col;
public:
	Shop(int row, int col);
	pair<PlantType, int> buyPlant(Point* point, int sunNum);
	int getRow();
	int getCol();
	pair<PlantType, int>* getGoods(int r, int c);
};


#endif //PLANTSVSZOMBIES_SHOP_H
