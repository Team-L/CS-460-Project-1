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

	cout << "got here.";
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

	/*
	for(int i = 0; i < lex->getLine().size(); i++)
	{
		cout << "here\n"; 
		// parse line
		do
		{
			//{
			t = lex->GetToken();

				// get lexeme GetToken created
				//lex->GetToken();
			  

			        // get a token
				// write its name to the debug file
				// write the corresponding lexeme to the debug file
		//}
		} while (t != EOF_T)
		
		// gets next line from file
		lex->getInput();
		// i must reset after each read in
		i = 0;

	}*/
	// parse the string
	
  
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
