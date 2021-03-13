/*
 * ZipfileProcessor.hpp
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

/*
 * For processing a zip file with a sufficiently distinctive name
 * for use naming a directory into which the zip file is expanded
 * while avoiding collisions with existing directories. Should a
 * collision occur, an exception is thrown and no damage is done.
 */

#ifndef ZIPFILEPROCESSOR_HPP_
#define ZIPFILEPROCESSOR_HPP_


#include "ZipfileExpander.hpp"

class ZipfileProcessor : protected ZipfileExpander {
public:
	string procLatestZipfile (string dir, bool trash=false);
	string procZipfile (string zipfile);
};


#endif /* ZIPFILEPROCESSOR_HPP_ */
