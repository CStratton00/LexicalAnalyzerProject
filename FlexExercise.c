%{ // variables to count the total number of characters, words, lines, and errors present in the code
int chars = 0;
int words = 0;
int lines = 0;
int errors = 0;
%}

%% // grammar error tokens
iint|intt {words++; errors++; printf("%6s : ERROR AT LINE: %i, CHAR: %i ... Did you mean int?\n", yytext, lines, chars);} // checks for the word int is mispelled
;; {chars++; errors++; printf("%6s : ERROR AT LINE: %i, CHAR: %i ... Did you mean ;?\n", yytext, lines, chars);} // checks for double semicolons

// assigns tokens in the code and adds numbers to the prior variables
test|main {words++; chars += strlen(yytext); printf("%6s : FUNCTION\n", yytext);} // produces a function token and adds to words and chars
int|bool|char|void|float|double {words++; chars += strlen(yytext); printf("%6s : TYPE\n", yytext);}
do|if|for|case|else|break|while|continue|default|return|read|write {words++; chars += strlen(yytext); printf("%6s : KEYWORD\n", yytext);}
[a-zA-Z]+ {words++; chars += strlen(yytext);printf("%6s : IDENTIFIER\n", yytext);}
[0-9]+\.[0-9]+ {chars += strlen(yytext); printf("%6s : FLOAT\n", yytext);}
[0-9]+ {chars += strlen(yytext); printf("%6s : CONSTANT\n", yytext);}
\+|-|=|\*|==|!=|<|<=|>|>=|&&|\/|\|\| {chars += strlen(yytext); printf("%6s : OPERATOR\n",yytext);}
\-|! {chars++; printf("%6s : UNARYOPERATOR\n",yytext);}
\{ {chars++; printf("%6s : LEFTCURLYBRACE\n",yytext);}
\} {chars++; printf("%6s : RIGHTCURLYBRACE\n",yytext);}
; {chars++; printf("%6s : ENDSTATEMENT\n",yytext);}
\( {chars++; printf("%6s : LEFTPARENTHESES\n",yytext);}
\) {chars++; printf("%6s : RIGHTPARENTHESES\n",yytext);}
\n {chars++; lines++;}
\  {chars++;}
\    {chars++;}
. {chars++; errors++; printf("Unrecognized character on line: %i, char: %i\n", lines, chars);}
%%

main(int argc, char **argv) {// main to read in the code to analyze
  if(argc > 1) {
          if(!(yyin = fopen(argv[1],"r"))) {
             perror(argv[1]);
             return(1);
          }
        }
        yylex();
        printf("Lines: %8d\nWords: %8d\nChars: %8d\nErrors: %7d\n", lines, words, chars, errors);
      }
