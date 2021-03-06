/*
 * Proco.cpp
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

#include "Proco.hpp"

#include <iostream>
#include <regex>

void Proco::init (string collectiondir) {
	CollectionProcessor::init(collectiondir);
	newXmlfilename = collectiondir + ".xml";
	bFirstFile = true;

	// Create an new empty file in which to construct one combined Xml file
	// (Equivalent to `touch` shell command)
	newXmlfile.open(newXmlfilename, ios_base::out | ios_base::trunc);
	newXmlfile.close();

	// Reopen new empty file for appending
	newXmlfile.open(newXmlfilename, ios_base::out | ios_base::app);
}

void Proco::proc (bfs::path xmlfilepath) {
	regex rxXmlTag( "^<?xml.*", regex::basic );
	regex rxPatBulkData( "^<uspat:PatentBulkData.*", regex::basic );
	regex rxPatBulkDataEnd( "^</uspat:PatentBulkData.*", regex::basic );

	ifstream xmlfile( xmlfilepath.string() );

	while (xmlfile.getline(linebuf, 4096)) {
		if(!bFirstFile) {
			// Exclude xml tags read from later files
			if ( regex_match(linebuf, rxXmlTag) )
				continue;

			// Separate the first uspat:PatentData tag from the opening uspat:PatentBulkData tag,
			// and exclude the opening uspat:PatentBulkData tag
			if ( regex_match(linebuf, rxPatBulkData) ) {
				string s = regex_replace(linebuf, regex("><",regex::basic), ">\n<");
				newXmlfile << s.substr(s.find('\n')) << endl;
				continue;
			}
		}

		// Exclude the closing PatentBulkData tag read from each file
		if ( regex_match(linebuf, rxPatBulkDataEnd) )
			break;

		newXmlfile << linebuf << endl;
	}

	bFirstFile = false;
}

void Proco::fnit () {
	// This code needs to be implemented separately from the destructor to enable
	// running of cleanup code whether or not `transform` throws an exception.

	// Finish the new combined file by appending a closing uspat:PatentBulkData tag
	newXmlfile << "</uspat:PatentBulkData>" << endl;
	newXmlfile.close();

	//Generate unique name for new html file
	string htmlname = bfs::path(newXmlfilename).stem().string() + "-" + datestamp + ".peds.htm";

	cout << "Processing combined XML file. This might take a while. Please wait... " << endl;
	transform(newXmlfilename, htmlname);
	cout << "Done." << endl;
}

Proco::~Proco () {
	bfs::remove_all(collectiondir);
	bfs::remove(newXmlfilename);
}
