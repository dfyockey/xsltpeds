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

class file_error : public runtime_error {
public:
	file_error (const string& exceptLoc, string filename) : runtime_error(exceptLoc), fn(filename) {};
	string filename () { return fn; };
private:
	string fn;
};

class file_not_opened : public file_error {
	string err;
public:
	file_not_opened (const string& exceptLoc, string filename, string err="") : file_error(exceptLoc, filename), err(err) {};
	string error () { return err; }
};

class file_not_found : public file_error {
private:
	vector<string> args;
public:
	file_not_found (const string& exceptLoc, initializer_list<string> l) : file_error(exceptLoc, *(l.begin()) ), args(l) {};
	string& operator()(int i) { return args[i]; };
};

class directory_error : public file_error {
public:
	directory_error (const string& exceptLoc, string filename) : file_error(exceptLoc, filename) {};
};

class directory_not_found : public file_error {
public:
	directory_not_found (const string& exceptLoc, string filename) : file_error(exceptLoc, filename) {};
};

#endif /* EXCEPTIONS_HPP_ */
