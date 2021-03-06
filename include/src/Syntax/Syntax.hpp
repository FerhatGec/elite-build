/*# MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/

#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include "../File/File.hpp"
#include "../Print/Print.hpp"
#include "../Print/Colors.hpp"
#include "../Lexer/Lexer.hpp"
#include "../Elitebuild.hpp"
#include <fstream>
#include <cstdlib> // for System function

class Syntax {
public:
    std::string CommentLine();
};

class SyntaxModel {
	File pwd;
	LexerKeywords keywords;
	Lexer lex;
public:
    SyntaxModel() {}
    ~SyntaxModel() {} 
    
    std::string line;
    std::string SetName;
    // Path
    std::string Path() { 
    	std::string path = pwd.GetCurrentWorkingDir();
    	path.append("/");
	path.append("Elitefile");
	return path;
    }
    
    // Get Between String    
    void GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr)
    {  
    int start = oStr.find(sStr1);   
    if (start >= 0)     
    {       
      std::string tstr = oStr.substr(start + sStr1.length());        
      int stop = tstr.find(sStr2);      
      if (stop >1)          
        rStr = oStr.substr(start + sStr1.length(), stop);
      else
        rStr ="error";  
    }
    else
       rStr = "error"; 
    }    
        
    // Erase Function 
    std::string EraseAllSubString(std::string & mainString, const std::string & erase) {
        size_t pos = std::string::npos;
    	while((pos = mainString.find(erase)) != std::string::npos)
    	{
    	    mainString.erase(pos, erase.length());
    	}
    	return mainString;
    }
    // Elitefile Read Function
    void ReadElitefile() {
    	 std::ifstream readfile(Path());
    	 if(readfile.is_open()) {
		while (std::getline(readfile, line)) {							
			if(strstr(line.c_str(), keywords.GetBegin.c_str())) {
			        std::string output;
				GetBtwString(line, keywords.GetBegin, keywords.GetEnd, output);
				line = EraseAllSubString(line, keywords.GetBegin + output + keywords.GetEnd);
				//std::cout << line; For testing
				line.append(getenv(output.c_str()));
				//std::cout << line; For testing
			}
			
			// Comment Lines
			if(line.find(keywords.CommentLines, 0) == 0) {
				line.erase(0, line.length());
				lex.FCommentLines();
			}
			
			if(line.find(keywords.GetEnvr + keywords.Whitespace, 0) == 0) {
				getenv(EraseAllSubString(line, keywords.GetEnvr + keywords.Whitespace).c_str());
			}
			
			// Printlnf
			if(line.find(keywords.Printlnf + keywords.Whitespace + keywords.ArrowType, 0) == 0) {
				printlnf(getenv(EraseAllSubString(line, keywords.Printlnf + keywords.Whitespace + keywords. ArrowType).c_str()));
			}
			
			if(line.find(keywords.Printlnf + keywords.Whitespace, 0) == 0) {
					std::cout << EraseAllSubString(line, keywords.Printlnf + keywords.Whitespace);
			}
			
			if(line.find(keywords.Printlnf, 0) == 0) {
				BOLD_RED_COLOR
				printlnf("Please put Whitespace front printlnf\n");
				BLACK_COLOR 
			} 
			if(line.find(keywords.CommentLines + keywords.Printlnf, 0) == 0) {
				line.erase(0, line.length());
				lex.FCommentLines();
			}
			
			if(line.find(keywords.System + keywords.Whitespace + keywords.ArrowType, 0) == 0) {
				system(getenv(EraseAllSubString(line, keywords.System + keywords.Whitespace + keywords.ArrowType).c_str()));
			
			}
			
			// System
			if(line.find(keywords.System + keywords.Whitespace, 0) == 0) {
				system(EraseAllSubString(line, keywords.System + keywords.Whitespace).c_str());
			} else if(line.find(keywords.CommentLines + keywords.System, 0) == 0) {
				line.erase(0, line.length());
				lex.FCommentLines();
			}
			
			// Set name
			if(line.find(keywords.SetEnvironmentName + keywords.Whitespace, 0) == 0) {
					SetName = EraseAllSubString(line, keywords.SetEnvironmentName + keywords.Whitespace);
			}
			
			// Set name to
			if(line.find(keywords.SetEnvironmentNameTo + keywords.Whitespace, 0) == 0) {
    			setenv(SetName.c_str(), EraseAllSubString(line, keywords.SetEnvironmentNameTo + keywords.Whitespace).c_str(), true);
    	}
    		}
    		
    	}
    	readfile.close();
    }
    
    /*bool FindAllSubString(std::string & mainString, const std::string & findstr) {
        size_t pos = std::string::npos;
    	while((pos = mainString.find(findstr)) != std::string::npos)
    	{
    	    return true;
    	}
    } */   
};


#endif // SYNTAX_HPP
