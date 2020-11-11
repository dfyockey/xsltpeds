/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#include <iostream>
#include "exceptions.hpp"
#include "PedsXmlCollectionProcessor.hpp"

int main () {
	try {

		//PedsXsltProcessor pedsXsltProc;

		//pedsXsltProc("1996-1998.xml", "Result1.html");
		//pedsXsltProc("pairbulk-20200825-163450.xml", "Result2.html");

		PedsXmlCollectionProcessor procPedsXmlCollection;
		procPedsXmlCollection.process("testdir", one);

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

		cerr << msg;

	}
}

