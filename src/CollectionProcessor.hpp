/*
 * CollectionProc.hpp
 *
 *  Created on: Oct 31, 2020
 *      Author: David Yockey
 */

#include <string>
#include "PedsXsltProcessor.hpp"

namespace bfs = boost::filesystem;

class CollectionProcessor : public PedsXsltProcessor {
public:
	virtual void init() = 0;
	virtual void proc(string datestamp, string xmlfilename, string newdir) = 0;
	virtual void fint() = 0;
	virtual ~CollectionProcessor(){}
};
