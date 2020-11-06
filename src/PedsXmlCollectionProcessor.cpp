/*
 * PedsXmlCollectionProcessor.cpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#include <ctime>
#include <boost/filesystem.hpp>
#include <iostream>
#include "PedsXmlCollectionProcessor.hpp"
#include "exceptions.hpp"

#include <string>
#include "Proca.hpp"
#include "Procf.hpp"
#include "Proco.hpp"

namespace bfs = boost::filesystem;

PedsXmlCollectionProcessor::PedsXmlCollectionProcessor () {
	collproc = 0;
}

void PedsXmlCollectionProcessor::process (string collectiondir, xsltranstype xtt) {

	/*
	 * WARNING! Objects proca and proco used in this method automatically
	 *          remove the collectiondir directory in their fnit() methods!
	 */

	generate_datestamp();

	switch (xtt) {
	case all:
		collproc = new Proca(datestamp); //&proca;
		break;
	case folder:
		collproc = new Procf(datestamp); //&procf;
		break;
	case one:
		collproc = new Proco(datestamp); //&proco;
		break;
	}

	collproc->init(collectiondir);

	bfs::directory_iterator dirIndex(collectiondir);	// Initially set as Start
	bfs::directory_iterator dirEnd;

	for ( /*nop*/; dirIndex != dirEnd; ++dirIndex ) {
		bfs::path p = dirIndex->path();
		if (p.extension() == ".xml") {
			collproc->proc(p);
		}
	}

	collproc->fnit();

	delete collproc;
	collproc = 0;
}

void PedsXmlCollectionProcessor::generate_datestamp () {
	time_t t = time(0);
	char ds[256];	// Unmanaged buffer to receive the datestamp output of strftime. Dangerous stuff. Yuck.

	if (strftime(ds, sizeof(ds), "%Y%m%d-%H%M%S", localtime(&t)))
		datestamp = ds;
	else
		throw system_exception("PedsXmlCollectionProcessor::generate_datestamp");
}
