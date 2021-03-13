/*
 * ZipArchive.hpp
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

#ifndef ZIPARCHIVE_HPP_
#define ZIPARCHIVE_HPP_

#include <string>
#include <zip.h>

class ZipArchive {
public:
	ZipArchive ( std::string zipfile, int flags );
	~ZipArchive ();
	operator zip_t* () { return pArchive; }
private:
	zip_t* pArchive;
};

class ZipArchiveFile {
public:
	ZipArchiveFile ( ZipArchive* pArchive, int index, int flags );
	~ZipArchiveFile ();
	operator zip_file_t* () { return pFile; }
	zip_stat_t stat () { return zs; }
private:
	zip_file_t* pFile;

	/* :(
	 * Took forever to figure out that the following line SHOULDN'T have been `zip_stat_t zs`,
	 * but I finally got a clue from https://gist.github.com/sdasgup3/a0255ebce3e3eec03e6878b47c8c7059.
	 * :) */
	struct zip_stat zs;
};

/* Excerpt from source code file `zipint.h`                        */
/* (see https://github.com/nih-at/libzip/blob/master/lib/zipint.h) */

struct zip {
    zip_source_t *src;       /* data source for archive */
    unsigned int open_flags; /* flags passed to zip_open */
    zip_error_t error;       /* error information */

    /* ... */
    /* Remaining struct zip members unused in this implementation! */
    /* ... */
};

#endif /* ZIPARCHIVE_HPP_ */
