/*
 * ZipfileProcessor.hpp
 *
 *  Created on: Nov 12, 2020
 *      Author: David Yockey
 */

/*
 * For processing a zip file with a sufficiently distinctive name
 * for use naming a directory into which the zip file is expanded
 * while avoiding collisions with existing directories. Should a
 * collision occur, an exception is thrown and no damage is done.
 */

#ifndef ZIPFILEPROCESSOR_HPP_
#define ZIPFILEPROCESSOR_HPP_


#include "ZipfileExpander.hpp"

class ZipfileProcessor : protected ZipfileExpander {
public:
	string procLatestZipfile (string dir);
	string procZipfile (string zipfile);
};


#endif /* ZIPFILEPROCESSOR_HPP_ */
