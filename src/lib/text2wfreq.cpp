/*******************************************************************
C++ Package of  Ternary Search Tree
Copyright (C) 2006  Zheyuan Yu

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Read full GPL at http://www.gnu.org/copyleft/gpl.html

Email me at jerryy@gmail.com if you have any question or comment
WebSite: http://www.cs.dal.ca/~zyu

*************************************************************************/
#include <ctime>
#include <iostream>

#include <ngram/config.h>
#include <ngram/text2wfreq.h>


using namespace std;

bool Text2wfreq::getOptions(int argc, char *argv[]) {
  if (argc < 2) {
    return false;
  }

  if (Config::hasOption("--help", argc, argv) ||
      Config::hasOption("-help", argc, argv)) {
    return false;
  }

  utf8_string value = Config::getOptionValue("-type", argc, argv);

  if (value == "character") {
    ngramType = Config::CHAR_NGRAM;
  } else if (value == "word") {
    ngramType = Config::WORD_NGRAM;
  } else if (value == "byte") {
    ngramType = Config::BYTE_NGRAM;
  } else if (value != "") {
    printf("wrong type option!\n");
    return false;
  }

  value = Config::getOptionValue("-n", argc, argv);

  if (value != "") {
    sscanf(value.c_str(), "%d", &ngramN);
  }

  inFileName = Config::getOptionValue("-in", argc, argv).c_str();
  outFileName = Config::getOptionValue("-out", argc, argv).c_str();

  return true;
}