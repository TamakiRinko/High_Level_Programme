//
// Created by rinko on 2019/11/11.
//

#include "Control.h"

Map gameMap(MAP_ROW, MAP_COL);										//全局地图
Shop shop(SHOP_ROW, SHOP_COL);										//全局商店
vector<Zombie* > zombieList;										//存在的僵尸列表
Plant* plantList[MAP_ROW][MAP_COL];									//存在的植物列表，二维指针数组
unordered_set<Bullet* > bulletList;									//存在的子弹列表
mutex curSunNumMutex;												//全局阳光数的互斥锁
mutex zombieListMutex;												//僵尸列表互斥锁
mutex plantListMutex;												//植物列表互斥锁
bool gameOver;														//游戏结束
int curSunNum;														//全局阳光数
int arriveSequence[MAP_ROW][MAP_COL];								//僵尸到达某点的次序
mutex arriveSequenceMutex[MAP_ROW][MAP_COL];						//arriveSequence的锁
Paint paint;														//画笔
int curScore;														//得分

int delay[6] = { 0 };


void arriveSequenceAdd(int x, int y){
	arriveSequenceMutex[x][y].lock();
	arriveSequence[x][y]++;
	arriveSequenceMutex[x][y].unlock();
}

/**
 * 删除一个植物
 */
void removePlant(int x, int y){
	plantListMutex.lock();
	delete plantList[x][y];
	plantList[x][y] = nullptr;
	plantListMutex.unlock();
	paint.paintBlank(x, y);			//重置为空白
	gameMap.reset(x, y);				//地图设置
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
		if (_kbhit()) {												//检测键盘按下操作
			char key = (char)_getch();								//并发获取，会将按下的按键存储起来
			if ((int)key == -32)	continue;						//上下左右键会返回两次，第一次为-32
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
	for (auto it = bulletList.begin(); it != bulletList.end(); ) {				//删除子弹
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
	
	for (auto it = zombieList.begin(); it != zombieList.end();) {				//删除僵尸
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
 * 模式按键检测(b, x, 回车 返回true)
 */
bool Control::modeCapture(char key) {
	bool flag = false;
	switch (key){
		case 'b':{
			if (keyBoardMode == NORMALMODE){
				keyBoardMode = SHOPMODE;
				curShopPos = new Point(0, 0);
				paint.paintSelectedShop(curShopPos->x, curShopPos->y);
				// cout << "商店中的位置： " << *curShopPos << endl;
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
			if (keyBoardMode == MAPMODE){					//选择种植位置模式，退回到选择植物模式
				keyBoardMode = SHOPMODE;
				curPlantType = NONETYPE;
				paint.paintBlankMap(curMapPos->x, curMapPos->y);		//将当前位置颜色清空
				if (curMapPos != nullptr){
					delete curMapPos;
					curMapPos = nullptr;
				}
				paint.paintSelectedShop(curShopPos->x, curShopPos->y);
			} else if (keyBoardMode == SHOPMODE){			//选择植物模式，退回到未选择模式
				keyBoardMode = NORMALMODE;
				if (curShopPos != nullptr){
					delete curShopPos;
					curShopPos = nullptr;
				}
				paint.paintShop();
			} else if (keyBoardMode == SHOVELMODE){			//铲子模式，取消即可
				keyBoardMode = NORMALMODE;
				paint.paintBlankMap(curMapPos->x, curMapPos->y);
			}
			flag = true;
			break;
		}
		case 13:{												//回车键
			if (keyBoardMode == SHOPMODE){						//选择植物
				buyPlant();
			} else if (keyBoardMode == MAPMODE){				//选择位置，种植植物
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
 * 上下左右检测
 */
void Control::keyCapture(char key){
	if (keyBoardMode == SHOPMODE){
		switch (key) {
			case 0x48:{									//上
				if (curShopPos->x > 0) {
					curShopPos->x -= 1;
				}
				break;
			}
			case 0x50:{									//下
				if (curShopPos->x < SHOP_ROW - 1) {
					curShopPos->x += 1;
				}
				break;
			}
			case 0x4b:{									//左
				if (curShopPos->y > 0) {
					curShopPos->y -= 1;
				}
				break;
			}
			case 0x4d:{									//右
				if (curShopPos->y < SHOP_COL - 1) {
					curShopPos->y += 1;
				}
				break;
			}
			default: break;
		}
		paint.paintSelectedShop(curShopPos->x, curShopPos->y);
		// cout << "商店中的位置： " << *curShopPos << endl;
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
		// cout << "地图中的位置： " << *curMapPos << endl;
		paint.paintSelectedMap(curMapPos->x, curMapPos->y);
	}
	
}

/**
* 在商店中购买植物
*/
void Control::buyPlant() {
	if (delay[curShopPos->x * 2 + curShopPos->y] > 0){
		return;
	}
	pair<PlantType, int> plant = shop.buyPlant(curShopPos, curSunNum);
	curPlantType = plant.first;
	if (curPlantType == NONETYPE) {
		// cout << "阳光不足!" << endl;
		return;
	}

	curPlantCost = plant.second;										//植物开销，种植下去才会实际花费

	curMapPos = new Point(0, 0);
	paint.paintSelectedMap(curMapPos->x, curMapPos->y);
	keyBoardMode = MAPMODE;
}

void Control::shovelPlant(){
	removePlant(curMapPos->x, curMapPos->y);

	paint.paintBlankMap(curMapPos->x, curMapPos->y);	//格子重新绘制为白色
	curMapPos = nullptr;									//置为nullptr，之前的位置已投入使用，无需析构
	keyBoardMode = NORMALMODE;
}

/**
* 生成一个植物
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
	curSunNum = curSunNum - curPlantCost;					//花费阳光
	curSunNumMutex.unlock();
	paint.paintSunNum();
	gameMap.setPlant(curMapPos->x, curMapPos->y);			//地图设置

	paint.paintBlankMap(curMapPos->x, curMapPos->y);	//格子重新绘制为白色
	
	curMapPos = nullptr;									//置为nullptr，之前的位置已投入使用，无需析构
	keyBoardMode = NORMALMODE;
	curPlantType = NONETYPE;

	paint.paintShop();
}

/**
 * 每6s产生25个自然光
 */
void Control::generateNaturalSun(){
	while (!gameOver) {
		Sleep(8007);
		curSunNumMutex.lock();
		curSunNum += 25;									//阳光增加
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
		
		zombie->setArriveTime(arriveSequence[point->x][point->y]);								//设置到达次序

		zombieListMutex.lock();
		zombieList.push_back(zombie);
		zombieListMutex.unlock();

		arriveSequenceAdd(point->x, point->y);
		// cout << "坐标: " << zombie->getPoint() << ", 类型" << type << endl;

		gameMap.setZombie(point->x, point->y);

	}
}

