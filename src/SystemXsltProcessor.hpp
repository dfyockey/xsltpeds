/*
 * SystemXsltProcessor.hpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#ifndef SYSTEMXSLTPROCESSOR_HPP_
#define SYSTEMXSLTPROCESSOR_HPP_


#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "exceptions.hpp"

class SystemXsltProcessor {
	//
private:
	typedef void (SystemXsltProcessor::*xsltproc_fptr) (string xmlfile, string xslfile, string htmlname);
	xsltproc_fptr xsltproc;
	string xslfile;
	bool exists(string f) { ifstream file(f); return file.good(); };
	//
public:
	SystemXsltProcessor ();
	void operator() (string xmlfile, string xslfile, string htmlname);
	void operator() (string xmlfile, string htmlname) { operator()(xmlfile, xslfile, htmlname); };
#ifdef __linux__
	void xalan (string xmlfile, string xslfile, string htmlname);
#endif
#ifdef _WIN32
	void msxsl (string xmlfile, string xslfile, string htmlname);
#endif
	//
};


#endif /* SYSTEMXSLTPROCESSOR_HPP_ */
