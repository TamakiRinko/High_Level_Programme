#include "Control.h"

int main(){
	//控制台最大化
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//隐藏控制台光标
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
// 	std::thread th1([] {threadFunc(10, '*'); });//这么蹩脚的写法是因为threadFunc需要先实例化
// 	std::thread th2([] {threadFunc(5, '#'); });
//
// 	th1.join();
// 	th2.join();
//
// 	return 0;
// }