#include "FileReader.h"

void ExceptionHandler::process(exception& e){
	cout << e.what() << endl;
}

FileReader::FileReader(){
	lineNum = 0;
}


void FileReader::open_file(string file_path){
	int index = 0;
	for (int i = file_path.size() - 1; i >= 0; --i){
		if (file_path[i] == '/'){
			index = i;
			break;
		}
	}
	if (index == 0)	index--;
	string name = file_path.substr(index + 1);
	if (fin.is_open()){
		throw FileOpenedException("FileOpenedException: " + file_name);			//TODO:文件名！
	}
	fin.open(file_path, ios::in);
	if (!fin.is_open()){
		throw OpenFileFailureException("OpenFileFailureException: " + name);		//TODO: 文件名!
	}
	file_name = name;
	string tempStr;
	getline(fin, tempStr);
	while(!fin.fail()){
		if (tempStr != ""){
			lineNum++;
			contents.push_back(tempStr);
		}
		getline(fin, tempStr);
	}
}

void FileReader::find(string s) {
	bool flag = false;
	for (int i = 0; i < contents.size(); ++i){
		int pos = 0;
		while ((pos = contents[i].find(s, pos)) != string::npos) {
			flag = true;
			cout << i + 1 << " " << pos + 1 << endl;
			pos++;
		}
	}
	if (!flag){
		throw StringNotFoundException("StringNotFoundException: " + s);
	}
}

void FileReader::print_lines(int start, int n) {
	start = start - 1;
	if (start >= contents.size()){
		throw LineNumberExceededException("LineNumberExceededException: " + to_string(n));
	}
	if (n == 0){
		for (int i = start; i < contents.size(); ++i){
			cout << contents[i] << endl;
		}
		return;
	}
	if (start + n - 1 >= contents.size()){
		throw LineNumberExceededException("LineNumberExceededException: " + to_string(n + start - lineNum));
	}
	for (int i = start; i < start + n; ++i) {
		cout << contents[i] << endl;
	}
	return;
}

void FileReader::close_file(){
	fin.close();
	file_name = "";
}