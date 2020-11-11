/*
 * system_exception.hpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_


#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class system_exception : public runtime_error {
public:
	system_exception (const string& exceptLoc) : runtime_error(exceptLoc){};
};

class argument_error : public invalid_argument {
private:
	vector<string> args;
public:
	argument_error (const string& exceptLoc, initializer_list<string> l) : invalid_argument(exceptLoc), args(l) {};
	string& operator()(int i) { return args[i]; };
};

class file_error : public runtime_error {
public:
	file_error (const string& exceptLoc, string filename) : runtime_error(exceptLoc), fn(filename) {};
	string filename () { return fn; };
private:
	string fn;
};

class file_not_opened : public file_error {
	file_not_opened (const string& exceptLoc, string filename) : file_error(exceptLoc, filename) {};
};

class files_not_saved : public file_error {
	files_not_saved (const string& exceptLoc, string filename) : file_error(exceptLoc, filename) {};
};

#endif /* EXCEPTIONS_HPP_ */
