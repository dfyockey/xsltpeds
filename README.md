# Xsltpeds *(eks·ess·ell·tee·pəds)*

Copyright © 2020-2021 David Yockey

Xsltpeds is licensed under the GNU General Public License, version 3 (GPL-3.0). See the accompanying LICENSE.txt file for details.

This README file is licensed under a [CC BY 4.0 license](https://creativecommons.org/licenses/by/4.0/).

## Description

Xsltpeds simplifies viewing of search results in requested XML downloads from the [USPTO's Patent Examination Data System](https://ped.uspto.gov/peds). Xsltpeds unzips a downloaded zip file containing XML files of PEDS search result data and processes the XML files by applying an XSLT stylesheet to generate one or more HTML files. The HTML files include the data for all of the results in a format similar to that of the limited number of results displayed on the PEDS site and are viewable in any modern web browser and.

**Note:** Processing may take a some time depending on the size of the search result data set and the speed of the user's system.

## Requirements

Xsltpeds requires installation of the following libraries:

- Boost Filesystem

- Boost Program Options

- Libzip

- Libxml2

- Libxslt

## Installation

Xsltpeds is set up and installed as follows:

1. Unzip the downloaded Xsltpeds package.

2. `cd` to the directory containing the unzipped package files.

3. Run `./configure` to configure the package for your system.
   
   If any errors occur, the most likely reason is that a required library or other other package is not be installed. Review the generated messages for any 'No' or other negative response indicating what is missing and install the required package(s) as needed.

4. Run `make` to compile the package.
   
   Once this step is completed, the program may be run from the directory containing the unzipped package files using the command `./xsltpeds`.

5. Run `sudo make install` to install the program. (Optional)
   
   Once this step is completed, the program may be run from any directory using the command `xsltpeds`.

## Usage

The following assumes that at least one zip file containing search results in XML format has been downloaded from [USPTO's Patent Examination Data System](https://ped.uspto.gov/peds).

Xsltpeds processes a PEDS XML format zip file into one of three different forms depending which of the following options is selected, one of which must be specified.

- `-i` generates HTML file(s) corresponding to the in the current directory.

- `-c` generates one or more HTML files in a new, uniquely-named directory within the current directory.

- `-o` generates a single HTML file in the current directory.

If the zip file(s) to be processed are in the current directory, Xsltpeds can be run without specifying a zip file. In this case, Xsltpeds will operate on the latest zip file found in the current directory and the command to, for example, generate a single HTML file would be:

   `xsltpeds -o`

On completion, the processed zip file will be moved to a directory within the current directory (created if necessary) named `zipTrash`. Since the latest zip file is processed, this move allows for subsequent processing of zip files saved to the same directory without specifying them explicitly. The zipTrash directory may be deleted, or it or its contents moved elsewhere, as desired.

If a zip file to be processed is elsewhere than in the current directory, or if processing without moving the zip file is desired, the zip file must be specified. For example, given the PEDS zip file `pairbulk-custom-xml.zip` saved in a user's `Downloads` folder, a command to generate a single HTML file from the zip file would be:

   `xsltpeds -o ~/Downloads/pairbulk-custom-xml.zip`

In this case, the processed zip file is not moved.

##### HTML File Usage

To toggle the visibility of all data sections in a generated HTML file except the ***Application Data*** sections, click any ***Application Data*** heading in the file. This can facilitate browsing through a large collection of results to find applications of interest.

To toggle the visibility of all information in a generated HTML file except that for a particular application, click that application's title. This facilitates printing information for a single application to paper or PDF.

**Note:** Visibility toggling operations require the viewing web browser's Javascript to be enabled.

**Note:** Visibility toggling operations may take a some time depending on the size of the HTML file and the speed of the user's system.

## Uninstallation

You'll never want to uninstall Xsltpeds, of course. ;^)

But just in case you do...

If Xsltpeds was not installed according to step 5 above, simply delete the directory containing the unzipped package files. Otherwise, run `sudo make uninstall` from the directory containing the unzipped package files.
