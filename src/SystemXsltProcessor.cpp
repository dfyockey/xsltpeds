/*
 * SystemXsltProcessor.cpp
 *
 *  Created on: Oct 15, 2020
 *      Author: David Yockey
 */

#define _CRT_SECURE_NO_WARNINGS		// Prevent Microsoft VC++ from complaining about use of `getenv()`

#include "SystemXsltProcessor.hpp"

SystemXsltProcessor::SystemXsltProcessor () {
#ifdef __linux__
	if ( exists("/usr/bin/Xalan") ) {
		xsltproc = &SystemXsltProcessor::xalan;
		cout << "Xalan found!" << endl;
	}
#endif
#ifdef _WIN32
	if ( exists( string(getenv("windir")) + "\\msxsl.exe" ) ) {
			xsltproc = &SystemXsltProcessor::msxsl;
			cout << "MSXSL found!" << endl;
	}
#endif
	else {
		throw system_exception("SystemXsltProcessor::SystemXsltProcessor");
	}
}

void SystemXsltProcessor::transform(string xmlfile, string xslfile, string htmlname) {
	assert(xsltproc);

	if ( exists(xmlfile) && exists(xslfile) && !htmlname.empty() )
		(this->*xsltproc)( xmlfile, xslfile, htmlname );
	else {
		if ( !exists(xmlfile) ) xmlfile.clear();
		if ( !exists(xslfile) ) xslfile.clear();
		throw argument_error("SystemXsltProcessor::transform()", {htmlname, xmlfile, xslfile});
	}
}

/*
 * Redundancy in the following implementations makes for an uncluttered
 * call in operator() and encapsulation of potentially different syntax
 * in any future implementations (e.g. Saxon) or any changes in the
 * existing processors' syntax.
 */

#ifdef __linux__
void SystemXsltProcessor::xalan (string xmlfile, string xslfile, string htmlname) {
	string cmd = string("Xalan -o '") + htmlname + "' '" + xmlfile + "' '" + xslfile + "'";
	system(cmd.c_str());
}
#endif

#ifdef _WIN32
void SystemXsltProcessor::msxsl (string xmlfile, string xslfile, string htmlname) {
	string cmd = string("msxsl.exe -o '") + htmlname + "' '" + xmlfile + "' '" + xslfile + "'";
	system(cmd.c_str());
}
#endif
