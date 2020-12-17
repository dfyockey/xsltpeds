/*
 * Procf.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: David Yockey
 */

#include "Procf.hpp"

void Procf::proc (bfs::path xmlfilepath) {
	string htmlname = collectiondir + "/" + xmlfilepath.stem().string() + "-" + datestamp + ".peds.htm";
	transform(xmlfilepath.string(), htmlname);
	bfs::remove(xmlfilepath);
}
