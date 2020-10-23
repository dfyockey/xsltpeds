/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#include "SystemXsltProcessor.hpp"

int main () {
	try {

		SystemXsltProcessor sysXsltProc = SystemXsltProcessor();

		sysXsltProc("a", "b", "c");

	} catch (system_exception &e) {
		cerr << "No XSLT processor found.\nPlease install Xalan (for Linux) or MSXSL (for Windows)." << endl;
	} catch (missing_argument &args) {
		string msg = string("Errors in ") + args.what() + " :\n";
		if ( args(0).empty() ) msg += "\tMissing filename for output Html file.\n";
		if ( args(1).empty() ) msg += "\tMissing filename of Xml file to be transformed to Html.\n";
		if ( args(2).empty() ) msg += "\tMissing filename of Xsl transformation file.\n";
		cerr << msg;
	}
}

