/*# MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/


#include <iostream>
#include <ctype.h>
#include <memory>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <stdio.h>

// Print
#include "../include/src/Print/Colors.hpp"
#include "../include/src/Print/Print.hpp"

// Help
#include "../include/src/Help/Help.hpp"

// Syntax 
#include "../include/src/Syntax/Syntax.hpp"

// File
#include "../include/src/File/File.hpp"

// Version Generator
#include "../include/src/Version/Version.hpp"

// Main
#include "../include/src/Elitebuild.hpp"

File path;
SyntaxModel model;
Version version_generator;

int main(int argc, char** argv)
{
    path.FindElitefile();
    if (argc > 1) 
    {
		for (int i = 1; i < argc; i++) 
		{
			std::string arg(argv[i]);

			if (arg.substr(0, 2) == "--") 
			{

				if (arg == "--build") {
					BOLD_RED_COLOR
        				printlnf("Not now\n");
        				model.ReadElitefile();
        				BLACK_COLOR
				} else if(arg == "--path") {
					WHITE_COLOR
					printlnf(model.Path().c_str());
					Slashn // printlnf("\n");
					BLACK_COLOR
				}
				else if (arg == "--help") {
					BOLD_RED_COLOR
					printlnf(Help.c_str());
					BLACK_COLOR
					exit(0);
				} else if (arg == "--version") {
					version_generator.PrintVersion();
					exit(0);
				} else {
					BOLD_RED_COLOR
					printlnf("Command or argument is not found!\n");
					WHITE_COLOR
					printlnf(Help.c_str());
					BLACK_COLOR
					exit(0);
				}
			} 
			else 
			{
				printlnf(Help.c_str());
			}
		}
	} 
	else 
	{
		WHITE_COLOR
		printlnf(Help.c_str());
		exit(0);
	}
    return 0;
}
