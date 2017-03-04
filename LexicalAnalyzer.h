//description of class: ...
#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
using namespace std;

enum token_type {NONE = -1, EOF_T, NUM_TOKENS, IDENT, IDKEY, NUMLIT, LISTOP, LT, GT, MINUS, PLUS, LTE, GTE, DIV, MULT, EQUALTO, LPAREN, RPAREN, QUOTE};
enum end_states {end_IDKEY_T = 1 ,end_NUMLIT_T, end_LISTOP_T, end_GT_T, end_LT_T, end_MINUS_T, end_PLUS_T, GTE_T, LTE_T, DIV_T, MULT_T, EQUALTO_T, LPAREN_T, RPAREN_T, QUOTE_T, IDKEY_T, error};

class ErrorToken
{

	public:
		ErrorToken(int column_in, string error_lexeme_in)
		{
			column_number = column_in;
			error_lexeme = error_lexeme_in;
		}
		string output(int line_number)
		{
			// convert line_number and column_number to strings
			// int -> string
			return "error at" + intToString(line_number) + intToString(column_number) + error_lexeme;
		}
		string intToString(int number)
		{
			string number_converted = "";
			while(number > 0)
			{
				//pull out a digit
				int digit = number % 10;
				number /= 10;
				//convert it to ascii
				char new_digit = digit + 48;
				//add to end of string

				number_converted = new_digit + number_converted;
			}
			return number_converted;
		}
		int getColumnNumber()
		{
			return column_number;
		}
	private:
		int column_number;
		string error_lexeme;
};
class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	int index(char a);
	token_type GetToken ();
	int detectEndOfLexeme(int state_found, int i, string lexeme, char a, int previous_state);
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError ();
	void getInput();
	string getLine();
	ifstream& getStream();
	int getPos();
	void setEOF();
	void fileName(string source_file_name);
	void dbgFile(string line);
	void closeFile();
	string idenCheck(string lexeme1) const;
	void incrementLineNumber();
	
    private:
	int previous_state;
	ifstream input;
	ofstream p1;
	ofstream listing;
	ofstream debug;
	token_type token;
	string line;
	string line_for_output;
	int line_number;
	int pos;
	string lexeme;
	int errors;
	int state;
	vector<string> lexemes;

	string token_name;
};
	
#endif
