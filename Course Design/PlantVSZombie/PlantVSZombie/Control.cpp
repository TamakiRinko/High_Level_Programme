//
// Created by rinko on 2019/11/11.
//

#include "Control.h"

Map gameMap(MAP_ROW, MAP_COL);										//ȫ�ֵ�ͼ
Shop shop(SHOP_ROW, SHOP_COL);										//ȫ���̵�
vector<Zombie* > zombieList;										//���ڵĽ�ʬ�б�
Plant* plantList[MAP_ROW][MAP_COL];									//���ڵ�ֲ���б���άָ������
unordered_set<Bullet* > bulletList;									//���ڵ��ӵ��б�
mutex curSunNumMutex;												//ȫ���������Ļ�����
mutex zombieListMutex;												//��ʬ�б�����
mutex plantListMutex;												//ֲ���б�����
bool gameOver;														//��Ϸ����
int curSunNum;														//ȫ��������
int arriveSequence[MAP_ROW][MAP_COL];								//��ʬ����ĳ��Ĵ���
mutex arriveSequenceMutex[MAP_ROW][MAP_COL];						//arriveSequence����
Paint paint;														//����
int curScore;														//�÷�

int delay[6] = { 0 };


void arriveSequenceAdd(int x, int y){
	arriveSequenceMutex[x][y].lock();
	arriveSequence[x][y]++;
	arriveSequenceMutex[x][y].unlock();
}

/**
 * ɾ��һ��ֲ��
 */
void removePlant(int x, int y){
	plantListMutex.lock();
	delete plantList[x][y];
	plantList[x][y] = nullptr;
	plantListMutex.unlock();
	paint.paintBlank(x, y);			//����Ϊ�հ�
	gameMap.reset(x, y);				//��ͼ����
}


Control::Control() /*: gameMap(MAP_ROW, MAP_COL), shop(SHOP_ROW, SHOP_COL)*/ {
	curSunNum = 1000;
	curScore = 0;
	for (int i = 0; i < MAP_ROW; ++i){
		for (int j = 0; j < MAP_COL; ++j){
			plantList[i][j] = nullptr;
		}
	}
	for (int i = 0; i < MAP_ROW; ++i){
		for (int j = 0; j < MAP_COL; ++j){
			arriveSequence[i][j] = 1;
		}
	}
	keyBoardMode = NORMALMODE;
	curPlantType = NONETYPE;
	curShopPos = nullptr;
	curMapPos = nullptr;
	curPlant = nullptr;
	curPlantCost = 0;
	gameOver = false;
}

void Control::start(){
	paint.paintBoarder();
	paint.paintShop();
	paint.paintSunNum();
	paint.paintScore();
	
	thread generateSunThread(&Control::generateNaturalSun, this);
	generateSunThread.detach();
	thread generateZombieThread(&Control::generateZombie, this);
	generateZombieThread.detach();
	thread keyBoardThread(&Control::keyBoardAction, this);
	keyBoardThread.detach();

	while(!gameOver){
		Sleep(50);
		mainLogic();
	}
}

void Control::keyBoardAction() {
	while (!gameOver) {
		Sleep(50);
		if (_kbhit()) {												//�����̰��²���
			char key = (char)_getch();								//������ȡ���Ὣ���µİ����洢����
			if ((int)key == -32)	continue;						//�������Ҽ��᷵�����Σ���һ��Ϊ-32
			if (!modeCapture(key)) {
				keyCapture(key);
			}
			if (key == 27) {										//ESC
				gameOver = true;
				break;
			}
		}
	}
}

void Control::mainLogic(){
	plantListMutex.lock();
	for (int i = 0; i < MAP_ROW; ++i){
		for (int j = 0; j < MAP_COL; ++j){
			if (plantList[i][j] != nullptr){
				plantList[i][j]->start();
			}
		}
	}
	plantListMutex.unlock();
	
	for (auto it = bulletList.begin(); it != bulletList.end(); ++it) {
		(*it)->start();
	}
	for (auto it = bulletList.begin(); it != bulletList.end(); ) {				//ɾ���ӵ�
		if ((*it)->getIsDead()){
			it = bulletList.erase(it);
		} else{
			++it;
		}
	}
	
	zombieListMutex.lock();
	for (int i = 0; i < zombieList.size(); ++i){
		zombieList[i]->start();
	}
	
	for (auto it = zombieList.begin(); it != zombieList.end();) {				//ɾ����ʬ
		if ((*it)->getIsDead()) {
			it = zombieList.erase(it);
		}
		else {
			++it;
		}
	}
	zombieListMutex.unlock();

	for (int i = 0; i < 6; ++i) {
		if (delay[i] > 0) {
			delay[i]--;
		}
	}

	paint.paintObject();
	if (keyBoardMode != SHOPMODE){
		paint.paintShop();
	}
	else{
		paint.paintSelectedShop(curShopPos->x, curShopPos->y);
	}
}


/**
 * ģʽ�������(b, x, �س� ����true)
 */
bool Control::modeCapture(char key) {
	bool flag = false;
	switch (key){
		case 'b':{
			if (keyBoardMode == NORMALMODE){
				keyBoardMode = SHOPMODE;
				curShopPos = new Point(0, 0);
				paint.paintSelectedShop(curShopPos->x, curShopPos->y);
				// cout << "�̵��е�λ�ã� " << *curShopPos << endl;
			}
			flag = true;
			break;
		}
		case 's': {
			if (keyBoardMode == NORMALMODE) {
				keyBoardMode = SHOVELMODE;
				curMapPos = new Point(0, 0);
				paint.paintSelectedMap(curMapPos->x, curMapPos->y);
			}
			flag = true;
			break;
		}
		case 'x':{
			if (keyBoardMode == MAPMODE){					//ѡ����ֲλ��ģʽ���˻ص�ѡ��ֲ��ģʽ
				keyBoardMode = SHOPMODE;
				curPlantType = NONETYPE;
				paint.paintBlankMap(curMapPos->x, curMapPos->y);		//����ǰλ����ɫ���
				if (curMapPos != nullptr){
					delete curMapPos;
					curMapPos = nullptr;
				}
				paint.paintSelectedShop(curShopPos->x, curShopPos->y);
			} else if (keyBoardMode == SHOPMODE){			//ѡ��ֲ��ģʽ���˻ص�δѡ��ģʽ
				keyBoardMode = NORMALMODE;
				if (curShopPos != nullptr){
					delete curShopPos;
					curShopPos = nullptr;
				}
				paint.paintShop();
			} else if (keyBoardMode == SHOVELMODE){			//����ģʽ��ȡ������
				keyBoardMode = NORMALMODE;
				paint.paintBlankMap(curMapPos->x, curMapPos->y);
			}
			flag = true;
			break;
		}
		case 13:{												//�س���
			if (keyBoardMode == SHOPMODE){						//ѡ��ֲ��
				buyPlant();
			} else if (keyBoardMode == MAPMODE){				//ѡ��λ�ã���ֲֲ��
				if (gameMap.isNotOccupied(curMapPos->x, curMapPos->y)){
					generatePlant();
				}
			} else if (keyBoardMode == SHOVELMODE){
				if (gameMap.isPlant(curMapPos->x, curMapPos->y)){
					shovelPlant();
				}
			}
			flag = true;
			break;
		}
		default: break;
	}
	return flag;
}

/**
 * �������Ҽ��
 */
void Control::keyCapture(char key){
	if (keyBoardMode == SHOPMODE){
		switch (key) {
			case 0x48:{									//��
				if (curShopPos->x > 0) {
					curShopPos->x -= 1;
				}
				break;
			}
			case 0x50:{									//��
				if (curShopPos->x < SHOP_ROW - 1) {
					curShopPos->x += 1;
				}
				break;
			}
			case 0x4b:{									//��
				if (curShopPos->y > 0) {
					curShopPos->y -= 1;
				}
				break;
			}
			case 0x4d:{									//��
				if (curShopPos->y < SHOP_COL - 1) {
					curShopPos->y += 1;
				}
				break;
			}
			default: break;
		}
		paint.paintSelectedShop(curShopPos->x, curShopPos->y);
		// cout << "�̵��е�λ�ã� " << *curShopPos << endl;
	} else if (keyBoardMode == MAPMODE || keyBoardMode == SHOVELMODE){
		paint.paintBlankMap(curMapPos->x, curMapPos->y);
		switch (key) {
			case 0x48:{
				if (curMapPos->x > 0) {
					curMapPos->x -= 1;
				}
				break;
			}
			case 0x50:{
				if (curMapPos->x < MAP_ROW - 1) {
					curMapPos->x += 1;
				}
				break;
			}
			case 0x4b:{
				if (curMapPos->y > 0) {
					curMapPos->y -= 1;
				}
				break;
			}
			case 0x4d:{
				if (curMapPos->y < MAP_COL - 1) {
					curMapPos->y += 1;
				}
				break;
			}
			default: break;
		}
		// paint.paintMapPos(curMapPos);
		// cout << "��ͼ�е�λ�ã� " << *curMapPos << endl;
		paint.paintSelectedMap(curMapPos->x, curMapPos->y);
	}
	
}

/**
* ���̵��й���ֲ��
*/
void Control::buyPlant() {
	if (delay[curShopPos->x * 2 + curShopPos->y] > 0){
		return;
	}
	pair<PlantType, int> plant = shop.buyPlant(curShopPos, curSunNum);
	curPlantType = plant.first;
	if (curPlantType == NONETYPE) {
		// cout << "���ⲻ��!" << endl;
		return;
	}

	curPlantCost = plant.second;										//ֲ�￪������ֲ��ȥ�Ż�ʵ�ʻ���

	curMapPos = new Point(0, 0);
	paint.paintSelectedMap(curMapPos->x, curMapPos->y);
	keyBoardMode = MAPMODE;
}

void Control::shovelPlant(){
	removePlant(curMapPos->x, curMapPos->y);

	paint.paintBlankMap(curMapPos->x, curMapPos->y);	//�������»���Ϊ��ɫ
	curMapPos = nullptr;									//��Ϊnullptr��֮ǰ��λ����Ͷ��ʹ�ã���������
	keyBoardMode = NORMALMODE;
}

/**
* ����һ��ֲ��
*/
void Control::generatePlant() {
	switch (curPlantType) {
	case SUNFLOWER:{
		curPlant = new SunFlower(0, *curMapPos, LITEYELLOW , 100);
		delay[0] = 40;
		break;
	}
	case PEASHOOTER:{
		curPlant = new PeaShooter(40, *curMapPos, GREEN, 100);
		delay[1] = 60;
		break;
	}
	case NUT: {
		curPlant = new Nut(0, *curMapPos, YELLOW, 250);
		delay[2] = 120;
		break;
	}
	case GARLIC: {
		curPlant = new Garlic(0, *curMapPos, LITEGREEN, 50);
		delay[3] = 40;
		break;
	}
	case ICEPEASHOOTER: {
		curPlant = new IcePeaShooter(30, *curMapPos, BLUE, 100);
		delay[4] = 120;
		break;
	}
	case HIGHNUT: {
		curPlant = new HighNut(0, *curMapPos, YELLOW, 400);
		delay[5] = 120;
		break;
	}
	default: break;
	}

	plantListMutex.lock();
	plantList[curMapPos->x][curMapPos->y] = curPlant;
	plantListMutex.unlock();
	
	curSunNumMutex.lock();
	curSunNum = curSunNum - curPlantCost;					//��������
	curSunNumMutex.unlock();
	paint.paintSunNum();
	gameMap.setPlant(curMapPos->x, curMapPos->y);			//��ͼ����

	paint.paintBlankMap(curMapPos->x, curMapPos->y);	//�������»���Ϊ��ɫ
	
	curMapPos = nullptr;									//��Ϊnullptr��֮ǰ��λ����Ͷ��ʹ�ã���������
	keyBoardMode = NORMALMODE;
	curPlantType = NONETYPE;

	paint.paintShop();
}

/**
 * ÿ6s����25����Ȼ��
 */
void Control::generateNaturalSun(){
	while (!gameOver) {
		Sleep(8007);
		curSunNumMutex.lock();
		curSunNum += 25;									//��������
		curSunNumMutex.unlock();
		paint.paintSunNum();
	}
}


void Control::generateZombie() {
	srand((unsigned)time(nullptr));
	while (!gameOver) {
		int wInterval = rand() % 4000 + 4000;
		Sleep(wInterval);

		int line = rand() % MAP_ROW;
		Point* point = new Point(line, MAP_COL - 1);

		int type = rand() % ZOMBIE_TYPE_NUM;
		// int type = 3;
		Zombie* zombie = getNewInstance<Zombie>(ZombieType(type), point);
		
		zombie->setArriveTime(arriveSequence[point->x][point->y]);								//���õ������

		zombieListMutex.lock();
		zombieList.push_back(zombie);
		zombieListMutex.unlock();

		arriveSequenceAdd(point->x, point->y);
		// cout << "����: " << zombie->getPoint() << ", ����" << type << endl;

		gameMap.setZombie(point->x, point->y);

	}
}

