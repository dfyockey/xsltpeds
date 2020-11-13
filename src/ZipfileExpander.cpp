/*
 * ZipfileExpander.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: David Yockey
 */

#include "ZipfileExpander.hpp"

#include <boost/filesystem.hpp>
#include <fstream>
#include <minizip/mz.h>
#include <minizip/mz_strm.h>
#include <minizip/mz_zip.h>
#include <minizip/mz_zip_rw.h>

#include "exceptions.hpp"

namespace bfs = boost::filesystem;

using namespace std;

bool ZipfileExpander::isZipfile (string filename) {
	ifstream f1(filename);
	string filesig(4,'\0');	// construct string to receive filesig from f1

	f1.read(&filesig[0],4);

	// Zip file signature is combination of ASCII codes for P, Y, ETX, and EOT
	return ( f1.gcount() >= 4 && filesig == "\x50\x4B\x03\x04" );
}

string ZipfileExpander::process (string zipfile, string datestamp) {
	string newdir = string("pairbulk-") + datestamp;
	bfs::create_directory(newdir);

	expand(zipfile, newdir);

	return newdir;
}

void ZipfileExpander::expand(string zipfile, string targetdir) {
	void *zip_reader = 0;
	mz_zip_reader_create(&zip_reader);

	if (mz_zip_reader_open_file(zip_reader, zipfile.c_str()) != MZ_OK)
		throw file_not_opened("ZipfileExpander::expand", zipfile);

	bfs::path destination_dir(targetdir);
	if (mz_zip_reader_save_all(zip_reader, destination_dir.string().c_str()) != MZ_OK)
		throw files_not_saved("ZipfileExpander::expand", zipfile);

    mz_zip_reader_close(zip_reader);
	mz_zip_reader_delete(&zip_reader);
}
