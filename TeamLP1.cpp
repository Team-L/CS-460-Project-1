#include <stdio.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <map>
using namespace std;
/*
File: TeamLP1.cpp

Author: David Tauraso, 

Date: 2/9/17

Description:

This progaram is a lexer.

*/
int start(char a, string stream, int i, string lexeme);
int collect1(char a, string stream, int i, string lexeme);
int collect2(char a, string stream, int i, string lexeme);
int collect3(char a, string stream, int i, string lexeme);
bool alphaNotAD(char a);
bool alphaNotC(char a);
bool alphaNotRD(char a);

int detectEndOfLexeme(int state_found, int i, string lexeme, char a);

void test(char a, string stream)
{

	int i = 0;
	while(i < stream.length())
	{

		i = start(a, stream, i, "");
	}
}
//enum end_states {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
enum end_states {end_PLUS_T = 1, end_MINUS_T, end_DIV_T, end_MULT_T, end_EQUALTO_T, end_GTE_T, end_LTE_T, end_GT_T, end_LT_T, end_LPAREN_T, end_RPAREN_T, end_QUOTE_T, end_LISTOP_T, end_IDKEY_T, end_NUMLIT_T, DIV_T, MULT_T, EQUALTO_T, GTE_T, LTE_T, LPAREN_T, RPAREN_T, QUOTE_T, IDKEY_T, error};

int index(char a)
{
	string char_ = "";
	char_ += a;
	// using the ascii chart to convert char to index to column of table
	if(tolower(a) >= 'a' && tolower(a) <= 'z') return a - 97;
	if (a >= '0' && a <= '9') return 25 + (a - 48);
	// if a is +  return 36
	if(char_ == "+") return 36;
	// if a is - return 37
	if(char_ == "-") return 37;
	// if a is / return 38
	if(char_ == "/") return 38;

	// if a is * return 39
	if(char_ == "*") return 39;
	// if a is = return 40
	if(char_ == "=") return 40;
	// if a is < return 41
	if(char_ == "<") return 41;
	// if a is > return 42
	if(char_ == ">") return 42;
	// if a is ( return 43
	if(char_ == "(") return 43;
	// if a is ) return 44
	if(char_ == ")") return 44;
	// if a is ` reutrn 45
	if(char_ == "`") return 45;
	// if a is ? return 46
	if(char_ == "?") return 46;
	// if a is . return 47
	if(char_ == ".") return 47;
	// if a is _ return 48
	if(char_ == "_") return 48;

}
int main()
{


// 49 elements but table[0, 48] = 0
int table [15][49] = {
						{	2	,	2	,	1	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	2	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	6	,	3	,	-16	,	-17	,	-18	,	12	,	13	,	-21	,	-22	,    -23	,	-25	,	8	,	-25	}	,
						{	4	,	5	,	5	,	4	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-24	,	-14	,	5	}	,
						{	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-24	,	-14	,	-14	}	,
						{	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	-2	,	10	,	-2	}	,
						{	5	,	5	,	5	,	4	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	11	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	5	}	,
						{	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	5	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-14	,	-24	,	-14	,	5	}	,
						{	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	,	-1	}	,
						{	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	7	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	9	,	-15	}	,
						{	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	}	,
						{	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	}	,
						{	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	,	-25	}	,
						{	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	,	-13	}	,
						{	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-19	,	-8		-8	,	-8	,	-8	,	-8	,	-8	,	-8	,	-8	}	,
						{	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-20	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	,	-9	}	,
						{	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	14	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	,	-15	}	};


	string stream = "car+cadrabc-cons/if*else=and>==>abccadr\na_symbol1.123-12.23caddr?cddddrlist?124.-..";
	//stream = "abccar+123-123abcxyz>==<zyx";
	string lexeme = "";
	// table is missing whitespace
	char a;
	int state = 0;
	//for(int i = 0; i < 49 ; i++)
	//	cout << i << " " << table[0][i] << endl;
	//return 0;
	for(int i = 0; i < stream.length(); i++)
	{

		//USE A CLASS
		a = stream[i];
		//cout << a << endl;
		int j = index(a);
		//cout << " ( " <<  state << ", ( " << a << " -> " << j << " ) ) "  << table[state][j] << endl;

		if(table[state][j] < 0)
		{

			int state_found = table[state][j] * -1;
			//cout << "state found = "<< state_found << " " <<  end_LISTOP_T << endl;

			i = detectEndOfLexeme(state_found, i, lexeme, a);
			lexeme = "";
			state = 0;
			
		}
		else
		{
			lexeme += a;
			// if we are on last letter

				// collect lexeme
			// assume the tables will be changed
			// some tokens have to be identified here(some tokens are a match for an infinite number of lexemes)
			//cout << lexeme << endl;
			if(i == stream.length() - 1)
				cout << lexeme << endl;
			state = table[state][j];

			//cout << state << endl;
		}

	}
// if table[i][j] < 0
	//get state table[i][j] * -1
	//switch(state_found)
	//	case end_1:
	//		jfkrlgjaklfjsdl;f
	/*
	string stream2 = "abccar +123 -123abc xyz>=zyx";
	string stream3 = "(car `(a b c)) (cdr `(a b c))";

	// cons doesn't work yet so it was replaced with car
	string stream4 = "(car `a (`x y z)) (+ (* 5 6.1) (/ -4 .5) (- 3. -2.1))";
	string stream5 = "(car(cdr`(list 123 49.007)))";
	//char a;
	printf("test 1\n");
	test(a, stream);
	cout << "\n-.. should be invalid";
	cout << endl;
	printf("test 2\n");

	test(a, stream2);
	cout << endl;
	printf("test 3\n");

	test(a, stream3);
	cout << endl;
	printf("test 4\n");

	test(a, stream4);

	cout << endl;
	printf("test 5\n");
	test(a, stream5);
	*/
	// there are notes in the functions

/*
	regex object
		regex string
		int next_state

*/
/*
each regex gets you to the next state
state -> (regex, next state)
start = 0
0 -> (c, 1)
0 -> (alpha - c, 2)
0 -> (-, 3)


	multimap<int, regex object> state_regex_objects;
	// 0 is start
	state_function_id.insert(pair<int,regex object>(1,a_regex_object));
*/
	// set state
	// for each character
		// regex_objects = state_regex_objects[state]
		// new state = state
		// while new state == state
			// if check(regex_object[i].regex_string, character)

				// new state = state_regex_objects[regex_object.next_state]
				// if new state != end state
					// collect character
				// else
					// return the token the end state is associated with

	return 0;

}

int detectEndOfLexeme(int state_found, int i, string lexeme, char a)
{
	switch(state_found)
	{
		// 1
		case end_PLUS_T:
			// collect lexeme
			cout << lexeme << endl;
			i--;
			return i;
		// 2
		case end_MINUS_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 3
		case end_DIV_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 4
		case end_MULT_T:
			// collect lexeme
			cout << lexeme << endl;
			i--;

			return i;
		// 5
		case end_EQUALTO_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 6
		case end_GTE_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 7
		case end_LTE_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 8
		case end_GT_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 9
		case end_LT_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 10
		case end_LPAREN_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;
		// 11
		case end_RPAREN_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;

		// 12
		case end_QUOTE_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;

		// 13
		case end_LISTOP_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;
			return i;

		// 14
		case end_IDKEY_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;

		// 15
		case end_NUMLIT_T:
			// collect lexeme
			cout << lexeme << endl;

			i--;

			return i;

		// 16 
		case DIV_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 17
		case MULT_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 18
		case EQUALTO_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 19
		case GTE_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 20
		case LTE_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 21
		case LPAREN_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 22
		case RPAREN_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 23
		case QUOTE_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 24
		case IDKEY_T:
			// add a to lexeme
			lexeme += a;
			cout << lexeme << endl;


			// return lexeme
			return i;

		// 25
		case error:

			lexeme += a;
			// print error
			cout << "error " << lexeme << endl;

			//i--;
			return i;

	}
}
int start(char a, string stream, int i, string lexeme)
{
	// There are no stream length checks because each lexeme is inside the string.
	// detects lexemes and prints them out
	a = stream[i];

	if(a == 'c')
	{

		lexeme += a;
		i++;

		a = stream[i];

		// identifier
		if(alphaNotAD(a) || isdigit(a) || a == '_')
		{
			lexeme += a;
			i++;
			a = stream[i];
			return collect1(a, stream, i, lexeme);
		}
		// c a|d
		else if(a == 'a' || a == 'd')
		{

			lexeme += a;
			i++;
			a = stream[i];
			// c (a|d)+
			while(a == 'd')
			{
				lexeme += a;
				i++;
				a = stream[i];

			}
			// c (a|d)+ r
			if(a == 'r')
			{
				lexeme += a;

				cout << lexeme << endl;
				i++;
				// The token LISTOP_T will need to be returned here because
				// a map can't conatain an infinite number of possible lexemes this branch 
				// accepts.
				return i;
			}
			// identifier
			else if(alphaNotRD(a) || isdigit(a) || a == '=')
			{
				lexeme += a;
				i++;
				a = stream[i];
				return collect1(a, stream, i, lexeme);
			}
			// can't let 0 be returned if this option is chosen
			else
				return i;
		}
		// c is an identifier
		else
		{
			cout << lexeme << endl;
			// There is no i++ here because it was done before these branches
			return i;
		}

	}
	// lexer is convinced key words are identifiers
	// identifier
	else if(alphaNotC(a))
	{
		lexeme += a;
		i++;
		a = stream[i];
		if(isalpha(a) || isdigit(a) || a == '_')
		{
			lexeme += a;
			i++;
			a = stream[i];
			while(isalpha(a) || isdigit(a) || a == '_')
			{
				lexeme += a;
				i++;
				a = stream[i];
			}
			return collect1(a, stream, i, lexeme);
		}

		if(a == '?')
		{
			lexeme += a;
			cout << lexeme << endl;
			i++;

			return i;
		}
		else
		{
			cout << lexeme << endl;
			// no i++ because i is at a char that is not an identifier
			return i;
		}

	}
	// -
	else if(a == '-')
	{
		lexeme += a;
		i++;
		a = stream[i];
		// - (.|#)
		if(a == '.' || isdigit(a))
		{
			lexeme += a;
			i++;
			a = stream[i];
			// - (.|#)+ #* . #*
			return collect2(a, stream, i, lexeme);
		}
		else
		{
			// - is not connected to anything it should be
			cout << lexeme << endl;
			return i;
		}
	}
	else if(a == '+')
	{
		lexeme += a;
		i++;
		a = stream[i];
		if(isdigit(a))
		{
			lexeme += a;
			i++;
			a = stream[i];
			return collect2(a, stream, i, lexeme);
		}
		else
		{
			cout << lexeme << endl;

			return i;
		}
	}
	else if(isdigit(a))
	{
		lexeme += a;
		i++;
		a = stream[i];
		return collect2(a, stream, i, lexeme);
	}
	else if(a == '.')
	{
		lexeme += a;
		i++;
		a = stream[i];
		if(isdigit(a))
			return collect3(a, stream, i, lexeme);
	}
	else if(a == '/' || a == '*' || a == '=' || a == '(' || a == ')' || a == '`')
	{
		lexeme += a;
		cout << lexeme << endl;
		i++;
		return i;
	}
	else if(a == '>' || a == '<')
	{
		lexeme += a;
		i++;
		a = stream[i];
		if(a == '=')
		{
			lexeme += a;
			cout << lexeme << endl;
			i++;

			return i;
		}
		else
		{
			cout << lexeme << endl;

			return i;
		}
	}
	else
	{
		if(a == '?') cout << "-25 " << a << endl;
		i++;
		return i;
	}
}



//some of the tokens have to be determined in the automaton code

int collect1(char a, string stream, int i, string lexeme)
{
	// collects all lexemes valid for IDKEY_T
	while(isalpha(a) || isdigit(a) || a == '_')
	{
		lexeme += a;
		i++;
		a = stream[i];
	}
	if(a == '?')
	{
		lexeme += a;
		cout << lexeme << endl;
		i++;

		return i;
	}
	else
	{
		cout << lexeme << endl;
		// no i++ because i is at a char that is not an identifier
		return i;
	}

}

int collect2(char a, string stream, int i, string lexeme)
{
	// represents a function version of collect2
	// collects all numbers valid for NUMLIT_T
	// wrong
	// accepts "-.."
	// invalid input, can't be separated into any valid subparts
	// automoton is missing a state to handle -. without accepting a dot
	// already have collected the dot or isdigit
	// state 2 only needs to handle a isdigit loop or a dot branch
	// DFA has another state to be added to this to ignore "-.."
	// - (.|#)+ #*
	while(isdigit(a))
	{
		lexeme += a;
		i++;
		a = stream[i];
	}
	// - (.|#)+ #* .
	if(a == '.')
	{
		lexeme += a;
		i++;
		a = stream[i];
		// - (.|#)+ #* . #*
		return collect3(a, stream, i, lexeme);
	}
	else
	{
		cout << lexeme << endl;
		// There is no i++ here because this is an option after the while loop ends.  Also, i++ is what
		// makes the while loop end.
		return i;
	}

}
int collect3(char a, string stream, int i, string lexeme)
{
	// - (.|#)+ #* . #*
	while(isdigit(a))
	{
		lexeme += a;
		i++;
		a = stream[i];
	}
	cout << lexeme << endl;
	// There is no i++ here because this is an option after the while loop ends.  Also, i++ is what
	// makes the while loop end.

	return i;
}

bool alphaNotAD(char a)
{
	return isalpha(a) && a != 'a' && a != 'A' && a != 'd' && a != 'D';
}


bool alphaNotC(char a)
{
	return isalpha(a) && a != 'c' && a != 'C';
}

bool alphaNotRD(char a)
{
	return isalpha(a) && a != 'r' && a != 'R' && a != 'd' && a != 'D';
}

