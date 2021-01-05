/*
 * CollectionProcessor.hpp
 *
 *  Created on: Oct 31, 2020
 *      Author: David Yockey
 */

#ifndef COLLECTIONPROCESSOR_HPP_
#define COLLECTIONPROCESSOR_HPP_

#include <boost/filesystem.hpp>
#include <string>
#include "PedsXsltProcessor.hpp"

namespace bfs = boost::filesystem;

class CollectionProcessor : public PedsXsltProcessor {
public:
	CollectionProcessor (string xslfile, string datestamp) : PedsXsltProcessor(xslfile), datestamp(datestamp) {}
	virtual void init (string collectiondir) {this->collectiondir = collectiondir;};
	virtual void proc(bfs::path xmlfilename) = 0;
	virtual void fnit() = 0;
	virtual ~CollectionProcessor(){}
protected:
	string collectiondir;
	string datestamp;
};

#endif /* COLLECTIONPROCESSOR_HPP_ */
