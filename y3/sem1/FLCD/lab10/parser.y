%{
extern int yylex(void);
#include <stdio.h>
#include <stdlib.h>

int yyerror(char *s);

#define YYDEBUG 1
%}

%token DEF;
%token INT;
%token STR;
%token CHAR;
%token READ;
%token IF;
%token ELSE;
%token PRINT;
%token WHILE;
%token DO;
%token FOR;
%token RET;
%token MAIN;
%token LEN;
%token GET_ELEM;
%token ARR;
%token ELIF;

%token PLUS;
%token MINUS;
%token TIMES;
%token DIV;
%token LESS;
%token LESSEQ;
%token EQ;
%token NEQ;
%token BIGGEREQ;
%token EQQ;
%token BIGGER;
%token AND;
%token OR;
%token MOD;
%token ADD1;

%token CURLYOPEN;
%token CURLYCLOSE;
%token SEMICOLON;
%token OPEN;
%token CLOSE;
%token BRACKETOPEN;
%token BRACKETCLOSE;
%token COMMA;
%token DOT;

%token IDENTIFIER;
%token INTCONSTANT;
%token STRINGCONSTANT;

%start Program

%%
Program : MAIN BRACKETOPEN CompoundStatement BRACKETCLOSE SEMICOLON { printf("Program -> main { CompoundStatement }\n"); }
	| DEF IDENTIFIER OPEN DeclarationStatement CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE SEMICOLON    { printf("Program -> def IDENTIFIER [ DeclarationStatement ]  ( CompoundStatement )\n"); }
        ;
CompoundStatement : Statement SEMICOLON CompoundStatement    { printf("CompoundStatement -> Statement ; CompoundStatement\n"); }
                  | Statement SEMICOLON                      { printf("CompoundStatement -> Statement ;\n"); }
                  ;
Statement : DeclarationStatement    { printf("Statement -> DeclarationStatement\n"); }
          | AssignmentStatement     { printf("Statement -> AssignmentStatement\n"); }
          | IfStatement             { printf("Statement -> IfStatement\n"); }
          | WhileStatement          { printf("Statement -> WhileStatement\n"); }
          | ForStatement            { printf("Statement -> ForStatement\n"); }
          | PrintStatement          { printf("Statement -> PrintStatement\n"); }
          | ReadStatement           { printf("Statement -> ReadStatement\n"); }
          | ReturnStatement         { printf("Statement -> ReturnStatement\n"); }
          ;
DeclarationStatement : Type IDENTIFIER COMMA DeclarationStatement    { printf("DeclarationStatement -> Type IDENTIFIER , DeclarationStatement\n"); }
                     | Type IDENTIFIER                               { printf("DeclarationStatement -> Type IDENTIFIER\n"); }
                     | ARR LESS Type BIGGER IDENTIFIER               { printf("DeclarationStatement -> arr IDENTIFIER\n"); }
                     ;
Type : INT    { printf("Type -> integer\n"); }
     | STR    { printf("Type -> string\n"); }
     | CHAR   { printf("Type -> char\n"); }
     ;
AssignmentStatement : Type IDENTIFIER EQ Expression        { printf("AssignmentStatement -> Type IDENTIFIER = Expression\n"); }
                    | Type IDENTIFIER EQ STRINGCONSTANT    { printf("AssignmentStatement -> Type IDENTIFIER = STRINGCONSTANT\n"); }
                    | IDENTIFIER ADD1                      { printf("AssignmentStatement -> Type IDENTIFIER++\n"); }
                    | IDENTIFIER PLUS EQ Expression        { printf("AssignmentStatement -> IDENTIFIER += Expression\n"); }
                    ;
Expression : Expression PLUS Term     { printf("Expression -> Expression + Term\n"); }
           | Expression MINUS Term    { printf("Expression -> Expression - Term\n"); }
           | ArrayExpression          { printf("Expression -> ArrayExpression\n"); }
           | Term                     { printf("Expression -> Term\n"); }
           ;
ArrayExpression : IDENTIFIER DOT LEN                         { printf("ArrayExpression -> IDENTIFIER .  length\n"); }
                | IDENTIFIER DOT GET_ELEM OPEN Term CLOSE    { printf("ArrayExpression -> IDENTIFIER . get_elem [ Term ]\n"); }
                ;
Term : Term TIMES Factor    { printf("Term -> Term * Factor\n"); }
     | Term DIV Factor      { printf("Term -> Term / Factor\n"); }
     | Term MOD Factor      { printf("Term -> Term mod Factor\n"); }
     | Factor               { printf("Term -> Factor\n"); }
     ;
Factor : OPEN Expression CLOSE    { printf("Factor -> ( Expression )\n"); }
       | IDENTIFIER               { printf("Factor -> IDENTIFIER\n"); }
       | INTCONSTANT              { printf("Factor -> INTCONSTANT\n"); }
       | MINUS IDENTIFIER         { printf("Factor -> - IDENTIFIER\n"); }
       ;
IfStatement : IF OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE                                                                                                                         { printf("IfStatement -> if [ Expression ] ( CompoundStatement )\n"); }
            | IF OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE ELIF OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE                                                    { printf("IfStatement -> if [ Expression ] ( CompoundStatement ) elif [ Expression ] ( CompoundStatement )\n"); }
            | IF OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE ELIF OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE ELSE BRACKETOPEN CompoundStatement BRACKETCLOSE    { printf("IfStatement -> if [ Expression ] ( CompoundStatement ) elif [ Expression ] ( CompoundStatement ) else { CompoundStatement }\n"); }
            | IF OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE ELSE BRACKETOPEN CompoundStatement BRACKETCLOSE                                                                         { printf("IfStatement -> if [ Expression ] ( CompoundStatement ) else { CompoundStatement }\n"); }
            ;
WhileStatement : WHILE OPEN Condition CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE    { printf("WhileStatement -> while [ Expression ] ( CompoundStatement )\n"); }
               ;
ForStatement : FOR OPEN AssignmentStatement SEMICOLON Condition SEMICOLON AssignmentStatement CLOSE BRACKETOPEN CompoundStatement BRACKETCLOSE    { printf("ForStatement -> for [ AssignmentStatement ; Condition ; AssignmentStatement ] ( CompoundStatement )\n"); }
             ;
PrintStatement : PRINT OPEN Expression CLOSE        { printf("PrintStatement -> print [ Expression ]\n"); }
               | PRINT OPEN STRINGCONSTANT CLOSE    { printf("PrintStatement -> print [ STRINGCONSTANT ]\n"); }
               ;
ReadStatement : READ OPEN IDENTIFIER CLOSE    { printf("ReadStatement -> read [ IDENTIFIER ]\n"); }
              ;
ReturnStatement : RET IDENTIFIER    { printf("ReturnStatement -> ret IDENTIFIER\n"); }
              ;
Condition : Expression Relation Expression AND Condition    { printf("Condition -> Expression Relation Expression AND Condition\n"); }
          | Expression Relation Expression OR Condition     { printf("Condition -> Expression Relation Expression OR Condition\n"); }
          | Expression Relation Expression                  { printf("Condition -> Expression Relation Expression\n"); }
          ;
Relation : LESS        { printf("Relation -> <\n"); }
         | LESSEQ      { printf("Relation -> <=\n"); }
         | EQQ         { printf("Relation -> ==\n"); }
         | NEQ         { printf("Relation -> <>\n"); }
         | BIGGEREQ    { printf("Relation -> >=\n"); }
         | BIGGER      { printf("Relation -> >\n"); }
	     | AND         { printf("Relation -> &&\n"); }
	     | OR          { printf("Relation -> ||\n"); }
         ;
%%
int yyerror(char *s) {
    printf("Error: %s", s);
}

extern FILE *yyin;

int main(int argc, char** argv) {
    if (argc > 1) 
        yyin = fopen(argv[1], "r");
    if (!yyparse()) 
        fprintf(stderr, "\tOK\n");
}