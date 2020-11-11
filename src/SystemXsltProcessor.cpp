/*
 * SystemXsltProcessor.cpp
 *
 *  Created on: Oct 15, 2020
 *      Author: David Yockey
 */

#include "libxml2/libxml/xmlstring.h"
#include "SystemXsltProcessor.hpp"
#include "exceptions.hpp"

/*
 * All the casts in the following are regrettable but expedient, and are at least safer and
 * more evident than the plain C-style casts libxml2 uses internally to get from xmlChar* to char*.
 */

void SystemXsltProcessor::transform(string xmlfile, xmlChar_string xslfile, string htmlname) {

	if ( exists(xmlfile) && exists(reinterpret_cast<char*>(const_cast<xmlChar*>(xslfile.c_str()))) && !htmlname.empty() ) {
		xsltStylesheetPtr pParsedXsltStylesheet = xsltParseStylesheetFile (xslfile.c_str());
		xmlDocPtr pParsedXmlFile = xmlParseFile(xmlfile.c_str());
		xmlDocPtr pHtmlDoc = xsltApplyStylesheet(pParsedXsltStylesheet, pParsedXmlFile, 0);
		xsltSaveResultToFilename(htmlname.c_str(), pHtmlDoc, pParsedXsltStylesheet, 0);
	}
	else {
		// Clear files to indicate which, if any, were not found...
		if ( !exists(xmlfile) ) xmlfile.clear();
		if ( !exists(reinterpret_cast<char*>(const_cast<xmlChar*>(xslfile.c_str()))) ) xslfile.clear();
		throw argument_error("SystemXsltProcessor::transform()", {htmlname, xmlfile, reinterpret_cast<char*>(const_cast<xmlChar*>(xslfile.c_str()))});
	}

}
