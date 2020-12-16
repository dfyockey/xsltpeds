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

string ZipfileProcessor::procLatestZipfile (string dir, string datestamp) {
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
		return process(latestZipfile.string(), datestamp);
	else
		throw file_not_found("ZipfileProcessor::procLatestZipfile", {dir});
}

string ZipfileProcessor::procZipfile (string zipfile, string datestamp) {
	return process(zipfile, datestamp);
}
