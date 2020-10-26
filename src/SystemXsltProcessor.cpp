/*
 * SystemXsltProcessor.cpp
 *
 *  Created on: Oct 15, 2020
 *      Author: David Yockey
 */

#include "SystemXsltProcessor.hpp"

SystemXsltProcessor::SystemXsltProcessor () {
	// Check for Xalan in both Linux and Windows to support use of Cygwin
	if ( exists("/usr/bin/Xalan") ) {
		xsltproc = &SystemXsltProcessor::xalan;
		cout << "Xalan found!" << endl;
	}
#ifdef _Win32
	else if ( exists( string(getenv("windir")) + "\\msxsl.exe" ) ) {
			xsltproc = &SystemXsltProcessor::msxsl;
			cout << "MSXSL found!" << endl;
	}
#endif
	else {
		throw system_exception("SystemXsltProcessor");
	}
}

void SystemXsltProcessor::operator() (string htmlname, string xmlfile, string xslfile) {
	assert(xsltproc);

	this->xslfile = xslfile;

	if ( !htmlname.empty() && !xmlfile.empty() && !xslfile.empty() )
		(this->*xsltproc)( htmlname, xmlfile, xslfile );
	else {
		throw missing_argument("SystemXsltProcessor", {htmlname, xmlfile, xslfile});
	}
}
