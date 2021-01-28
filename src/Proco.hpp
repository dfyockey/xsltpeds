/*
 * Proco.hpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
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
