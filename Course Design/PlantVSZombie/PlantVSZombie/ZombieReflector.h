#ifndef PLANTSVSZOMBIES_ZOMBIEREFLECTOR_H
#define PLANTSVSZOMBIES_ZOMBIEREFLECTOR_H


#include <unordered_map>
#include "Zombie.h"
using namespace std;

class ZombieFactory {
public:
	ZombieFactory();
	virtual ~ZombieFactory();
	virtual Zombie* newInstances(ZombieType zombieType, Point* point) = 0;					//���ģ�����ʵ������
};

class ZombieReflector {
public:
	ZombieReflector();
	~ZombieReflector();
	bool registerFactory(int typeNum, ZombieFactory* zf);
	Zombie* getNewInstance(int typeNum, Point* point);
private:
	unordered_map<int, ZombieFactory*> zombieFactories;				//���ģ����󹤳���������ӳ��
};

ZombieReflector& zombie_reflector();




//��������������Ԥ����
//***********************************************************************
#define ZOMBIEREFLECT(name, typeNum)\
class ZombieFactory_##name : public ZombieFactory{\
public:\
    ZombieFactory_##name(){}\
    virtual ~ZombieFactory_##name(){}\
    Zombie* newInstances(ZombieType zombieType, Point* point){\
        return new name(zombieType, point); \
    }\
};\
class Register_##name{\
public:\
    Register_##name(){\
        zombie_reflector().registerFactory(typeNum, new ZombieFactory_##name()); \
    }\
};\
Register_##name register_##name;
//************************************************************************


//����������ȡ����ʵ��
//*************************************************************************
template<typename T>
T* getNewInstance(const int& typeNum, Point* point) {
	return dynamic_cast<T*>(zombie_reflector().getNewInstance(typeNum, point));
}
//*************************************************************************




#endif
