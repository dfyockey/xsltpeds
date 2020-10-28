/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#include "PedsXsltProcessor.hpp"
#include "PedsXmlCollectionProcessor.hpp"

int main () {
	try {

		//PedsXsltProcessor pedsXsltProc;

		//pedsXsltProc("1996-1998.xml", "Result1.html");
		//pedsXsltProc("pairbulk-20200825-163450.xml", "Result2.html");

		PedsXmlCollectionProcessor pedsXmlCollProc;

	} catch (system_exception &e) {

		string msg;

		switch (e.what()) {
		case "SystemXsltProcessor::SystemXsltProcessor":
			msg = "No XSLT processor found.\nPlease install Xalan (for Linux) or MSXSL (for Windows).";
			break;
		case "PedsXmlCollectionProcessor::PedsXmlCollectionProcessor":
			msg = "Unable to generate a unique identifier for generated files due to a system error.";
			break;
		default:
			msg = "Unknown system error!";
			break;
		}

		cerr << msg << endl;

	} catch (argument_error &args) {

		string msg = string("Errors in ") + args.what() + " :\n";

		if ( args(0).empty() ) msg += "\tMissing filename for output HTML file.\n";
		if ( args(1).empty() ) msg += "\tXML file to be transformed not found.\n";
		if ( args(2).empty() ) msg += "\tXSL transformation file not found.\n";

		cerr << msg;

	}
}

