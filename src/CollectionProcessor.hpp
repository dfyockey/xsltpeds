/*
 * CollectionProcessor.hpp
 *
 *  Copyright © 2020-2021 David Yockey
 *
 *  This file is part of Xsltpeds.
 *
 *  Xsltpeds is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Xsltpeds is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Xsltpeds.  If not, see <https://www.gnu.org/licenses/>.
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
