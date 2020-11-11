/*
 * PedsXsltProcessor.cpp
 *
 *  Created on: Oct 27, 2020
 *      Author: David Yockey
 */

#include "PedsXsltProcessor.hpp"

void PedsXsltProcessor::transform(string xmlfile, string xslfile, string htmlname) {
	// Save xslfile for use in transforming multiple xml files in a PEDS zip file
	xslpedsfile = xslfile;
	transform(xmlfile, htmlname);
}
