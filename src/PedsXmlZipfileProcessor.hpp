/*
 * PedsXmlZipfileProcessor.h
 *
 *  Created on: Dec 17, 2020
 *      Author: David Yockey
 */

#ifndef PEDSXMLZIPFILEPROCESSOR_HPP_
#define PEDSXMLZIPFILEPROCESSOR_HPP_

#include "PedsXmlCollectionProcessor.hpp"
#include "ZipfileProcessor.hpp"

class PedsXmlZipfileProcessor: protected PedsXmlCollectionProcessor, protected ZipfileProcessor {
public:
	void run (string target, xsltranstype xtt);
};

#endif /* PEDSXMLZIPFILEPROCESSOR_HPP_ */
