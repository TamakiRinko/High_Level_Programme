#include "Map.h"
#include <mutex>

mutex mapMutex;														//地图锁

Map::Map(int r, int c) {
	row = r + 2;
	col = c + 2;
	MAP = new int*[row];
	for (int i = 0; i < row; ++i) {
		MAP[i] = new int[col];
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (i == 0 || i == r + 1 || j == 0 || j == c + 1){			//边界为-1
				MAP[i][j] = -1;
			} else{														//其余为0，表示未有植物。1表示有植物
				MAP[i][j] = 0;
			}
		}
	}
}
Map::~Map() {
	for (int i = 0; i < row; ++i){
		delete MAP[i];
	}
	delete MAP;
}

bool Map::isNotOccupied(int r, int c) const {
	return MAP[r + 1][c + 1] == 0;
}

void Map::setPlant(int r, int c) const {
	mapMutex.lock();
	MAP[r + 1][c + 1] = 1;
	mapMutex.unlock();
}

void Map::setZombie(int r, int c) const{
	mapMutex.lock();
	MAP[r + 1][c + 1] = 2;
	mapMutex.unlock();
}

void Map::reset(int r, int c) const{
	mapMutex.lock();
	MAP[r + 1][c + 1] = 0;
	mapMutex.unlock();
}

bool Map::isPlant(int r, int c) const{
	return MAP[r + 1][c + 1] == 1;
}

bool Map::isZombie(int r, int c) const{
	return MAP[r + 1][c + 1] == 2;
}
