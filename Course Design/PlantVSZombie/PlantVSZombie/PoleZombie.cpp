//
// Created by rinko on 2019/11/15.
//

#include "PoleZombie.h"
#include "NormalZombie.h"
#include "Paint.h"
#include "Garlic.h"
#include "HighNut.h"
#include "ZombieReflector.h"

extern Plant* plantList[MAP_ROW][MAP_COL];									//���ڵ�ֲ���б�
extern mutex plantListMutex;												//ֲ���б�����
extern bool gameOver;														//��Ϸ����
extern Map gameMap;																//��ͼ
extern int arriveSequence[MAP_ROW][MAP_COL];								//��ʬ����ĳ��Ĵ���
extern Paint paint;															//����

extern void arriveSequenceAdd(int x, int y);
extern void removePlant(int x, int y);

ZOMBIEREFLECT(PoleZombie, (int)ZombieType::POLE)

PoleZombie::PoleZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood) :
Zombie(speed, attackPower, point, color, score, remainBlood), hasPole(true){
}

PoleZombie::PoleZombie(ZombieType zombieType, Point* point): Zombie(zombieType, point), hasPole(true){}

bool PoleZombie::jump(){
	if (hasPole){
		if (dynamic_cast<HighNut* >(plantList[point.x][point.y - 1])){		//������Ծ��ʧ��
			hasPole = false;
			return true;
		}
		if (point.y - 2 < 0){
			paint.paintGameOver();
			gameOver = true;
			return true;
		}
		if (gameMap.isPlant(point.x, point.y - 2)){							//��������Ծ
			return false;
		}
		//��Ծ���ƶ�2��
		move(2);
		hasPole = false;
		return true;
	}
	return false;
}

void PoleZombie::start() {
	if (isSlowDown) {
		slowDownInterval++;
		if (slowDownInterval >= 40) {								//ʱ�䵽�ˣ��ָ��ٶȣ���ɫ
			isSlowDown = false;
			speed = preSpeed;
			color = preColor;
		}
	}
	if (speed == 0) {
		return;
	}

	interval++;
	if (interval >= 30 / speed && gameMap.isPlant(point.x, point.y - 1)) {				//��ֲ���
		interval = 0;

		if (jump()){
			return;
		}
		
		if (plantList[point.x][point.y - 1] != nullptr && plantList[point.x][point.y - 1]->attacked(attackPower)) {
			removePlant(point.x, point.y - 1);
		}
		else if (dynamic_cast<Garlic*>(plantList[point.x][point.y - 1])) {		//��������
			gameMap.reset(point.x, point.y);
			paint.paintBlank(point.x, point.y);									//ԭλ����Ϊ�հ�

			//�ƶ�
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

			//���õ���ʱ��
			arriveTime = arriveSequence[point.x][point.y];
			arriveSequenceAdd(point.x, point.y);
		}
	}//TODO: �ӵ��뽩ʬ��ײ����
	else if (interval >= 240 / speed && gameMap.isNotOccupied(point.x, point.y - 1)) {	//�޶�����ǰ��
		interval = 0;
		move(1);
		if (point.y == 0) {									//TODO: ��ʱ���
			paint.paintGameOver();
			gameOver = true;
		}
	}
}

void PoleZombie::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "�Ÿ˽�ʬ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	if (hasPole) {
		cout << "�гŸ�";
	}
	else {
		cout << "�޳Ÿ�";
	}
	resetTextColor();
}
