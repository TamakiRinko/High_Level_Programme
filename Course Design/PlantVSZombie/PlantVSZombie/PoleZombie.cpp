//
// Created by rinko on 2019/11/15.
//

#include "PoleZombie.h"
#include "NormalZombie.h"
#include "Paint.h"
#include "Garlic.h"
#include "HighNut.h"
#include "ZombieReflector.h"

extern Plant* plantList[MAP_ROW][MAP_COL];									//存在的植物列表
extern mutex plantListMutex;												//植物列表互斥锁
extern bool gameOver;														//游戏结束
extern Map gameMap;																//地图
extern int arriveSequence[MAP_ROW][MAP_COL];								//僵尸到达某点的次序
extern Paint paint;															//画笔

extern void arriveSequenceAdd(int x, int y);
extern void removePlant(int x, int y);

ZOMBIEREFLECT(PoleZombie, (int)ZombieType::POLE)

PoleZombie::PoleZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood) :
Zombie(speed, attackPower, point, color, score, remainBlood), hasPole(true){
}

PoleZombie::PoleZombie(ZombieType zombieType, Point* point): Zombie(zombieType, point), hasPole(true){}

bool PoleZombie::jump(){
	if (hasPole){
		if (dynamic_cast<HighNut* >(plantList[point.x][point.y - 1])){		//尝试跳跃，失败
			hasPole = false;
			return true;
		}
		if (point.y - 2 < 0){
			paint.paintGameOver();
			gameOver = true;
			return true;
		}
		if (gameMap.isPlant(point.x, point.y - 2)){							//不尝试跳跃
			return false;
		}
		//跳跃，移动2格
		move(2);
		hasPole = false;
		return true;
	}
	return false;
}

void PoleZombie::start() {
	if (isSlowDown) {
		slowDownInterval++;
		if (slowDownInterval >= 40) {								//时间到了，恢复速度，颜色
			isSlowDown = false;
			speed = preSpeed;
			color = preColor;
		}
	}
	if (speed == 0) {
		return;
	}

	interval++;
	if (interval >= 30 / speed && gameMap.isPlant(point.x, point.y - 1)) {				//是植物，吃
		interval = 0;

		if (jump()){
			return;
		}
		
		if (plantList[point.x][point.y - 1] != nullptr && plantList[point.x][point.y - 1]->attacked(attackPower)) {
			removePlant(point.x, point.y - 1);
		}
		else if (dynamic_cast<Garlic*>(plantList[point.x][point.y - 1])) {		//大蒜类型
			gameMap.reset(point.x, point.y);
			paint.paintBlank(point.x, point.y);									//原位置置为空白

			//移动
			if (point.x == 0 && !gameMap.isPlant(point.x + 1, point.y)) {
				point.x = point.x + 1;
			}
			else if (point.x == MAP_ROW - 1 && !gameMap.isPlant(point.x - 1, point.y)) {
				point.x = point.x - 1;
			}
			else if (point.x > 0 && !gameMap.isPlant(point.x - 1, point.y)) {
				point.x = point.x - 1;
			}
			else if (point.x > 0 && !gameMap.isPlant(point.x + 1, point.y)) {
				point.x = point.x + 1;
			}
			gameMap.setZombie(point.x, point.y);
			isModified = true;

			//设置到达时间
			arriveTime = arriveSequence[point.x][point.y];
			arriveSequenceAdd(point.x, point.y);
		}
	}//TODO: 子弹与僵尸碰撞过程
	else if (interval >= 240 / speed && gameMap.isNotOccupied(point.x, point.y - 1)) {	//无东西，前进
		interval = 0;
		move(1);
		if (point.y == 0) {									//TODO: 暂时如此
			paint.paintGameOver();
			gameOver = true;
		}
	}
}

void PoleZombie::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "撑杆僵尸";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	if (hasPole) {
		cout << "有撑杆";
	}
	else {
		cout << "无撑杆";
	}
	resetTextColor();
}
