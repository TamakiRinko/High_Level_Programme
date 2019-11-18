//
// Created by rinko on 2019/11/11.
//

#include "Shop.h"

Shop::Shop(int row, int col) {
	pair<PlantType, int>* sunFlower = new pair<PlantType, int>(SUNFLOWER, 50);
	pair<PlantType, int>* peaShooter = new pair<PlantType, int>(PEASHOOTER, 100);
	pair<PlantType, int>* nut = new pair<PlantType, int>(NUT, 50);
	pair<PlantType, int>* garlic = new pair<PlantType, int>(GARLIC, 50);
	pair<PlantType, int>* icePeaShooter = new pair<PlantType, int>(ICEPEASHOOTER, 200);
	pair<PlantType, int>* highNut = new pair<PlantType, int>(HIGHNUT, 150);
	
	plants.push_back(sunFlower);
	plants.push_back(peaShooter);
	plants.push_back(nut);
	plants.push_back(garlic);
	plants.push_back(icePeaShooter);
	plants.push_back(highNut);
	this->row = row;
	this->col = col;
}

/**
* 当能够购买时返回购买的植物的种类
* 不能购买时返回NONETYPE
* @param r
* @param c
* @param sunNum
* @return
*/
pair<PlantType, int> Shop::buyPlant(Point* point, int sunNum) {
	int index = point->x * col + point->y;
	if (plants.at(index)->second <= sunNum){
		return *(plants.at(index));
	}
	return *(new pair<PlantType, int>(NONETYPE, 0));
}

int Shop::getRow(){
	return row;
}

int Shop::getCol(){
	return col;
}

pair<PlantType, int>* Shop::getGoods(int r, int c){
	int index = r * col + c;
	if (index > plants.size() - 1){
		return new pair<PlantType, int>(NONETYPE, 0);
	}
	return plants.at(index);
}
