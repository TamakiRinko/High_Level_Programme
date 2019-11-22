#include "FileReader.h"

int main(){
	string path_prefix;
	path_prefix = "./";
	try {
		FileReader reader;
		reader.open_file(path_prefix + "sample_text.txt");
		reader.find("has");
		reader.print_lines(16, 4);
	} catch(OpenFileFailureException& e) {
		ExceptionHandler handler;
		handler.process(e);
	} catch(StringNotFoundException& e) {
		ExceptionHandler handler;
		handler.process(e);
	} catch(LineNumberExceededException& e) {
		ExceptionHandler handler;
		handler.process(e);
	} catch (FileOpenedException& e){
		ExceptionHandler handler;
		handler.process(e);
	}
	try{
		FileReader reader;
		reader.open_file(path_prefix + "sample_text.txt");
		reader.print_lines(1, 10000);
	} catch(LineNumberExceededException& e) {
		ExceptionHandler handler;
		handler.process(e);
	}
}