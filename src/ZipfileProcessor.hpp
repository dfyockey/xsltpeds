/*
 * ZipfileProcessor.hpp
 *
 *  Created on: Nov 12, 2020
 *      Author: David Yockey
 */

#ifndef ZIPFILEPROCESSOR_HPP_
#define ZIPFILEPROCESSOR_HPP_


#include "ZipfileExpander.hpp"

class ZipfileProcessor : private ZipfileExpander {
public:
	string procLatestZipfile (string dir, string datestamp);
	string procZipfile (string zipfile, string datestamp);
};


#endif /* ZIPFILEPROCESSOR_HPP_ */
