/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#include "PedsXmlCollectionProcessor.hpp"
#include "ZipfileProcessor.hpp"

int main () {
	try {

		//PedsXsltProcessor pedsXsltProc;

		//pedsXsltProc("1996-1998.xml", "Result1.html");
		//pedsXsltProc("pairbulk-20200825-163450.xml", "Result2.html");

		//PedsXmlCollectionProcessor procPedsXmlCollection;
		//procPedsXmlCollection.process(".", all);

/*
		ZipfileExpander zipfileExpander;
		cout << zipfileExpander.isZipfile("LICENSE.txt") << endl;
		cout << zipfileExpander.isZipfile("pairbulk-custom-dcbc7c92-9aa5-45ef-b593-0521fc006720-xml.zip") << endl;
		cout << zipfileExpander.isZipfile("peds.xsl") << endl;
		cout << zipfileExpander.isZipfile("README.md") << endl;
*/

		//zipfileExpander.process("pairbulk-custom-dcbc7c92-9aa5-45ef-b593-0521fc006720-xml.zip", "test");

		ZipfileProcessor zipfileProcessor;
		//zipfileProcessor.procLatestZipfile("testdir", "datestamp02");
		zipfileProcessor.procZipfile("testdir/pairbulk-custom-dcbc7c92-9aa5-45ef-b593-0521fc006720-xml.zip", "datestamp04");


	} catch (system_exception &e) {

		string msg;
		string loc(e.what());

		if (loc == "SystemXsltProcessor::SystemXsltProcessor")
			msg = "No XSLT processor found.\nPlease install Xalan (for Linux) or MSXSL (for Windows).";
		else if (loc == "PedsXmlCollectionProcessor::generate_datestamp")
			msg = "Unable to generate a unique identifier for generated files due to a system error.";
		else
			msg = "Unknown system error!";

		cerr << msg << endl;

	} catch (argument_error &args) {

		string msg = string("Errors in ") + args.what() + " :\n";

		if ( args(0).empty() ) msg += "\tMissing filename for output HTML file.\n";
		if ( args(1).empty() ) msg += "\tXML file to be transformed not found.\n";
		if ( args(2).empty() ) msg += "\tXSL transformation file not found.\n";

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

		if (loc == "ZipfileProcessor::procLatestZipfile")
			msg = "No zip file found in directory";
		else if (loc == "ZipfileExpander::process")
			msg = "File not found :";

		cerr << msg << " " << e.filename() << endl;

	} catch (directory_error &e) {

		cerr << "Unable to create directory " << e.filename() << " because it already exists.";

	}
}

