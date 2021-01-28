/*
 * Proca.cpp
 *
 *  Created on: Oct 31, 2020
 *      Author: David Yockey
 */

#include "Proca.hpp"

void Proca::proc (bfs::path xmlfilepath) {
	string htmlname = xmlfilepath.stem().string() + "-" + datestamp + ".peds.htm";
	transform(xmlfilepath.string(), htmlname);
}

Proca::~Proca () {
	bfs::remove_all(collectiondir);
}
