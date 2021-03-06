/*
 * Proco.hpp
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
#ifndef PROCO_HPP_
#define PROCO_HPP_

#include "CollectionProcessor.hpp"

class Proco : public CollectionProcessor {
public:
	Proco (string xslfile, string datestamp) : CollectionProcessor (xslfile, datestamp), bFirstFile(true) {};
   ~Proco ();
	void init (string collectiondir);
	void proc (bfs::path xmlfilepath);
	void fnit ();
private:
	string newXmlfilename;
	ofstream newXmlfile;
	bool bFirstFile;
	char linebuf[4097];	// The longest line expected should be under 1024 chars, but memory's cheap and abundant so we can afford to be profilgate. :)
};


#endif /* PROCO_HPP_ */
