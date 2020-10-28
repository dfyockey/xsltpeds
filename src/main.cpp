/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#include "PedsXsltProcessor.hpp"

int main () {
	try {

		PedsXsltProcessor pedsXsltProc;

		pedsXsltProc("1996-1998.xml", "Result1.html");
		pedsXsltProc("pairbulk-20200825-163450.xml", "Result2.html");

	} catch (system_exception &e) {
		cerr << "No XSLT processor found.\nPlease install Xalan (for Linux) or MSXSL (for Windows)." << endl;
	} catch (argument_error &args) {
		string msg = string("Errors in ") + args.what() + " :\n";
		if ( args(0).empty() ) msg += "\tMissing filename for output HTML file.\n";
		if ( args(1).empty() ) msg += "\tXML file to be transformed not found.\n";
		if ( args(2).empty() ) msg += "\tXSL transformation file not found.\n";
		cerr << msg;
	}
}

