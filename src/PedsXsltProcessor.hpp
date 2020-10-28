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
	string xslpedsfile;
public:
	PedsXsltProcessor () : SystemXsltProcessor(), xslpedsfile("peds.xsl") {};
	PedsXsltProcessor (string xslfile) : SystemXsltProcessor(), xslpedsfile(xslfile) {};

	void operator() (string xmlfile, string xslfile, string htmlname);
	void operator() (string xmlfile, string htmlname) { SystemXsltProcessor::operator()(xmlfile, xslpedsfile, htmlname); };
};

#endif /* PEDSXSLTPROCESSOR_HPP_ */
