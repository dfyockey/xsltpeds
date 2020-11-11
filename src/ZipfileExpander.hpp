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
// In constructor:
// 1. Check for zip file on command line, process and exit if found
// 2. Find latest zip file in a given directory, process, move, and exit
//
// In processing:
// 🗸1. Create a uniquely named directory (based on datestamp)
// 🗸2. unzip into the new directory
public:
	string process(string zipfile, string datestamp);
private:
	void expand(string zipfile, string targetdir);
};

#endif /* ZIPFILEEXPANDER_HPP_ */
