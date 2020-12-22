/*
 * ZipfileProcessor.cpp
 *
 *  Created on: Nov 12, 2020
 *      Author: David Yockey
 */

/*
 * For processing a zip file with a sufficiently distinctive name
 * for use naming a directory into which the zip file is expanded
 * while avoiding collisions with existing directories. Should a
 * collision occur, an exception is thrown and no damage is done.
 */

#include "ZipfileProcessor.hpp"

#include <boost/filesystem.hpp>
#include <ctime>

#include "exceptions.hpp"

namespace bfs = boost::filesystem;

string ZipfileProcessor::procLatestZipfile (string dir) {
	bfs::directory_iterator dirIndex(dir);	// Initially set at directory Start
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
		return process(latestZipfile.string());
	else
		throw file_not_found("ZipfileProcessor::procLatestZipfile", {dir});
}

string ZipfileProcessor::procZipfile (string zipfile) {
	return process(zipfile);
}
