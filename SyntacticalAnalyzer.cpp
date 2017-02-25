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
	do
	  {
	    // read in line
	    lex->getInput();
	    cout << "new line\n";
	    // index should be using pos
	    if(lex->getStream().eof()) t = EOF_T;
	    while(lex->getPos() < lex->getLine().size())
	      
	      // get all lexemes
	      t = lex->GetToken();
	    
	  } while(t != EOF_T/*!(lex->getStream().eof())*/); //eof has not been set
	
	
	
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
  delete lex;
}
