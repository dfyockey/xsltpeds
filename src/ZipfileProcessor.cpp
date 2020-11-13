/*
 * ZipfileProcessor.cpp
 *
 *  Created on: Nov 12, 2020
 *      Author: David Yockey
 */

#include "ZipfileProcessor.hpp"

#include <boost/filesystem.hpp>
#include <ctime>

#include "exceptions.hpp"

namespace bfs = boost::filesystem;

void PedsXmlZipfileProcessor::procLatestZipfile (string dir, string datestamp) {

	string linebuf(4096,'\0');	// construct string to receive a filename from f1

	bfs::directory_iterator dirIndex(dir);	// Initially set as Start
	bfs::directory_iterator dirEnd;

	time_t latest = 0;
	bfs::path latestZipfile;

	for ( /*nop*/; dirIndex != dirEnd; ++dirIndex ) {
		bfs::path p = dirIndex->path();
		if ( isZipfile(p.string()) ) {
			time_t t = boost::filesystem::last_write_time(p);
			if ( t > latest ) {
				latest = t;
				latestZipfile = p;
			}
		}
	}

	if ( latest > 0 )
		process(latestZipfile.string(), datestamp);
	else
		throw file_not_found("PedsXmlZipfileProcessor::procLatestZipfile", {dir});
}
