/*
 * main.cpp
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

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "PedsXmlZipfileProcessor.hpp"
#include "exceptions.hpp"

namespace bpo = boost::program_options;

class Errout {
public:
	ostream& operator<< (string s) { return cerr << "Error: " << s; }
} errout;

int main (int argc, char* argv[]) {

	try {

		// Construct absolute pathname to XSL transformation file that should be located in one of three places...
		string pxsl("peds.xsl");
		bfs::path xslfile = (bfs::path("/usr/local/share/xsltpeds") /= pxsl);	// Check standard install location
		if ( !bfs::exists(xslfile) ) {
			xslfile = (bfs::current_path() /= pxsl);							// Check current directory
			if ( !bfs::exists(xslfile) ) {
				xslfile = (bfs::current_path().parent_path() /= pxsl);			// Check parent directory (facilitating use of a 'build' dir)
				if ( !bfs::exists(xslfile) )
					throw file_not_found("main", {pxsl});
			}
		}

		///////////////////////////////////////////
		// Process program options and arguments...

		bpo::options_description opts("Options");
		opts.add_options()
				("individual_files,i", "Converts the zip file to one or more HTML files in the current directory.\n")
				("collection_of_files,c", "Converts the zip file to one or more HTML files in a date-time-stamped directory.\n")
				("one_file,o", "Converts the zip file to a single HTML file.\n")
				("help,h", "Show this usage information.")
				;

		bpo::options_description hidden("Hidden Options");
		hidden.add_options()
				("zip_file", bpo::value<string>(), "zip file")
				;

		bpo::options_description cmdln_opts;
		cmdln_opts.add(opts).add(hidden);

		bpo::positional_options_description p;
		p.add("zip_file", 1);

		bpo::variables_map parsed_opts;

		store(bpo::command_line_parser(argc, argv).options(cmdln_opts).positional(p).run(), parsed_opts);
		notify(parsed_opts);

		if (parsed_opts.count("help")) {
			cout << "\nUsage:" << endl << "  xsltpeds OPTION [ZIPFILE]" << endl << endl;
			cout << "  If no ZIPFILE is provided, xsltpeds will operate on the latest zip file" << endl;
			cout << "  found in the current directory." << endl << endl;
			cout << "Description:" << endl;
			cout << "  Converts a PEDS XML zip file to one or more date-time-stamped HTML files" << endl;
			cout << "  for viewing in a browser (e.g. Chrome, Edge, Firefox, or Safari)." << endl << endl;
			cout << opts << endl;
			return 0;
		}

		xsltranstype xtt;
		if (parsed_opts.count("individual_files"))
			xtt = all;
		else if (parsed_opts.count("collection_of_files"))
			xtt = folder;
		else if (parsed_opts.count("one_file"))
			xtt = one;
		else {
			errout << "An option is required." << endl;
			return 1;
		}

		string zipfile;
		if (parsed_opts.count("zip_file")) {
			zipfile = string(parsed_opts["zip_file"].as<string>());
		}

		//////////////////////////////////////////
		// Now, do the real work of the program...

		PedsXmlZipfileProcessor pedsxmlZipfileProcessor(xslfile);
		pedsxmlZipfileProcessor.run(zipfile, xtt);

	} catch (boost::wrapexcept<boost::program_options::unknown_option> &e) {
		errout << e.what() << endl;
	} catch (system_exception &e) {

		string msg;
		string loc(e.what());

		if (loc == "PedsXmlCollectionProcessor::generate_datestamp")
			msg = "Unable to generate a unique identifier for generated files.";

		errout << msg << endl;

	} catch (file_not_opened &e) {
		// from one of the classes in ZipArchive.cpp

		errout << "Unable to open file " << e.filename();

		if ( !(e.error().empty()) )
			cerr << " : " << e.error();

		cerr << endl;

	} catch (file_not_found &e) {

		string msg;
		string loc(e.what());

		if (loc == "SystemXsltProcessor::transform") {
			if ( e(0).empty() ) msg += "Missing filename for output HTML file. ";
			if ( e(1).empty() ) msg += "XML file to be transformed not found. ";
			if ( e(2).empty() ) msg += "XSL transformation file `peds.xsl` not found.";

			errout << msg << endl;
		}
		else {
			if (loc == "ZipfileProcessor::procLatestZipfile")
				msg = "No valid zip file found in directory";
			else if (loc == "main")
				msg = "File not found : XSL transformation file";
			else // if (loc == "ZipfileExpander::process") or otherwise
				msg = "File not found :";

			errout << msg << " " << e.filename() << endl;
		}

	} catch (directory_error &e) {

		string loc(e.what());

		errout << "Unable to create directory " << e.filename();

		if ( loc == "ZipfileExpander::process_(exists)" )
			cerr << " because it already exists.";

		cerr << endl;

	} catch (directory_not_found &e) {

		errout << "Directory " << e.filename() << " not found.";

	} catch (boost::filesystem::filesystem_error &e) {

		errout << e.what() << endl;

	} catch (file_error &e) {

		string loc(e.what());

		if ( loc == "PedsXmlZipfileProcessor::run" ) {
			//cerr << loc << " : Target is neither a zip file nor a directory" << endl;
			errout << e.filename() << " is not a valid zip file." << endl;
		}
	}
}

