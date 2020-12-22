/*
 * ZipfileExpander.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: David Yockey
 */

#include "ZipfileExpander.hpp"

#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <zip.h>

#include "exceptions.hpp"
#include "ZipArchive.hpp"

namespace bfs = boost::filesystem;

using namespace std;

bool ZipfileExpander::isZipfile (string filename) {
	ifstream f1(filename);
	string filesig(4,'\0');	// construct string to receive filesig from f1

	f1.read(&filesig[0],4);

	// Zip file signature is combination of ASCII codes for P, K, ETX, and EOT
	return ( f1.gcount() >= 4 && filesig == "\x50\x4B\x03\x04" );
}

string ZipfileExpander::process (string zipfile, string datestamp) {
	if (!bfs::exists(zipfile))
		throw file_not_found("ZipfileExpander::process", {zipfile});

	string newdir = bfs::path(zipfile).stem().string();

	if ( !datestamp.empty() ) {
		newdir += "-";
		newdir += datestamp;
	}

	if ( bfs::exists(newdir) )
		throw directory_error("ZipfileExpander::process_(exists)", newdir);
	else if ( !bfs::create_directory(newdir) )
		throw directory_error("ZipfileExpander::process", newdir);

	expand(zipfile, newdir);

	return newdir;
}

void ZipfileExpander::expand(string zipfile, string targetdir) {
	try {
		ZipArchive zipArchive(zipfile, ZIP_RDONLY);

		bfs::path destination_dir(targetdir);
		vector<char> vBuffer;

		int n = zip_get_num_entries(zipArchive, 0);	// get number of files in archive

		for (int i=0; i<n; ++i) {
			ZipArchiveFile zipFile(&zipArchive, i, 0);

			if ((zipFile.stat().valid & ZIP_STAT_NAME) && (zipFile.stat().valid & ZIP_STAT_SIZE)) {
				int zipFileSize = zipFile.stat().size;

				vBuffer.resize(zipFileSize);
				zip_fread(zipFile, &vBuffer[0], zipFileSize);

				string targetfile = targetdir + "/" + zipFile.stat().name;
				ofstream outfile(targetfile, ios::binary);
				outfile.write(&vBuffer[0], zipFileSize);
			}
		}
	} catch (...) {
		if (bfs::exists(targetdir))
			bfs::remove_all(targetdir);

		throw;
	}
}

