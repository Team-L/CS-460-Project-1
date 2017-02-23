//description of class: ...
#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {NONE = -1, EOF_T, NUM_TOKENS};

enum end_states {end_PLUS_T = 1, end_MINUS_T, end_DIV_T, end_MULT_T, end_EQUALTO_T, end_GTE_T, end_LTE_T, end_GT_T, end_LT_T, end_LPAREN_T, end_RPAREN_T, end_QUOTE_T, end_LISTOP_T, end_IDKEY_T, end_NUMLIT_T, DIV_T, MULT_T, EQUALTO_T, GTE_T, LTE_T, LPAREN_T, RPAREN_T, QUOTE_T, IDKEY_T, error};

class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	int index(char a);
	token_type GetToken ();
	int detectEndOfLexeme(int state_found, int i, string lexeme, char a);
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
	void getInput();
	string getLine();
	ifstream& getStream();
	int getPos();
	void setEOF();

    private:
	//add table[][];

	ifstream input;
	ofstream listing;
	ofstream debug;
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
	int state;
};
	
#endif
