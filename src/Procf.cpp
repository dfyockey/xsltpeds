/*
 * Procf.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: David Yockey
 */

#include "Procf.hpp"

void Procf::proc (bfs::path xmlfilepath) {
	string htmlname = collectiondir + "/" + xmlfilepath.stem().string() + "-" + datestamp + ".peds.htm";

	// In "folder" processing mode, `collectiondir` shouldn't be removed at all unless there's an error.
	try {
		transform(xmlfilepath.string(), htmlname);
	} catch (...) {
		bfs::remove_all(collectiondir);
		throw;
	}

	bfs::remove(xmlfilepath);
}
