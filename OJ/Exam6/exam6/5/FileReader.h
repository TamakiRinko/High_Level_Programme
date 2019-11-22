#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class OpenFileFailureException : public exception{
private:
	string msg;
public:
	OpenFileFailureException(string m) {
		msg = m;
	}
	~OpenFileFailureException() throw () {}

	const char* what() const throw () {
		return msg.c_str();
	}
};

class FileOpenedException : public exception {
private:
	string msg;
public:
	FileOpenedException(string m) {
		msg = m;
	}
	~FileOpenedException() throw () {}

	const char* what() const throw () {
		return msg.c_str();
	}
};

class LineNumberExceededException : public exception {
private:
	string msg;
public:
	LineNumberExceededException(string m) {
		msg = m;
	}
	~LineNumberExceededException() throw () {}

	const char* what() const throw () {
		return msg.c_str();
	}
};

class StringNotFoundException : public exception {
private:
	string msg;
public:
	StringNotFoundException(string m) {
		msg = m;
	}
	~StringNotFoundException() throw () {}

	const char* what() const throw () {
		return msg.c_str();
	}
};

class ExceptionHandler{
public:
	void process(exception& e);
};


class FileReader{
private:
	ifstream fin;
	string file_name;
	vector<string> contents;
	int lineNum;
public:
	FileReader();
	void open_file(string file_path);
	void print_lines(int start, int n);
	void find(string s);
	void close_file();
};