#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;


static string token_names[] = {	"EOF_T" }; 

int table [15][20] = {  { 2 , 1 , 2 , 2 , 2 , 7 , 6 , 3 , -10  , -11  , -12  , 12  , 13  , -13  , -14  , -15,    -17 , 8 , -17 , -17 } ,
                      { 4 , 5 , 4 , 5 , 5 , 5 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -16  , -1  , -17 , 5 } ,
                      { 5 , 5 , 5 , 5 , 5 , 5 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -16  , -1  , -17 , 5 } ,
                      { -6  , -6  , -6  , -6  , -6  , 7 , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , 10  , -17 , -6  } ,
                      { 5 , 5 , 4 , 11  , 5 , 5 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , 5 } ,
                      { 5 , 5 , 5 , 5 , 5 , 5 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -16  , -1  , -17 , 5 } ,
                      { -7  , -7  , -7  , -7  , -7  , 7 , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -17 , -7  } ,
                      { -2  , -2  , -2  , -2  , -2  , 7 , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , 9 , -17 , -2  } ,
                      { -17 , -17 , -17 , -17 , -17 , 9 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 } ,
                      { -2  , -2  , -2  , -2  , -2  , 9 , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -17 , -2  } ,
                      { -17 , -17 , -17 , -17 , -17 , 14  , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 } ,
                      { -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -17 , -3  } ,
                      { -5  , -5  , -5  , -5  , -5  , -5  , -5  , -5  , -5  , -5  , -9  , -5    -5  , -5  , -5  , -5  , -5  , -5  , -17 , -5  } ,
                      { -4  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -8  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -17 , -4  } ,
                      { -2  , -2  , -2  , -2  , -2  , 14  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -17 , -2  } };

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

  if(char_ == "a") return 0;
  if(char_ == "c") return 1;
  if(char_ == "d") return 2;
  if(char_ == "r") return 3;

  // isalpha (upper and lower cases)  
  if(isalpha(a)) return 4;


    // else a
    // else c
    // else d
    // else r
  // is digit
  if(isdigit(a)) return 5;


  // using the ascii chart to convert char to index to column of table
  //if(tolower(a) >= 'a' && tolower(a) <= 'z') return a - 97;
  //if (a >= '0' && a <= '9') return 25 + (a - 48);
  // if a is +  return 36
  if(char_ == "+") return 6;
  // if a is - return 37
  if(char_ == "-") return 7;
  // if a is / return 38
  if(char_ == "/") return 8;

  // if a is * return 39
  if(char_ == "*") return 9;
  // if a is = return 40
  if(char_ == "=") return 10;
  // if a is < return 41
  if(char_ == "<") return 11;
  // if a is > return 42
  if(char_ == ">") return 12;
  // if a is ( return 43
  if(char_ == "(") return 13;
  // if a is ) return 44
  if(char_ == ")") return 14;
  // if a is ` reutrn 45
  if(char_ == "'") return 15;
  // if a is ? return 46
  if(char_ == "?") return 16;
  // if a is . return 47
  if(char_ == ".") return 17;
  // if a is _ return 48
  if(char_ == "_") return 19;

  // anything else = 18
  else
    {
      //cout << char_;
      return 18;
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
    //cout << " ( " <<  state << ", ( " << a << " -> " << j << " ) ) "  << table[state][j] << endl;
    //cout << table[state][j];
    if(table[state][j] < 0)
    {

      int state_found = table[state][j] * -1;
      //cout << "state found = "<< state_found << " " <<  -3 << endl;
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
          cout << "lexeme " << lexeme << endl;
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
    //enum end_states = {end_IDKEY_T = 1 ,end_NUMLIT_T, end_LISTOP_T, end_LT_T, end_GT_T, end_MINUS_T, end_PLUS_T, LTE_T, GTE_T, DIV_T, MULT_T, EQUALTO_T, LPAREN_T, RPAREN_T, QUOTE_T, IDKEY_T, error};
    // 1
    case end_IDKEY_T:
      // collect lexeme
      cout  << "lexeme "<< lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    
    // 2
    case end_NUMLIT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    
    // 3
    case end_LISTOP_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;      
    // 4
    case end_LT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 5
    case end_GT_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 6
    case end_MINUS_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    // 7
    case end_PLUS_T:
      // collect lexeme
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();
      i--;

      return i;
    

      // string match lexeme against all keywords and predicates to find the right token
      // if match fails then token is -16
      // collect lexeme

    // 16 
    case LTE_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 17
    case GTE_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 18
    case DIV_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 19
    case MULT_T:
      // add a to lexeme
      lexeme += a;
      cout << "lexeme " << lexeme << endl;
      token = NUM_TOKENS;
      setEOF();

      // return lexeme
      return i;

    // 20
    case EQUALTO_T:
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

    // can't tell the difference between a valid ending char for the state and an actual error
    // 25
    case error:

      // cases 1 and 2 must be separate
      // have each casse return separately
      // a space should not be an error
      if(a == ' ')
      {
        //cout << "|" << a << "| is not an error" << endl;
        // empty lexemes are being recognized
        if(lexeme.size() > 0) cout << "lexeme " << lexeme << endl;

        setEOF();
        //i++;
        return i;
      }
      // if lexeme is empty
      if(lexeme.size() == 0)
      {
              cout << "error " << a << endl;
              token = NONE;
              setEOF();
      }
        // actual error
      // if lexeme ends in ? and idkey case has been ignored
      else if(a == '?')
      {
              cout << "error " << a << endl;
              token = NONE;
              setEOF();
        // error
      }
      else
      {
        // end state
        // collect and leave
        // i--
        cout << "lexeme " << lexeme << endl;

        lexeme += a;
        token = NONE;
        setEOF();
        // print -17

        i--;
      }
      return i;

  }
}

//example of token is LISTOP_T
string LexicalAnalyzer::GetTokenName (token_type t) const
{
  
  // The GetTokenName function returns a string containing the name of the
  // token passed to it. 

  //end_IDKEY_T = 1 ,end_NUMLIT_T, end_LISTOP_T, end_LT_T, end_GT_T, end_MINUS_T, end_PLUS_T, LTE_T, GTE_T,
  // DIV_T, MULT_T, EQUALTO_T, LPAREN_T, RPAREN_T, QUOTE_T, IDKEY_T, error
/* once the enum is in the proper places and all that. 
switch(t){
  case IDKEY:
       return "IDKEY_T";
  case NUMLIT:
       return "NUMLIT_T";
  case LISTOP:
       return "LISTOP_T";
  case LT:
       return "LT_T";
  case LTE:
       return "LTE_T";
  case GT:
       return "GT_T";
  case GTE:
       return "GTE_T";
  case MINUS:
       return "MINUS_T";
  case PLUS:
       return "PLUS_T";
  case DIV:
       return "DIV_T";
  case MULT:
       return "MULT_T";
  case EQUALTO:
       return "EQUALTO_T";
  case LPAREN:
       return "LPAREN_T";
  case RPAREN:
       return "RPAREN_T";
  case QUOTE:
       return "QUOTE_T";
  case ERROR:
       return "ERROR";
  }
  */

  // non if lexeme is invalid
  // eof_t if hit end of file and EOF_T token was found
  // numtokens if a valid lexeme was found
  //test enum output NONE = -1, EOF_T, NUM_TOKENS
  switch(t){
            case NONE:
                 return ""
            case EOF_T:
                 return "EOF_T";
            case NUM_TOKENS:
                 return "NUMTOKEN_T";
  }
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
  // This function will be called to write an -17 message to a file
}
void LexicalAnalyzer::getInput()
{

    // part of creation of infinite loop
    getline(input, line);

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
