#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T" }; 
int table [15][49] = {
            { 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 6 , 3 , -16 , -17 , -18 , 12  , 13  , -21 , -22 ,    -23  , -25 , 8 , -25 } ,
            { 4 , 5 , 5 , 4 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -24 , -14 , 5 } ,
            { 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -24 , -14 , -14 } ,
            { -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , 10  , -2  } ,
            { 5 , 5 , 5 , 4 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 11  , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , 5 } ,
            { 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -14 , -24 , -14 , 5 } ,
            { -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  } ,
            { -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , 9 , -15 } ,
            { -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 } ,
            { -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 } ,
            { -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , 14  , 14  , 14  , 14  , 14  , 14  , 14  , 14  , 14  , 14  , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 , -25 } ,
            { -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 , -13 } ,
            { -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -8  , -19 , -8    -8  , -8  , -8  , -8  , -8  , -8  , -8  } ,
            { -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -20 , -9  , -9  , -9  , -9  , -9  , -9  , -9  , -9  } ,
            { -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , 14  , 14  , 14  , 14  , 14  , 14  , 14  , 14  , 14  , 14  , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 , -15 } };

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // set input to filename
  input.open(filename);
  if(!input)
      cout << filename << " does not exist.\n";
  //input >> line;
  // set ofstream listing to listing file
  // set ofstream debug to debug file
  pos = 0;
  state = 0;
  token = NUM_TOKENS;
  // This function will initialize the lexical analyzer class
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
  
  // This function will complete the execution of the lexical analyzer class
}
int LexicalAnalyzer::index(char a)
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

  else
    {
      cout << "char " << char_;
      return -1;
    }

}
//
token_type LexicalAnalyzer::GetToken ()
{

  // This function will find the next lexeme in the input file and return
  // the token_type value associated with that lexeme
  char a;

  // creates 1 lexeme
  //cout << "line[pos] pos : " << pos <<endl;
    a = line[pos];
    //cout << pos;
    //cout << a << endl;
    int j = index(a);
    cout << " ( " <<  state << ", ( " << a << " -> " << j << " ) ) "  << table[state][j] << endl;
    //cout << table[state][j];
    if(table[state][j] < 0)
    {

      int state_found = table[state][j] * -1;
      //cout << "state found = "<< state_found << " " <<  end_LISTOP_T << endl;
      // only works if lexeme is not the last lexeme in string
      pos = detectEndOfLexeme(state_found, pos, lexeme, a);
      lexeme = "";
      state = 0;
      
    }
    else
    {
     lexeme += a;
     //cout << "long lexeme " << lexeme << endl;
     //cout << "pos " << pos << endl;
      // if we are on last letter

        // collect lexeme
      // assume the tables will be changed
      // some tokens have to be identified here(some tokens are a match for an infinite number of lexemes)
      //cout << lexeme << endl;
      // lexeme is last in string
      if(pos == line.length() - 1)
      {
          cout << lexeme << endl;
        //  token = EOF_T;
          setEOF();
      }
      state = table[state][j];
      //cout << "state " << state << endl;
      // it is stuck on the c
      //cout << state;
    }
  pos++;
//cout << token << endl;

  // return status of token
  // NONE = -1, EOF_T, NUM_TOKENS

  // forces while loop to run forever
  //token = NONE;
  return token;
}
int LexicalAnalyzer::detectEndOfLexeme(int state_found, int i, string lexeme, char a)
{
  switch(state_found)
  {
    // 1
    case end_PLUS_T:
      // collect lexeme
      cout  << "lexeme "<< lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;
      return i;
    // 2
    case end_MINUS_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 3
    case end_DIV_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 4
    case end_MULT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 5
    case end_EQUALTO_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 6
    case end_GTE_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 7
    case end_LTE_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 8
    case end_GT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 9
    case end_LT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 10
    case end_LPAREN_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 11
    case end_RPAREN_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;

    // 12
    case end_QUOTE_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;

    // 13
    case end_LISTOP_T:
      // collect lexeme
      cout << "lexemew " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;
      return i;

    // 14
    case end_IDKEY_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;

    // 15
    case end_NUMLIT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;

    // 16 
    case DIV_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 17
    case MULT_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 18
    case EQUALTO_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 19
    case GTE_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 20
    case LTE_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 21
    case LPAREN_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 22
    case RPAREN_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 23
    case QUOTE_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 24
    case IDKEY_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 25
    case error:

      lexeme += a;
      // print error
      cout << "error " << lexeme << endl;
      token = NONE;
      setEOF();
      //i--;
      return i;

  }
}

//example of token is LISTOP_T
string LexicalAnalyzer::GetTokenName (token_type t) const
{
  
  // The GetTokenName function returns a string containing the name of the
  // token passed to it. 

  // non if lexeme is invalid
  // eof_t if hit end of file and EOF_T token was found
  // numtokens if a valid lexeme was found
  return "";
}

string LexicalAnalyzer::GetLexeme () const
{
  // This function will return the lexeme found by the most recent call to 
  // the get_token function
  return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
  // This function will be called to write an error message to a file
}
void LexicalAnalyzer::getInput()
{

    input >> line;

    pos = 0;
    state = 0;
    token = NUM_TOKENS;
    lexeme = "";
    //cout << line;
}
string LexicalAnalyzer::getLine()
{
  return line;
}
ifstream& LexicalAnalyzer::getStream()
{
  return input;
}

int LexicalAnalyzer::getPos()
{

  return pos;
}
void LexicalAnalyzer::setEOF()
{
    // if input got last line
    if(input.eof())
      token = EOF_T;
}