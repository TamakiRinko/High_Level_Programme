//
// Created by rinko on 2019/11/13.
//

#ifndef PLANTSVSZOMBIES_PAINT_H
#define PLANTSVSZOMBIES_PAINT_H

#include "Object.h"
#include "Shop.h"

class Paint{
private:
	mutex paintMutex;									//绘画互斥锁
public:
	Paint();
	~Paint();
	void paintBoarder();
	void paintShop();
	void paintSelectedShop(int r, int c);				
	void paintSelectedMap(int r, int c);				//绘制选中地图
	void paintObject();
	void paintBlank(int r, int c);						//清除僵尸和植物之前的痕迹
	void paintString(int r, int c, string str);
	void paintGameOver();
	void paintMapPos(Point* mapPos);
	void paintBlankBullet(int r, int c);				//清除子弹
	void paintBlankMap(int r, int c);					//清除选中地图
	void paintSunNum();									//绘制全局阳光数
	void paintScore();									//绘制得分
};

#endif
