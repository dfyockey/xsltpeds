/*
 * SystemXsltProcessor.cpp
 *
 *  Created on: Oct 15, 2020
 *      Author: David Yockey
 */

/*
 * Must target build to x64 for SystemXsltProcessor() to work on 64-bit Windows
 */

#include "SystemXsltProcessor.hpp"

SystemXsltProcessor::SystemXsltProcessor () {
	if ( exists("/usr/bin/Xalan") ) {
		xsltproc = &SystemXsltProcessor::xalan;
		cout << "Xalan found!" << endl;
	} else {
		//string windir = string(getenv("windir")) + "\\System32\\msxsl.exe";
		string windir = string(getenv("windir")) + "\\msxsl.exe";
		if ( exists(windir) ) {
			xsltproc = &SystemXsltProcessor::msxsl;
			cout << "MSXSL found!" << endl;
		}
		else {
			throw system_exception("SystemXsltProcessor");
		}
	}
}

void SystemXsltProcessor::operator() (string htmlname, string xmlfile, string xslfile) {
	assert(xsltproc);

	this->xslfile = xslfile;

	if ( !htmlname.empty() && !xmlfile.empty() && !xslfile.empty() )
		(this->*xsltproc)( htmlname, xmlfile, xslfile );
	else {
		//string msg;
		//if ( htmlname.empty() ) msg += "Missing filename for output Html file.\n";
		//if ( xmlfile.empty() ) msg += "Missing Xml file to be transformed to Html.\n";
		//if ( xmlfile.empty() ) msg += "Missing Xsl transformation file.\n";
		//throw invalid_argument(msg);

		throw missing_argument("SystemXsltProcessor", {htmlname, xmlfile, xslfile});
	}
}
