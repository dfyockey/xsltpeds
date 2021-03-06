/*
 * PedsXmlZipfileProcessor.cpp
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

#include "PedsXmlZipfileProcessor.hpp"
#include "exceptions.hpp"

void PedsXmlZipfileProcessor::run (string target, xsltranstype xtt) {
	string collection;
	const bool trash = true;

	if ( target.empty() )
		collection = procLatestZipfile( bfs::current_path().string(), trash );
//	else if ( bfs::is_directory(target) ) {
		// Process all zipfiles in the specified directory...
//	}
	else
		if ( bfs::exists(target) ) {
			if ( isZipfile(target) )
				collection = procZipfile(target);
			else
				throw file_error("PedsXmlZipfileProcessor::run", target);
		}
		else
			throw file_not_found("PedsXmlZipfileProcessor::run", {target});

	procXmlCollection(collection, xtt);
}
