//
// Created by rinko on 2019/11/14.
//

#include "ClownZombie.h"
#include "Paint.h"
#include "Garlic.h"
#include <random>

extern Plant* plantList[MAP_ROW][MAP_COL];									//���ڵ�ֲ���б�
extern mutex plantListMutex;												//ֲ���б�����
extern bool gameOver;														//��Ϸ����
extern Map map;																//��ͼ
extern int arriveSequence[MAP_ROW][MAP_COL];								//��ʬ����ĳ��Ĵ���
extern Paint paint;															//����
extern int curScore;														//�÷�

extern void arriveSequenceAdd(int x, int y);
extern void removePlant(int x, int y);

bool ClownZombie::explosion(){
	int x = (((unsigned)rand()) % 15);
	if (x == 1){
		// paint.paintString(MAP_ROW + 2, 0, "1");
		//��ըЧ��
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (point.x + i >= 0 && point.y + j >= 0 && point.x + i < MAP_ROW && point.y + j < MAP_COL) {
					paint.paintSelectedMap(point.x + i, point.y + j);
				}
			}
		}
		Sleep(500);
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (point.x + i >= 0 && point.y + j >= 0 && point.x + i < MAP_ROW && point.y + j < MAP_COL) {
					paint.paintBlankMap(point.x + i, point.y + j);
				}
			}
		}
		for (int i = -1; i < 2; ++i){
			for (int j = -1; j < 2; ++j){
				if (i == 0 && j == 0){
					continue;
				}
				if (point.x + i >= 0 && point.y + j >= 0 && point.x + i < MAP_ROW && point.y + j < MAP_COL){
					if (plantList[point.x + i][point.y + j] != nullptr){
						removePlant(point.x + i, point.y + j);
					}
				}
			}
		}
		
		isDead = true;
		attacked(50);
		paint.paintBlank(point.x, point.y);
		curScore = curScore - score;															//�Ա������ӷ�
		paint.paintScore();
		map.reset(point.x, point.y);
		return true;
	}
	return false;
}

ClownZombie::ClownZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood) :
Zombie(speed, attackPower, point, color, score, remainBlood){
}

void ClownZombie::start() {
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
	if (interval >= 30 / speed && map.isPlant(point.x, point.y - 1)) {				//��ֲ���
		interval = 0;
		if (plantList[point.x][point.y - 1] != nullptr && plantList[point.x][point.y - 1]->attacked(attackPower)) {
			removePlant(point.x, point.y - 1);
		} else if (dynamic_cast<Garlic*>(plantList[point.x][point.y - 1])){		//��������
			map.reset(point.x, point.y);
			paint.paintBlank(point.x, point.y);									//ԭλ����Ϊ�հ�

			//�ƶ�
			if (point.x == 0 && !map.isPlant(point.x + 1, point.y)) {
				point.x = point.x + 1;
			} else if (point.x == MAP_ROW - 1 && !map.isPlant(point.x - 1, point.y)){
				point.x = point.x - 1;
			}else if (point.x > 0 && !map.isPlant(point.x - 1, point.y)) {
				point.x = point.x - 1;
			}else if (point.x > 0 && !map.isPlant(point.x + 1, point.y)){
				point.x = point.x + 1;
			}
			map.setZombie(point.x, point.y);
			isModified = true;

			//���õ���ʱ��
			arriveTime = arriveSequence[point.x][point.y];
			arriveSequenceAdd(point.x, point.y);
		}
	}//TODO: �ӵ��뽩ʬ��ײ����
	else if (interval >= 240 / speed && map.isNotOccupied(point.x, point.y - 1)) {	//�޶�����ǰ��
		interval = 0;

		if (explosion()){																//��ը
			return;
		}
		
		move(1);
		if (point.y == 0) {									//TODO: ��ʱ���
			paint.paintGameOver();
			gameOver = true;
		}
	}
	
}

void ClownZombie::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "С��ʬ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << remainBlood * 2<< "% ";
	resetTextColor();
}
