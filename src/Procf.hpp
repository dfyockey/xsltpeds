/*
 * Procf.hpp
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

#ifndef PROCF_HPP_
#define PROCF_HPP_

#include "CollectionProcessor.hpp"

class Procf : public CollectionProcessor {
public:
	Procf (string xslfile, string datestamp) : CollectionProcessor (xslfile, datestamp) {};
	void proc(bfs::path xmlfilepath);
	void fnit(){};
};


#endif /* PROCF_HPP_ */
