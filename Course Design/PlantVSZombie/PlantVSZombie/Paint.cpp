#include "Paint.h"

extern int curSunNum;														//ȫ��������
extern Shop shop;															//ȫ���̵�
extern Plant* plantList[MAP_ROW][MAP_COL];									//���ڵ�ֲ���б���άָ������
extern vector<Zombie* > zombieList;											//���ڵĽ�ʬ�б�
extern unordered_set<Bullet* > bulletList;									//���ڵ��ӵ��б�
extern bool gameOver;														//��Ϸ����
extern int curScore;														//�ܷ���
extern int delay[];

Paint::Paint() {
}


Paint::~Paint() {
}

void Paint::paintBoarder(){
	for (int i = 0; i < MAP_ROW * 9 + 1; ++i){
		if (i % 9 == 0){
			for (int j = 0; j < MAP_COL * 16 + 1; ++j) {
				cout << "*";
			}
		}else{
			for (int j = 0; j < MAP_COL * 16 + 1; ++j){
				if (j % 16 == 0){
					cout << "*";
				} else{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void Paint::paintShop(){
	COORD coord;
	coord.Y = MAP_ROW * 9 + 1;
	coord.X = 0;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "[�̵�]" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < shop.getRow(); ++i){
		for (int j = 0; j < shop.getCol(); ++j){
			pair<PlantType, int>* p = shop.getGoods(i, j);
			switch (p->first){
				case SUNFLOWER: {
					cout << "���տ�: ";
					cout << p->second << ": " << delay[0] / 20 << "\t\t\t";
					break;
				}
				case PEASHOOTER: {
					cout << "�㶹����: ";
					cout << p->second << ": " << delay[1] / 20 << "\t\t\t";
					break;
				}
				case NUT: {
					cout << "���: ";
					cout << p->second << ": " << delay[2] / 20 << "\t\t\t";
					break;
				}
				case GARLIC: {
					cout << "����: ";
					cout << p->second << ": " << delay[3] / 20 << "\t\t\t";
					break;
				}
				case ICEPEASHOOTER: {
					cout << "��������: ";
					cout << p->second << ": " << delay[4] / 20 << "\t\t\t";
					break;
				}
				case HIGHNUT: {
					cout << "�߼��: ";
					cout << p->second << ": " << delay[5] / 20 << "\t\t\t";
					break;
				}
				default: break;
			}
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;
	paintMutex.unlock();
}

void Paint::paintSelectedShop(int r, int c){
	COORD coord;
	coord.Y = MAP_ROW * 9 + 1;
	coord.X = 0;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "[�̵�]" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for (int i = 0; i < shop.getRow(); ++i) {
		for (int j = 0; j < shop.getCol(); ++j) {
			if (i == r && j == c){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			}
			pair<PlantType, int>* p = shop.getGoods(i, j);
			switch (p->first) {
			case SUNFLOWER: {
				cout << "���տ�: ";
				cout << p->second << ": " << delay[0] / 20 << "\t\t\t";
				break;
			}
			case PEASHOOTER: {
				cout << "�㶹����: ";
				cout << p->second << ": " << delay[1] / 20 << "\t\t\t";
				break;
			}
			case NUT: {
				cout << "���: ";
				cout << p->second << ": " << delay[2] / 20 << "\t\t\t";
				break;
			}
			case GARLIC: {
				cout << "����: ";
				cout << p->second << ": " << delay[3] / 20 << "\t\t\t";
				break;
			}
			case ICEPEASHOOTER: {
				cout << "��������: ";
				cout << p->second << ": " << delay[4] / 20 << "\t\t\t";
				break;
			}
			case HIGHNUT: {
				cout << "�߼��: ";
				cout << p->second << ": " << delay[5] / 20 << "\t\t\t";
				break;
			}
			default: break;
			}
			if (i == r && j == c){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
					FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;
	paintMutex.unlock();
}

void Paint::paintSelectedMap(int r, int c){
	paintMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	COORD coord;
	coord.Y = r * 9;
	coord.X = c * 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 17; ++i){
		cout << "*";
	}
	for (int i = 1; i < 9; ++i){
		coord.Y = r * 9 + i;
		coord.X = c * 16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		cout << "*";
		coord.Y = r * 9 + i;
		coord.X = c * 16 + 16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		cout << "*";
	}
	coord.Y = (r + 1) * 9;
	coord.X = c * 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 17; ++i) {
		cout << "*";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);
	paintMutex.unlock();
}

void Paint::paintObject(){
	for (int i = 0; i < MAP_ROW; ++i) {
		for (int j = 0; j < MAP_COL; ++j) {
			if (plantList[i][j] != nullptr) {
				paintMutex.lock();
				plantList[i][j]->draw();
				paintMutex.unlock();
			}
		}
	}
	for (int i = 0; i < zombieList.size(); ++i) {
			paintMutex.lock();
			zombieList[i]->draw();
			paintMutex.unlock();
	}
	for (auto it = bulletList.begin(); it != bulletList.end(); ++it){
			paintMutex.lock();
			(*it)->draw();
			paintMutex.unlock();
	}
}

void Paint::paintBlank(int r, int c){
	COORD coord;
	coord.X = c * 16 + 1;
	coord.Y = r * 9 + 4;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 15; ++i){
		cout << " ";
	}
	coord.X = c * 16 + 1;
	coord.Y = r * 9 + 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 15; ++i) {
		cout << " ";
	}
	paintMutex.unlock();
}

void Paint::paintString(int r, int c, string str){
	COORD coord;
	coord.X = c * 16 + 3;
	coord.Y = r * 9 + 4;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << str << endl;
	paintMutex.unlock();
}

void Paint::paintGameOver(){
	COORD coord;
	coord.Y = MAP_ROW * 9 + 7;
	coord.X = 0;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "GameOver!" << endl;
	paintMutex.unlock();
}

void Paint::paintMapPos(Point* mapPos){
	COORD coord;
	coord.Y = MAP_ROW * 9 + 5;
	coord.X = 0;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "��ͼ�е�λ�ã� " << *mapPos << endl;
	paintMutex.unlock();
}

void Paint::paintBlankBullet(int r, int c){
	COORD coord;
	coord.Y = r;
	coord.X = c;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "  ";
	paintMutex.unlock();
}

void Paint::paintBlankMap(int r, int c){
	paintMutex.lock();
	COORD coord;
	coord.Y = r * 9;
	coord.X = c * 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 17; ++i) {
		cout << "*";
	}
	for (int i = 1; i < 9; ++i) {
		coord.Y = r * 9 + i;
		coord.X = c * 16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		cout << "*";
		coord.Y = r * 9 + i;
		coord.X = c * 16 + 16;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		cout << "*";
	}
	coord.Y = (r + 1) * 9;
	coord.X = c * 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 17; ++i) {
		cout << "*";
	}
	paintMutex.unlock();
}

void Paint::paintSunNum(){
	COORD coord;
	coord.Y = MAP_ROW * 9 + 1;
	coord.X = 80;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 16; ++i){
		cout << " ";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "���������� " << curSunNum;
	paintMutex.unlock();
}

void Paint::paintScore(){
	COORD coord;
	coord.Y = MAP_ROW * 9 + 1;
	coord.X = 100 ;
	paintMutex.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < 16; ++i) {
		cout << " ";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "������ " << curScore;
	paintMutex.unlock();
}

