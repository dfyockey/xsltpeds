/*
 * ZipfileProcessor.cpp
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

string ZipfileProcessor::procLatestZipfile (string dir, bool trash) {
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

	if ( latest > 0 ) {
		string newdir = process(latestZipfile.string());

		if (trash) {
			bfs::path ziptrash = ( bfs::current_path() /= "ziptrash" );
			if ( !exists(ziptrash) )
				bfs::create_directory(ziptrash);
			bfs::rename(latestZipfile, ( ziptrash /= bfs::path(latestZipfile).filename() ));
		}

		return newdir;
	}
	else
		throw file_not_found("ZipfileProcessor::procLatestZipfile", {dir});
}

string ZipfileProcessor::procZipfile (string zipfile) {
	return process(zipfile);
}
