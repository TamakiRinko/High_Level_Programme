#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"window.h"

class Manager{
private:
	string id;
	string password;
public:
	Manager(string ID, string PASSWORD) : id(ID), password(PASSWORD){}
	Manager(Manager& manager){
		id = manager.id;
		password = manager.password;
	}
	string get_id(){ return id; }
	string get_password(){ return password; }
};

class Managing{
private:
	Manager manager;
	char* student_list;
	char* teacher_list;
	fstream stu;
	fstream tea;
	Window manage_window;
public:
	Managing(Manager mana, char* sstr = "student.txt", char* tstr = "teacher.txt"): manager(mana) {
		strcpy(student_list, sstr);
		strcpy(teacher_list, tstr);
	}
	bool accepted();	//��֤��¼�����ļ�
	void exec();		//����Ա����
	void record();		//¼����Ա
	void show();		//��Ա�鿴
	void del();			//��Աɾ��
};





#endif
