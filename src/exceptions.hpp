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

class file_not_found : public invalid_argument {
private:
	vector<string> args;
public:
	file_not_found (const string& exceptLoc, initializer_list<string> l) : invalid_argument(exceptLoc), args(l) {};
	string& operator()(int i) { return args[i]; };
};

#endif /* EXCEPTIONS_HPP_ */
