//
// Created by rinko on 2019/11/13.
//

#ifndef PLANTSVSZOMBIES_PAINT_H
#define PLANTSVSZOMBIES_PAINT_H

#include "Object.h"
#include "Shop.h"

class Paint{
private:
	mutex paintMutex;									//�滭������
public:
	Paint();
	~Paint();
	void paintBoarder();
	void paintShop();
	void paintSelectedShop(int r, int c);				
	void paintSelectedMap(int r, int c);				//����ѡ�е�ͼ
	void paintObject();
	void paintBlank(int r, int c);						//�����ʬ��ֲ��֮ǰ�ĺۼ�
	void paintString(int r, int c, string str);
	void paintGameOver();
	void paintMapPos(Point* mapPos);
	void paintBlankBullet(int r, int c);				//����ӵ�
	void paintBlankMap(int r, int c);					//���ѡ�е�ͼ
	void paintSunNum();									//����ȫ��������
	void paintScore();									//���Ƶ÷�
};

#endif
