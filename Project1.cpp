#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"

/*
File: Project1.cpp

Author: David Tauraso, David Smith, Austin Lehrer

Date: 2/22/17

Description:

This progaram is a lexical analyzer.

*/
int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf ("format: proj1 <filename>\n");
		exit (1);
	}
    	SetLimits ();

	SyntacticalAnalyzer parser (argv[1]);
	/*
	works on test_individuals for the following part
	car

	cadr
	caddr
	*/
	//parser->()


	return 0;
}
