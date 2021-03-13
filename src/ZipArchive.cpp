/*
 * ZipArchive.cpp
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

#define _CRT_SECURE_NO_WARNINGS		// Prevent Microsoft VC++ from complaining about use of `strerror()`

#include "ZipArchive.hpp"

#include <cstring>

#include "exceptions.hpp"

ZipArchive::ZipArchive ( std::string zipfile, int flags ) {
	int ziperr;
	pArchive = zip_open(zipfile.c_str(), ZIP_RDONLY, &ziperr);
	if ( pArchive == NULL )
		throw file_not_opened("ZipArchive::ZipArchive", zipfile, strerror(ziperr));
}

ZipArchive::~ZipArchive () {
	if (pArchive) zip_close(pArchive);
}

///////////////////////////////////////////////////////////////////////////

/* :(
 * This method kept throwing an exception when zipArchive was passed as `ZipArchive zipArchive`.
 * After a good amount of tedious debugging, I realized that zipArchive was being created at each
 * call to zip_stat_index and zip_fopen_index, and then destroyed on return. Changing to passing
 * zipArchive as a pointer rather than a reference facilitated persistence of zipArchive throughout
 * the calls and returns, eliminating throw of an exception.
 * :) */
ZipArchiveFile::ZipArchiveFile ( ZipArchive* zipArchive, int index, int flags ) {
	zip_stat_init(&zs);
	zip_stat_index(*zipArchive, index, 0, &zs);

	pFile = zip_fopen_index(*zipArchive, index, 0);
	if ( pFile == NULL ) {
		throw file_not_opened("ZipArchiveFile::ZipArchiveFile", std::string() + to_string(index) + " in zip archive.", zip_error_strerror(&(zipArchive->operator zip *()->error)));
	}
}

ZipArchiveFile::~ZipArchiveFile () {
	if (pFile) zip_fclose(pFile);
}
