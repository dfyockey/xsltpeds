/*
 * PedsXmlZipfileProcessor.cpp
 *
 *  Created on: Dec 17, 2020
 *      Author: David Yockey
 */

#include "PedsXmlZipfileProcessor.hpp"
#include "exceptions.hpp"

void PedsXmlZipfileProcessor::run (string target, xsltranstype xtt) {
	string collection;
	const bool trash = true;

	if ( target.empty() )
		collection = procLatestZipfile( bfs::current_path().string(), trash );
	else if ( bfs::is_directory(target) )
		collection = procLatestZipfile(target);
	else if ( isZipfile(target) )
		collection = procZipfile(target);
	else
		throw file_error("PedsXmlZipfileProcessor::run", target);

	procXmlCollection(collection, xtt);
}
