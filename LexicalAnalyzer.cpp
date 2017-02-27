#include <iomanip>
#include <cstdlib>
#include <algorithm>

#include "LexicalAnalyzer.h"

using namespace std;


static string token_names[] = {	"EOF_T" }; 

int table [15][20] = {  { 2 , 1 , 2 , 2 , 2 , 7 , 6 , 3 , -10  , -11  , -12  , 12  , 13  , -13  , -14  , -15,    -17 , 8 , -17 , -17 } ,
                      { 4 , 5 , 4 , 5 , 5 , 5 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -16  , -1  , -17 , 5 } ,
                      { 5 , 5 , 5 , 5 , 5 , 5 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -16  , -1  , -17 , 5 } ,
                      { -6  , -6  , -6  , -6  , -6  , 7 , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , -6  , 10  , -17 , -6  } ,
                      { 5 , 5 , 4 , 11  , 5 , 5 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , 5 } ,
                      { 5 , 5 , 5 , 5 , 5 , 5 , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -1  , -16  , -1  , -17 , 5 } ,
                      { -7  , -7  , -7  , -7  , -7  , 7 , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , -7  , /*-7*/9  , -17 , -7  } ,
                      { -2  , -2  , -2  , -2  , -2  , 7 , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , 9 , -17 , -2  } ,
                      { -17 , -17 , -17 , -17 , -17 , 9 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 } ,
                      { -2  , -2  , -2  , -2  , -2  , 9 , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -17 , -2  } ,
                      { -17 , -17 , -17 , -17 , -17 , 14  , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 , -17 } ,
                      { -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -3  , -17 , -3  } ,
                      { -5  , -5  , -5  , -5  , -5  , -5  , -5  , -5  , -5  , -5  , -9  , /*-5*/-17, -5  , -5  , -5  , -5  , -5  , -5  , -17 , -5  } ,
                      { -4  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -8  , -4  , -4  , -4  , -4  , -4  , -4  , -4  , -17 , -4  } ,
                      { -2  , -2  , -2  , -2  , -2  , 14  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -2  , -17 , -2  } };

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  // set input to filename
  input.open(filename);
  if(!input)
    {
      cout << filename << " does not exist.\n";
      printf ("format: proj1 <filename>\n");
      exit(1);
    }
  previous_state = 0;  
  pos = 0;
  state = 0;
  errors = 0;
  line_number = 1;
  // initalize lexemes to size 0
  lexemes.resize(0);

  token = NUM_TOKENS;
  string file_name = "";
  for(int i = 0; filename[i] != '.'; i++)

    file_name += filename[i];
  file_name += ".p1";
  debug.open(file_name.c_str());

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
  if(isalpha(tolower(a))) return 4;
  // is digit
  if(isdigit(a)) return 5;
  if(char_ == "+") return 6;
  if(char_ == "-") return 7;
  if(char_ == "/") return 8;
  if(char_ == "*") return 9;
  if(char_ == "=") return 10;
  if(char_ == "<") return 11;
  if(char_ == ">") return 12;
  if(char_ == "(") return 13;
  if(char_ == ")") return 14;
  if(char_ == "'"|| char_ == "`") return 15;
  if(char_ == "?") return 16;
  if(char_ == ".") return 17;
  if(char_ == "_") return 19;
  else
  {
      //error
      return 18;
  }
}

token_type LexicalAnalyzer::GetToken ()
{

  // This function will find the next lexeme in the input file and return
  // the token_type value associated with that lexeme
  char a;

  // creates 1 lexeme
  a = line[pos];
  int j = index(a);
  
  // We have hit an error state
  if(table[state][j] < 0)
    {

      int state_found = table[state][j] * -1;
      // only works if lexeme is not the last lexeme in string
      // pass previous state into detectEndOfLexeme
      pos = detectEndOfLexeme(state_found, pos, lexeme, a, previous_state);
      lexeme = "";
      state = 0;
      previous_state = 0;
      
    }
  // We have not hit an error state.
  else
    {
      lexeme += a;
      // save previous state
      previous_state = table[state][j];
      // if we are on last letter
      // collect lexeme
      // assume the tables will be changed
      // some tokens have to be identified here(some tokens are a match for an infinite number of lexemes)
      // lexeme is last in string
      if(pos == line.length() - 1)
    	{
          detectEndOfLexeme(previous_state, pos, lexeme, a, previous_state);
        	setEOF();
    	}
      state = table[state][j];
    }
  pos++;
  
  // return status of token
  // NONE = -1, EOF_T, NUM_TOKENS
  // forces while loop to run forever
  return token;
}
int LexicalAnalyzer::detectEndOfLexeme(int state_found, int i, string lexeme, char a, int previous_state)
{
  // finds end of lexeme
  // sets token enum
  switch(state_found)
    {
      // 1
    case end_IDKEY_T:
      // collect lexeme
      // find out if identifier is a keyword or predicate lexeme
      lexemes.push_back(lexeme);

      token = IDENT;

      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;
      lexemes.resize(0);

      setEOF();
      i--;
      return i;
      
      // 2
    case end_NUMLIT_T:
      // collect lexeme

      token = NUM_TOKENS;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      i--;
      return i;
      
      // 3
    case end_LISTOP_T:
      // collect lexeme

      token = LISTOP;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      i--;
      return i;      
      
      // 4
    case end_LT_T:
      // collect lexeme
      token = LT;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      i--;
      return i;
    
      // 5
    case end_GT_T:
      // collect lexeme
      token = GT;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      i--;
      return i;
      
      // 6
    case end_MINUS_T:
      // collect lexeme
      token = MINUS;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      i--;
      return i;
      
      // 7
    case end_PLUS_T:
      // collect lexeme
      token = PLUS;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;
      setEOF();
      i--;
      return i;

      // 8 
    case LTE_T:
      // add a to lexeme
      lexeme += a;

      token = LTE;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 9
    case GTE_T:
      // add a to lexeme
      lexeme += a;
      token = GTE;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 10
    case DIV_T:
      // add a to lexeme
      lexeme += a;

      token = DIV;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 11
    case MULT_T:
      // add a to lexeme
      lexeme += a;

      token = MULT;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 12
    case EQUALTO_T:
      // add a to lexeme
      lexeme += a;

      token = EQUALTO;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 13
    case LPAREN_T:
      // add a to lexeme
      lexeme += a;

      token = LPAREN;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 14
    case RPAREN_T:
      // add a to lexeme
      lexeme += a;

      token = RPAREN;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;

      setEOF();
      return i;

      // 15
    case QUOTE_T:
      // add a to lexeme
      lexeme += a;

      token = QUOTE;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;


      setEOF();
      return i;

      // 16
    case IDKEY_T:
      // add a to lexeme
      lexeme += a;


      lexemes.push_back(lexeme);
      token = IDENT;
      debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;
      lexemes.resize(0);


      setEOF();
      return i;

      // 17
    case error:

      // these are states that require peaking to detect end
      if(previous_state == 11 || previous_state == 1 || previous_state == 5 || previous_state == 2 || previous_state == 3 || previous_state == 14 || previous_state == 6 || previous_state == 7 || previous_state == 9 || previous_state == 12 || previous_state == 13)
      {
        if(lexeme.size() > 0)
        {

          if(previous_state == 11)
            token = LISTOP;
          else if(previous_state == 1)
          {


            token = IDENT;
            lexemes.push_back(lexeme);
          }
          else if(previous_state == 5)
          {

            token = IDENT;
            lexemes.push_back(lexeme);
          }
          else if(previous_state == 2)
          {

            token = IDENT;
            lexemes.push_back(lexeme);
          }
          else if(previous_state == 3)
            token = MINUS;
          // NUM_TOKENS == NUMLIT
          else if(previous_state == 14)
            token = NUM_TOKENS;
          else if(previous_state == 6)
            token = PLUS;
          else if(previous_state == 7)
            token = NUM_TOKENS;
          else if(previous_state == 9)
           token =  NUM_TOKENS;
          else if(previous_state == 12)
           token =  GT;
          else if(previous_state == 13)
           token =  LT;

         debug << left << setw(15) << GetTokenName(token) << setw(10) << lexeme << endl;
         lexemes.resize(0);

        }
        i--;

        token = NONE;
        setEOF();
        return i;
      }
      // if previous state is any of the following
         // assume lexeme is valid
      // cases 1 and 2 must be separate
      // have each casse return separately
      // a space should not be an error
      // doesn't visit this case
      if(a == ' ' || a == '\t')
      {       

        setEOF();

        return i;
      }
      // if lexeme is empty
      // error case
      if(lexeme.size() == 0)
      {
        lexeme += a;

        // save line number, col number and error lexeme
        debug << left << setw(15) << "ERROR_T" << lexeme << endl;

        token = NONE;
        errors++;
        setEOF();
        return i;
      }
      // error case
      if(lexeme.size() > 0)
      {

        debug << left << setw(15) << "ERROR_T" << lexeme << endl;

        i--;
        token = NONE;
        errors++;
        setEOF();
        return i;
      }
      // if lexeme ends in ? and idkey case has been ignored
      // error case

      else if(a == '?')
      {
        lexeme += a;

        debug << left << setw(15) << "ERROR_T" << lexeme << endl;


        token = NONE;
        errors++;
        setEOF();

        return i;
      }
      

    }
}

//example of token is LISTOP_T
string LexicalAnalyzer::GetTokenName (token_type t) const
{
  
  // The GetTokenName function returns a string containing the name of the
  // token passed to it. 
    switch(t)
    {
      case NONE:
           return "";
      case EOF_T:
           return "EOF_T";
      case NUM_TOKENS:
           return "NUMLIT_T";
      case IDENT:
           return idenCheck(lexemes[0]);
      case LISTOP:
           return "LISTOP_T";
      case PLUS:
           return "PLUS_T";  
      case MINUS:
           return "MINUS_T";
      case DIV:
           return "DIV_T";
      case MULT:
           return "MULT_T";
      case EQUALTO:
           return "EQUALTO_T";
      case LT:
           return "LT_T";
      case GT:
           return "GT_T";
      case GTE:
           return "GTE_T";
      case LTE:
           return "LTE_T";
      case LPAREN:
           return "LPAREN_T";
      case RPAREN:
           return "RPAREN_T";
      case QUOTE:
           return "QUOTE_T";
      default:
            return "";
    }       

}

string LexicalAnalyzer::GetLexeme () const
{
  // This function will return the lexeme found by the most recent call to 
  // the get_token function
  return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
  // This function will be called to write an error message to a file
}
void LexicalAnalyzer::getInput()
{
  // part of creation of infinite loop
  getline(input, line);
  pos = 0;
  state = 0;
  token = NUM_TOKENS;
  lexeme = "";  
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
   {
      token = EOF_T;
      debug << GetTokenName(token) << endl;
      //tokens.push_back(GetTokenName(token));
    }
}
void Print(string a)
{
  cout << a << " ";
}
void LexicalAnalyzer::fileName(string source_file_name)
{
  //print file name to dbg

    debug << "Input file: " << source_file_name << endl;

}
void LexicalAnalyzer::dbgFile(string line)
{

  //say what line you are on and print that line.
  debug << line_number << ": " << line << endl;

  
}

void LexicalAnalyzer::closeFile()
{
  debug.close();
}
string LexicalAnalyzer::idenCheck(string lexeme1) const
{

       if(lexeme1[lexeme1.size() - 1] == '?')
       {

            if(lexeme1 == "number?")
                    return "NUMBERP_T";
            if(lexeme1 == "symbol?")
                    return "SYMBOLP_T";
            if(lexeme1 == "list?")
                    return "LISTP_T";
            if(lexeme1 == "zero?")
                    return "ZEROP_T";
            if(lexeme1 == "null?")
                    return "NULLP_T";
            if(lexeme1 == "char?")
                    return "CHARP_T";
            if(lexeme1 == "string?")
                    return "STRINGP_T";
       }
       if(lexeme1.length() ==2)
       {
            if(lexeme1 == "if")
                    return "IF_T";
            if(lexeme1 == "or")
                    return "OR_T";
       }
       if(lexeme1.length() == 3)
       {

            if(lexeme1 == "cons")
                    return "CONS_T";
            if(lexeme1 == "and")
                    return "AND_T";
            if(lexeme1 == "not")
                    return "NOT_T";
       }
       if(lexeme1 == "while")
            return "WHILE_T";
       if(lexeme1 == "define")
            return "DEFINE_T";
       
       return "IDENT_T";

}


void LexicalAnalyzer::incrementLineNumber()
{
    line_number++;
}




