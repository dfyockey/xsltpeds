# README for Xsltpeds

  Copyright © 2020 David Yockey
  
  Copying and distribution of this file, with or without modification,
  are permitted in any medium without royalty provided the copyright
  notice and this notice are preserved.
  
---

## Description

   _This project is under development but not yet entirely functional.
   All information provided herein is tentative, may change at any time,
   and may not be up-to-date._

   Xsltpeds is an application and XSLT formatting to facilitate viewing
   search results downloaded in XML format from the USPTO's Patent
   Examination Data System (https://ped.uspto.gov/peds/).
   
   Xsltpeds is the successor to the Bash-script-based XSLT_PEDS. While
   this application is beneficial to Linux users, the motivation for
   this project was particularly to simplify setup and usage within
   Microsoft Windows.
   
## Requirements & Recommendations

  The following are recommended configurations for different systems.
  All recommendations & requirements are available cost-free.
  
### Linux users
  - Xalan (required; listed in package managers as 'xalan' or 'xalan-c')
  
### Microsoft Windows users
  - MSXML 6.0 (`msxml6.msi` required for 32-bit PCs; `msxml6_x64.msi` required for most 64-bit PCs; `msxml6_ia64.msi` required for 64-bit PCs with Itanium processors)
  - MSXSL (`msxsl.exe` required; should be placed in `%windir%` (ordinarily `C:\Windows`).
  
### Microsoft Windows linux-development-environment users (e.g. WSL, Cygwin)
  Either of the above arrangements may be used. If both are provided, Xalan
  will be used.