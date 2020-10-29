/*
 * PedsXmlCollectionProcessor.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#ifndef PEDSXMLCOLLECTIONPROCESSOR_HPP_
#define PEDSXMLCOLLECTIONPROCESSOR_HPP_

#include <string>
#include "PedsXsltProcessor.hpp"

using namespace std;

class PedsXmlCollectionProcessor : PedsXsltProcessor {
	//
private:
	string datestamp;
	string newdir;
	//
public:
	PedsXmlCollectionProcessor ();
};

#endif /* PEDSXMLCOLLECTIONPROCESSOR_HPP_ */
