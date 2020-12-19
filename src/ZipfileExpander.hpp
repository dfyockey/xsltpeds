/*
 * ZipfileExpander.hpp
 *
 *  Created on: Nov 2, 2020
 *      Author: David Yockey
 */

#ifndef ZIPFILEEXPANDER_HPP_
#define ZIPFILEEXPANDER_HPP_

#include <string>
using namespace std;

class ZipfileExpander {
public:
	bool isZipfile (string filename);
	string process(string zipfile, string datestamp="");
private:
	void expand(string zipfile, string targetdir);
};

#endif /* ZIPFILEEXPANDER_HPP_ */
