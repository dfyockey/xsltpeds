/*
 * system_exception.hpp
 *
 *  Copyright © 2020-2021 David Yockey
 *
 *  This file is part of Xsltpeds.
 *
 *  Xsltpeds is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Xsltpeds is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Xsltpeds.  If not, see <https://www.gnu.org/licenses/>.
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
