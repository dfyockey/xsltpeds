/*
 * PedsXmlCollectionProcessor.cpp
 *
 *  Created on: Oct 28, 2020
 *      Author: David Yockey
 */

#include <iostream>

#include "PedsXmlCollectionProcessor.hpp"

PedsXmlCollectionProcessor::PedsXmlCollectionProcessor () {
	time_t t = time(0);
	char ds[256];	// Unmanaged buffer to receive the datestamp output of strftime. Dangerous stuff. Yuck.

	if (strftime(ds, sizeof(ds), "%Y%m%d-%H%M%S", localtime(&t))) {
		datestamp = ds;
	} else {

	}
}
