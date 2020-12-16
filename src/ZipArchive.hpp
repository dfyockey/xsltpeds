/*
 * ZipArchive.hpp
 *
 *  Created on: Dec 5, 2020
 *      Author: David Yockey
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
