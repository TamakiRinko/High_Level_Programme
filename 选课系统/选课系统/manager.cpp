#include"manager.h"

bool Managing::accepted(){
	string id = "admin";
	string password = "admin";
	if (manager.get_id() != id || manager.get_password() != password){
		cerr << "login error\n";
		return 0;
	}
	stu.open(student_list, ios::in | ios::out | ios::app);
	tea.open(teacher_list, ios::in | ios::out | ios::app);
	if (!stu.is_open() || !tea.is_open()){
		cerr << "file open error\n";
		return 0;
	}
	return 1;
}

void Managing::exec(){//管理员工作
	//----------------------- 登录 ----------------------------
	if (accepted() == false){
		return;
	}
	//---------------------------------------------------------
	manage_window.manage();
	char c;
	while ((c = getchar()) != 'Q'){
	//----------------------- 清屏 ----------------------------
		manage_window.manage();
	//---------------------------------------------------------
	//----------------------- 执行 ----------------------------
		switch (c){
			case 'A':	show();		break;
			case 'B':	record();	break;
			case 'C':	del();		break;
			default :	break;
		}
	}
	//---------------------------------------------------------
}

void Managing::show(){

}