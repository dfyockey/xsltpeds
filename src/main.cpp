/*
 * main.cpp
 *
 *  Created on: Oct 16, 2020
 *      Author: David Yockey
 */

/*
 * Command Line Usage to be implemented:
 * (display if no option is provided)
 *

  Usage: xsltpeds OPTION [ZIPFILE]

  -i, --individual_files
	Unzips a PEDS collection of Xml files to *individual* files in
	the current folder while insuring that each file has unique name.

  -d, --directory_of_files
	Unzips a PEDS collection of Xml files to individual files in
	a directory (i.e. folder) while insuring that the folder is uniquely named.

  -f, --folder_of_files
    Synonyms of option -d and --directory_of_files.

  -o, --one_file
	Unzips a PEDS collection of Xml files and combines them
	into *one* uniquely-named Xml file.

  -h, --help
    Show this usage information.

  If no ZIPFILE is provided, xsltpeds will operate on the latest zip file
  found in the current directory, if any.

 */

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "PedsXmlZipfileProcessor.hpp"
#include "exceptions.hpp"

namespace bpo = boost::program_options;

int main (int argc, char* argv[]) {

	try {

		///////////////////////////////////////////
		// Process program options and arguments...

		bpo::options_description opts("Options");
		opts.add_options()
				("individual_files,i", "Transform a PEDS XML zip file's contents to individual date-time-stamped HTML files in the current directory (i.e. folder).\n")
				("directory_of_files,d", "Transform a PEDS XML zip file's contents to individual HTML files in a date-time-stamped directory (i.e. folder).\n")
				("folder_of_files,f", "Synonym of option -d [--directory_of_files].\n")
				("one_file,o", "Transform a PEDS XML zip file's contents into one date-time-stamped HTML file.\n")
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
			cout << "Usage:" << endl << "  xsltpeds OPTION [ZIPFILE]" << endl << endl;
			cout << opts << endl;
			cout << "  If no ZIPFILE is provided, xsltpeds will operate on the latest zip file" << endl << "  found in the current directory, if any." << endl;
			return 0;
		}

		xsltranstype xtt;
		if (parsed_opts.count("individual_files"))
			xtt = all;
		else if (parsed_opts.count("directory_of_files") || parsed_opts.count("folder_of_files"))
			xtt = folder;
		else if (parsed_opts.count("one_file"))
			xtt = one;
		else {
			cerr << "Error : An option is required.";
			return 1;
		}

		string zipfile;
		if (parsed_opts.count("zip_file")) {
			zipfile = string(parsed_opts["zip_file"].as<string>());
		}


		// Construct absolute pathname to XSL transformation file located in same directory as executable file...
		bfs::path xslfile = bfs::path(argv[0]).parent_path();
		xslfile /= "peds.xsl";

		//////////////////////////////////////////
		// Now, do the real work of the program...

		PedsXmlZipfileProcessor pedsxmlZipfileProcessor(xslfile);
		pedsxmlZipfileProcessor.run(zipfile, xtt);

	} catch (boost::wrapexcept<boost::program_options::unknown_option> &e) {

		cerr << "Error : " << e.what() << endl;

	} catch (system_exception &e) {

		string msg;
		string loc(e.what());

		if (loc == "PedsXmlCollectionProcessor::generate_datestamp")
			msg = "Unable to generate a unique identifier for generated files due to a system error.";
		else
			msg = "Unknown system error!";

		cerr << msg << endl;

	} catch (file_not_opened &e) {

		cerr << "Unable to open file " << e.filename();

		if ( !(e.error().empty()) )
			cerr << " : " << e.error();

		cerr << endl;

	} catch (files_not_saved &e) {

		cerr << "Unable to save one or more unzipped files from " << e.filename() << endl;

	} catch (file_not_found &e) {

		string msg;
		string loc(e.what());

		if (loc == "SystemXsltProcessor::transform") {
			msg = string("Errors in ") + loc + " :\n";

			if ( e(0).empty() ) msg += "\tMissing filename for output HTML file.\n";
			if ( e(1).empty() ) msg += "\tXML file to be transformed not found.\n";
			if ( e(2).empty() ) msg += "\tXSL transformation file not found.\n";

			cerr << msg << endl;
		}
		else {
			if (loc == "ZipfileProcessor::procLatestZipfile")
				msg = "No zip file found in directory";
			else if (loc == "ZipfileExpander::process")
				msg = "File not found :";

			cerr << msg << " " << e.filename() << endl;
		}

	} catch (directory_error &e) {

		string loc(e.what());

		cerr << "Unable to create directory " << e.filename();

		if ( loc == "ZipfileExpander::process_(exists)" )
			cerr << " because it already exists.";

		cerr << endl;

	} catch (boost::filesystem::filesystem_error &e) {

		cerr << e.what() << endl;

	} catch (file_error &e) {

		string loc(e.what());

		if ( loc == "PedsXmlZipfileProcessor::run" )
			cerr << loc << " : Target is neither a zip file nor a directory" << endl;
		else
			cerr << loc << " : File error" << endl;

	}
}

