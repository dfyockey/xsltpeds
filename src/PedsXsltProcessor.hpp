/*
 * PedsXsltProcessor.hpp
 *
 *  Created on: Oct 27, 2020
 *      Author: David Yockey
 */

#ifndef PEDSXSLTPROCESSOR_HPP_
#define PEDSXSLTPROCESSOR_HPP_

#include "SystemXsltProcessor.hpp"

class PedsXsltProcessor : public SystemXsltProcessor {
	//
private:
	xmlChar_string xslpedsfile;
public:
	PedsXsltProcessor () : SystemXsltProcessor(), xslpedsfile(xmlCharStrdup("peds.xsl")) { };
	PedsXsltProcessor (xmlChar_string xslfile) : SystemXsltProcessor(), xslpedsfile(xslfile) {};

	void transform (string xmlfile, xmlChar_string xslfile, string htmlname);
	void transform (string xmlfile, string htmlname) { SystemXsltProcessor::transform(xmlfile, xslpedsfile, htmlname); };
};

#endif /* PEDSXSLTPROCESSOR_HPP_ */
