/*
 * SystemXsltProcessor.cpp
 *
 *  Created on: Oct 15, 2020
 *      Author: David Yockey
 */


#define _CRT_SECURE_NO_WARNINGS		// Prevent Microsoft VC++ from complaining about use of `getenv()`

#include "libxml/xmlstring.h"

#include "SystemXsltProcessor.hpp"
#include "exceptions.hpp"

void SystemXsltProcessor::transform(string xmlfile, string xslfile, string htmlname) {

	if ( exists(xmlfile) && exists(xslfile) && !htmlname.empty() ) {
		xsltStylesheetPtr pParsedXsltStylesheet = xsltParseStylesheetFile(xmlCharStrdup(xslfile.c_str()));
		xmlDocPtr pParsedXmlFile = xmlParseFile(xmlfile.c_str());
		xmlDocPtr pHtmlDoc = xsltApplyStylesheet(pParsedXsltStylesheet, pParsedXmlFile, 0);
		xsltSaveResultToFilename(htmlname.c_str(), pHtmlDoc, pParsedXsltStylesheet, 0);
	}
	else {
		// Clear files to indicate which, if any, were not found...
		if ( !exists(xmlfile) ) xmlfile.clear();
		if ( !exists(xslfile) ) xslfile.clear();
		throw file_not_found("SystemXsltProcessor::transform()", {htmlname, xmlfile, xslfile});
	}

}
