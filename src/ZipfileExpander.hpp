/*
 * ZipfileExpander.hpp
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

#ifndef ZIPFILEEXPANDER_HPP_
#define ZIPFILEEXPANDER_HPP_

#include <string>
using namespace std;

class ZipfileExpander {
public:
	bool isZipfile (string filename);
	string process(string zipfile, string datestamp="");
private:
	void expand(string zipfile, string targetdir);
};

#endif /* ZIPFILEEXPANDER_HPP_ */
