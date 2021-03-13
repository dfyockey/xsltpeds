/*
 * SystemXsltProcessor.cpp
 *
 *  Copyright © 2020-2021 David Yockey
 *
 *  This file is part of Xsltpeds.
 *
 *  Xsltpeds is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Xsltpeds is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Xsltpeds.  If not, see <https://www.gnu.org/licenses/>.
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
		throw file_not_found("SystemXsltProcessor::transform", {htmlname, xmlfile, xslfile});
	}

}
