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

namespace bfs = boost::filesystem;

PedsXmlCollectionProcessor::PedsXmlCollectionProcessor () {
	collproc = 0;
}

void PedsXmlCollectionProcessor::process (string collectiondir, xsltranstype xtt) {

	generate_datestamp();
	newdir = string("pairbulk-") + datestamp;
	bfs::create_directory(newdir);

	switch (xtt) {
	case all:
		collproc = &proca;
		break;
	case folder:
		//collproc = &procf;
		break;
	case one:
		//collproc = &proco;
		break;
	}

	bfs::directory_iterator dirIndex(collectiondir);	// Initially set as Start
	bfs::directory_iterator dirEnd;

	for ( /*nop*/; dirIndex != dirEnd; ++dirIndex ) {
		bfs::path p = dirIndex->path();
		if (p.extension() == ".xml") {
			collproc->proc(datestamp, p.filename().string(), newdir);
		}
	}
}

void PedsXmlCollectionProcessor::generate_datestamp () {
	time_t t = time(0);
	char ds[256];	// Unmanaged buffer to receive the datestamp output of strftime. Dangerous stuff. Yuck.

	if (strftime(ds, sizeof(ds), "%Y%m%d-%H%M%S", localtime(&t)))
		datestamp = ds;
	else
		throw system_exception("PedsXmlCollectionProcessor::generate_datestamp");
}
