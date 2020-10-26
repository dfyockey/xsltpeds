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
	typedef void (SystemXsltProcessor::*xsltproc_fptr) (string htmlname, string xmlfile, string xslfile);
	xsltproc_fptr xsltproc;
	string xslfile;
	bool exists(string f) { ifstream file(f); return file.good(); };
	//
public:
	SystemXsltProcessor ();
	void operator() (string htmlname, string xmlfile, string xslfile);
	void operator() (string htmlname, string xmlfile) { operator()(htmlname, xmlfile, xslfile); };
	void xalan (string htmlname, string xmlfile, string xslfile) { cout << "Using xalan!" << endl; };
#ifdef _Win32
	void msxsl (string htmlname, string xmlfile, string xslfile) { cout << "Using msxsl!" << endl; };
#endif
	//
};


#endif /* SYSTEMXSLTPROCESSOR_HPP_ */
