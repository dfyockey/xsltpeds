/*
 * Proco.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: David Yockey
 */

#include <regex>
#include "Proco.hpp"

Proco::Proco (string datestamp) : CollectionProcessor (datestamp), bFirstFile(true) {

}

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
	// Finish the new combined file by appending a closing uspat:PatentBulkData tag
	newXmlfile << "</uspat:PatentBulkData>" << endl;

	//Generate unique name for new html file
	string htmlname = bfs::path(newXmlfilename).stem().string() + "-" + datestamp + ".peds.htm";

	transform(newXmlfilename, htmlname);

	bfs::remove_all(collectiondir);
	bfs::remove(newXmlfilename);
}