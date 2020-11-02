/*
 * Proca.cpp
 *
 *  Created on: Oct 31, 2020
 *      Author: David Yockey
 */

#include "Proca.hpp"

void Proca::proc (string datestamp, string xmlfilepath, string newdir) {
	this->newdir = newdir;
	string htmlname = xmlfilepath + "-" + datestamp + ".peds.htm";
	transform(xmlfilepath, htmlname);
}

void Proca::fint () {
	bfs::remove(newdir);
}
