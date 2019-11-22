#ifndef PLANTSVSZOMBIES_ZOMBIEREFLECTOR_H
#define PLANTSVSZOMBIES_ZOMBIEREFLECTOR_H


#include <unordered_map>
#include "Zombie.h"
using namespace std;

class ZombieFactory {
public:
	ZombieFactory();
	virtual ~ZombieFactory();
	virtual Zombie* newInstances(ZombieType zombieType, Point* point) = 0;					//核心，生成实例对象
};

class ZombieReflector {
public:
	ZombieReflector();
	~ZombieReflector();
	bool registerFactory(int typeNum, ZombieFactory* zf);
	Zombie* getNewInstance(int typeNum, Point* point);
private:
	unordered_map<int, ZombieFactory*> zombieFactories;				//核心，对象工厂与类名的映射
};

ZombieReflector& zombie_reflector();




//反射声明！利用预处理
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


//根据类名获取对象实例
//*************************************************************************
template<typename T>
T* getNewInstance(const int& typeNum, Point* point) {
	return dynamic_cast<T*>(zombie_reflector().getNewInstance(typeNum, point));
}
//*************************************************************************




#endif
