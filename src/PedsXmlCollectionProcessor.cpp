/*
 * PedsXmlCollectionProcessor.cpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#define _CRT_SECURE_NO_WARNINGS		// Prevent Microsoft VC++ from complaining about use of `localtime()`

#include "PedsXmlCollectionProcessor.hpp"

#include <ctime>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "exceptions.hpp"
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

	bfs::exists(collectiondir);	// throws filesystem_error if nonexistent

	collproc->init(collectiondir);

//	collproc->proc()
	{
		std::vector<bfs::path> xmlfilepaths;

		bfs::directory_iterator dirIndex(collectiondir);	// Initially set as dirStart
		bfs::directory_iterator dirEnd;

		for ( /*nop*/; dirIndex != dirEnd; ++dirIndex ) {
			bfs::path p = dirIndex->path();
			if (p.extension() == ".xml") {
				xmlfilepaths.push_back(p);
			}
		}

		sort (xmlfilepaths.begin(), xmlfilepaths.end(), greater<bfs::path>());

		for (std::vector<bfs::path>::const_iterator i = xmlfilepaths.begin(); i != xmlfilepaths.end(); ++i)
			collproc->proc(*i);
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
