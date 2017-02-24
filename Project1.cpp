#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"
// project 1
// David Tauraso, David Smith, Austin Lehrer
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
