/*
 * ZipfileProcessor.hpp
 *
 *  Created on: Nov 12, 2020
 *      Author: David Yockey
 */

#ifndef ZIPFILEPROCESSOR_HPP_
#define ZIPFILEPROCESSOR_HPP_

#include "ZipfileExpander.hpp"

//
// 1. Method to find latest zip file in a given directory and process
//		1.1 If given directory is current directory, move zip file to zipTrash
// 2. Method to check a passed file: is zip file, process
//

class PedsXmlZipfileProcessor : private ZipfileExpander {
public:
	void procLatestZipfile (string dir, string datestamp);
	void procZipfile (string zipfile);
//private:
//	ZipfileExpander zipfileExpander;
};



#endif /* ZIPFILEPROCESSOR_HPP_ */
