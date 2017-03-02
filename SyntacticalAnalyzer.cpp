#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
  
  lex = new LexicalAnalyzer (filename);

	token_type t;
	// read 1 line in at a time as a string
	lex->fileName(string(filename) );
	do
	  {
	    // read in line
	    lex->getInput();
	    // index should be using pos
	    if(lex->getStream().eof()) t = EOF_T;
	    // print line, line_number

	    while(lex->getPos() < lex->getLine().size())
		{
	      // get part of lexeme
	      t = lex->GetToken();
	      if(t == lex->GetToken)
		{
		  lex->ReportError();
		}
	      // retrieve the lexeme
	      // string token_name = retrieve the tokenName(t)
	      // how to know when the end of the lexeme is found

		}


	  	// print tokens, lexemes
		lex->incrementLineNumber();

	  } while(t != EOF_T); //eof has not been set

	// output 
	lex->closeFile();
	
	//delete lex;
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
  delete lex;
}
