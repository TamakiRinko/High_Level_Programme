#include "Control.h"

int main(){
	//����̨���
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//���ؿ���̨���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(handle, &CursorInfo);
	
	Control* control = new Control();
	control->start();
	return 0;
}




// #include<thread>
// #include<iostream>
// #include<mutex>
// #include<vector>
// #include<iterator>
//
//
// std::mutex g_mutex;
//
//
// void doThreadFunc(int n, char c) {
// 	g_mutex.lock();
//
// 	std::vector<int> vec(n, c);
// 	std::copy(vec.begin(), vec.end(), std::ostream_iterator<char>(std::cout, ""));
// 	std::cout << std::endl;
//
// 	g_mutex.unlock();
// }
//
//
// template<typename ... Args >
// void threadFunc(Args&& ... args) {
// 	try {
// 		doThreadFunc(std::forward<Args>(args)...);
// 	}
// 	catch (...) {
// 	}
// }
//
//
//
//
// int main() {
// 	
// 	std::thread th1([] {threadFunc(10, '*'); });//��ô���ŵ�д������ΪthreadFunc��Ҫ��ʵ����
// 	std::thread th2([] {threadFunc(5, '#'); });
//
// 	th1.join();
// 	th2.join();
//
// 	return 0;
// }