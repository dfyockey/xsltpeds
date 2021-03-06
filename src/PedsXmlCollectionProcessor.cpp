/*
 * PedsXmlCollectionProcessor.cpp
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

PedsXmlCollectionProcessor::PedsXmlCollectionProcessor (bfs::path xslfile) : xslfile(xslfile) {
	collproc = 0;
}

PedsXmlCollectionProcessor::~PedsXmlCollectionProcessor () {
	if (collproc){
		delete collproc;
		collproc = 0;
	}
}

void PedsXmlCollectionProcessor::procXmlCollection (string collectiondir, xsltranstype xtt) {

	/*
	 * WARNING! Objects proca and proco used in this method automatically
	 *          remove the collectiondir directory in their fnit() methods!
	 */

	if ( !bfs::exists(collectiondir) )
		throw directory_not_found("PedsXmlCollectionProcessor::procXmlCollection", collectiondir);

	generate_datestamp();

	switch (xtt) {
	case all:
		collproc = new Proca(xslfile.string(), datestamp); //&proca;
		break;
	case folder:
		collproc = new Procf(xslfile.string(), datestamp); //&procf;
		break;
	case one:
		collproc = new Proco(xslfile.string(), datestamp); //&proco;
		break;
	}

	collproc->init(collectiondir);

//	collproc->proc() processing...
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

		sort (xmlfilepaths.begin(), xmlfilepaths.end(), less<bfs::path>());

		cout << endl << "Processing " << xmlfilepaths.size() << " XML files... " << flush;
		for (std::vector<bfs::path>::const_iterator i = xmlfilepaths.begin(); i != xmlfilepaths.end(); ++i) {
			cout << "*" << flush;
			collproc->proc(*i);
		}
		cout << " ... Done." << endl << endl;
	}

	collproc->fnit();

	delete collproc;
	collproc = 0;

	// If the collproc->fnit() leaves collectiondir (i.e. when xtt = folder), then
	// append the datestamp to collectiondir's name to prevent future name collisions
	if ( bfs::exists(collectiondir) )
		bfs::rename(collectiondir, ( bfs::path(collectiondir).string() + "-" + datestamp ) );
}

void PedsXmlCollectionProcessor::generate_datestamp () {
	time_t t = time(0);
	char ds[256];	// Unmanaged buffer to receive the datestamp output of strftime. Dangerous stuff. Yuck.

	if (strftime(ds, sizeof(ds), "%Y%m%d-%H%M%S", localtime(&t)))
		datestamp = ds;
	else
		throw system_exception("PedsXmlCollectionProcessor::generate_datestamp");
}
