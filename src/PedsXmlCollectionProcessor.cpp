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

PedsXmlCollectionProcessor::PedsXmlCollectionProcessor () : PedsXsltProcessor () {
	time_t t = time(0);
	char ds[256];	// Unmanaged buffer to receive the datestamp output of strftime. Dangerous stuff. Yuck.

	if (strftime(ds, sizeof(ds), "%Y%m%d-%H%M%S", localtime(&t))) {
		datestamp = ds;
		newdir = string("pairbulk-") + datestamp;
		boost::filesystem::create_directory(newdir);
	} else {
		throw system_exception("PedsXmlCollectionProcessor::PedsXmlCollectionProcessor");
	}
}
