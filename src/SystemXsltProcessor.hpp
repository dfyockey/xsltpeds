/*
 * SystemXsltProcessor.hpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

#ifndef SYSTEMXSLTPROCESSOR_HPP_
#define SYSTEMXSLTPROCESSOR_HPP_

extern int xmlLoadExtDtdDefaultValue;

#include <fstream>

#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <string>
using namespace std;

typedef basic_string<xmlChar> xmlChar_string;

class SystemXsltProcessor {
	//
private:
	bool exists(string f) { ifstream file(f); return file.good(); };
	//
public:
	SystemXsltProcessor () { xmlLoadExtDtdDefaultValue = 1; };
	void transform (string xmlfile, xmlChar_string xslfile, string htmlname);
};

#endif /* SYSTEMXSLTPROCESSOR_HPP_ */
