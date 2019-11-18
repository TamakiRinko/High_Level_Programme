//
// Created by rinko on 2019/11/12.
//
//

#ifndef PLANTSVSZOMBIES_MAP_H
#define PLANTSVSZOMBIES_MAP_H

// #include "Object.h"
#include <iostream>
#include <windows.h>
using namespace std;

class Map{
	int** MAP;
	int row;
	int col;
public:
	Map(int r, int c);
	~Map();
	bool isNotOccupied(int r, int c) const;
	void setPlant(int r, int c) const;
	void setZombie(int r, int c) const;
	void reset(int r, int c) const;
	bool isPlant(int r, int c) const;
	bool isZombie(int r, int c) const;
	void show() const{
		while (true){
			Sleep(3000);
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					if (MAP[i][j] == -1) {
						cout << "* ";
					}
					else if (MAP[i][j] == 0) {
						cout << "  ";
					}
					else if (MAP[i][j] == 1) {
						cout << "# ";
					}
					else if (MAP[i][j] == 2) {
						cout << "$ ";
					}
				}
				cout << endl;
			}
		}
	}
};

#endif
