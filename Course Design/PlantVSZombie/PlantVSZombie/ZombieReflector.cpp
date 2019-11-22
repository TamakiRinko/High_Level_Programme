#include "ZombieReflector.h"


ZombieFactory::ZombieFactory(){}
ZombieFactory::~ZombieFactory(){}

ZombieReflector::ZombieReflector() {
}


ZombieReflector::~ZombieReflector() {
	unordered_map<int, ZombieFactory*>::iterator it = zombieFactories.begin();
	for (; it != zombieFactories.end(); ++it){
		delete it->second;
	}
	zombieFactories.clear();
}

bool ZombieReflector::registerFactory(int typeNum, ZombieFactory* zf) {
	if (zf == nullptr)	return false;
	return zombieFactories.insert(make_pair(typeNum, zf)).second;
}

Zombie* ZombieReflector::getNewInstance(int typeNum, Point* point) {
	unordered_map<int, ZombieFactory*>::iterator it = zombieFactories.find(typeNum);
	if (it != zombieFactories.end()){
		return it->second->newInstances(ZombieType(typeNum), point);
	}
	return nullptr;
}

ZombieReflector& zombie_reflector(){
	static ZombieReflector zombieReflector;
	return zombieReflector;
}
