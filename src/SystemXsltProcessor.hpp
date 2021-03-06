/*
 * SystemXsltProcessor.hpp
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

#ifndef SYSTEMXSLTPROCESSOR_HPP_
#define SYSTEMXSLTPROCESSOR_HPP_

extern int xmlLoadExtDtdDefaultValue;

#include <fstream>

#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <string>
using namespace std;

class SystemXsltProcessor {
	//
private:
	bool exists(string f) { ifstream file(f); return file.good(); };
	//
public:
	SystemXsltProcessor () { xmlLoadExtDtdDefaultValue = 1; };
	void transform (string xmlfile, string xslfile, string htmlname);
};

#endif /* SYSTEMXSLTPROCESSOR_HPP_ */
