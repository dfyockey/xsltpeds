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
private:
	string datestamp;
	string newdir;
	void generate_datestamp ();

	bfs::path xslfile;
	CollectionProcessor *collproc;
public:
	PedsXmlCollectionProcessor (bfs::path xslfile);
	void procXmlCollection(string collectiondir, xsltranstype xtt);
};

#endif /* PEDSXMLCOLLECTIONPROCESSOR_HPP_ */
