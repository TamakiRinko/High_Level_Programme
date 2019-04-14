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
	bool accepted();	//验证登录，打开文件
	void exec();		//管理员工作
	void record();		//录入人员
	void show();		//人员查看
	void del();			//人员删除
};





#endif
