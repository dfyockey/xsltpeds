/*
 * PedsXmlCollectionProcessor.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#ifndef PEDSXMLCOLLECTIONPROCESSOR_HPP_
#define PEDSXMLCOLLECTIONPROCESSOR_HPP_

#include "CollectionProcessor.hpp"

using namespace std;

enum xsltranstype {all, folder, one};


class PedsXmlCollectionProcessor {
//
private:
	string datestamp;
	string newdir;
	void generate_datestamp ();

	CollectionProcessor *collproc;

	//Proca proca;
	//Procf procf;
	//Proco proco;
//
public:
	PedsXmlCollectionProcessor ();
	void procXmlCollection(string collectiondir, xsltranstype xtt);
//
};

#endif /* PEDSXMLCOLLECTIONPROCESSOR_HPP_ */
