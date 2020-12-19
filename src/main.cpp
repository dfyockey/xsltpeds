/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#include <iostream>
#include <boost/filesystem.hpp>
#include "PedsXmlZipfileProcessor.hpp"
#include "exceptions.hpp"

int main () {
	try {

		PedsXmlZipfileProcessor pedsxmlZipfileProcessor;
		pedsxmlZipfileProcessor.run("testdir/pairbulk-custom-dcbc7c92-9aa5-45ef-b593-0521fc006720-xml.zip", all);

	} catch (system_exception &e) {

		string msg;
		string loc(e.what());

		if (loc == "PedsXmlCollectionProcessor::generate_datestamp")
			msg = "Unable to generate a unique identifier for generated files due to a system error.";
		else
			msg = "Unknown system error!";

		cerr << msg << endl;

	} catch (file_not_opened &e) {

		cerr << "Unable to open file " << e.filename();

		if ( !(e.error().empty()) )
			cerr << " : " << e.error();

		cerr << endl;

	} catch (files_not_saved &e) {

		cerr << "Unable to save one or more unzipped files from " << e.filename() << endl;

	} catch (file_not_found &e) {

		string msg;
		string loc(e.what());

		if (loc == "SystemXsltProcessor::transform") {
			msg = string("Errors in ") + loc + " :\n";

			if ( e(0).empty() ) msg += "\tMissing filename for output HTML file.\n";
			if ( e(1).empty() ) msg += "\tXML file to be transformed not found.\n";
			if ( e(2).empty() ) msg += "\tXSL transformation file not found.\n";

			cerr << msg << endl;
		}
		else {
			if (loc == "ZipfileProcessor::procLatestZipfile")
				msg = "No zip file found in directory";
			else if (loc == "ZipfileExpander::process")
				msg = "File not found :";

			cerr << msg << " " << e.filename() << endl;
		}

	} catch (directory_error &e) {

		cerr << "Unable to create directory " << e.filename();

		if ( e.what() == "ZipfileExpander::process_(exists)" )
			cerr << " because it already exists.";

		cerr << endl;

	} catch (boost::filesystem::filesystem_error &e) {
		cerr << e.what() << endl;
	} catch (file_error &e) {
		if ( e.what() == "PedsXmlZipfileProcessor::run" )
			cerr << e.what() << " : Target is neither a zip file nor a directory" << endl;
		else
			cerr << e.what() << " : File error" << endl;
	}
}

