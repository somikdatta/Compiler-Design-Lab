/*
* @author Somik Datta
* @version 1.0.0
* @description lexical analyzer
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h> 

#define LIMIT 200

int tokens=0;

bool isHash(char ch) 
{ 
    if (ch == '#') 
        return (true); 
    return (false); 
} 

bool isQuote(char ch) 
{ 
    if (ch == '"') 
        return (true); 
    return (false); 
} 

bool isWhiteSpaceOrNewLine(char ch) 
{ 
    if (ch == ' ' || ch=='\n') 
        return (true); 
    return (false); 
} 

bool hasHeaderEnded(char ch) 
{ 
    if (ch == '>') 
        return (true); 
    return (false); 
}

bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}') 
        return (true); 
    return (false); 
} 
  
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=') 
        return (true); 
    return (false); 
} 
  
bool isValidIdentifier(char* str) 
{ 
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true) 
        return (false); 
    return (true); 
} 
  
bool isKeyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int") 
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "char") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        return (true); 
    return (false); 
} 

bool isInteger(char* str) 
{ 
    int i, len = strlen(str); 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
            return (false); 
    } 
    return (true); 
} 
  
bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str)-1; 
    bool hasDecimal = false; 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 
  
char* lexeme(char* str, int left, int right) 
{
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 
  
void main() 
{ 
    char str[LIMIT];
    int left = 0, right = 0; 

    fgets(str, LIMIT, stdin);

    int len = strlen(str); 

    printf("Lexeme\t\t\tToken\t\t\tToken class\n");
  
    while (right <= len && left <= right) { 
        if(isHash(str[left])){
            left++;
            right++;
            while(hasHeaderEnded(str[right])==false){
                left++;
                right++;
            }
            left++;
            right++;
        }
        if(isQuote(str[left])){
            right++;
            while(isQuote(str[right])==false){
                right++;
            }
            right++;
        }
        if (isDelimiter(str[right]) == false) 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) { 
            if(!isWhiteSpaceOrNewLine(str[right])){
                printf("'%c'\t\t\t<stc, '%c'>\t\t\tSpecial Token Class\n", str[right], str[right]);
                tokens++; 
            }
            if (isOperator(str[right]) == true) {
                printf("'%c'\t\t\t<op, '%c'>\t\t\tOperator\n", str[right],str[right]); 
                tokens++;
            }
            right++; 
            left = right; 
        } else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
            char* subStr = lexeme(str, left, right - 1); 
  
            if (isKeyword(subStr) == true){
                printf("'%s'\t\t\t<kwd, '%s'>\t\t\tKeyword\n", subStr, subStr); 
                tokens++;
            }
  
            else if (isInteger(subStr) == true) {
                printf("'%s'\t\t\t<num, '%s'>\t\t\tNumber\n", subStr, subStr); 
                tokens++;
            }
  
            else if (isRealNumber(subStr) == true) {
                printf("'%s'\t\t\t<num, '%s'>\t\t\tNumber\n", subStr, subStr);
                tokens++;
            }
  
            else if (isValidIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false && !isWhiteSpaceOrNewLine(subStr[0])) {
                printf("'%s'\t\t\t<id, '%s'>\t\t\tIdentifier\n", subStr, subStr);
                tokens++;
            }
  
            else if (isValidIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false) {
                printf("'%s'\t\t\t<id, '%s'>\t\t\tInvalid Identifier\n", subStr, subStr);
                tokens++;
            }
            left = right; 
        } 
    } 
    printf("Total number of tokens = %d\n",tokens);
    return; 
} 


// Input: #include<stdio.h> #include<conio.h> void main() { int a=10,b,c; a=b*c; printf("the value of a is %d",a); getch(); }
// Output ---------------------------------------------------------------------
// Lexeme                  Token                   Token class
// 'void'                  <kwd, 'void'>                   Keyword
// 'main'                  <id, 'main'>                    Identifier
// '('                     <stc, '('>                      Special Token Class
// ')'                     <stc, ')'>                      Special Token Class
// '{'                     <stc, '{'>                      Special Token Class
// 'int'                   <kwd, 'int'>                    Keyword
// 'a'                     <id, 'a'>                       Identifier
// '='                     <stc, '='>                      Special Token Class
// '='                     <op, '='>                       Operator
// '10'                    <num, '10'>                     Number
// ','                     <stc, ','>                      Special Token Class
// 'b'                     <id, 'b'>                       Identifier
// ','                     <stc, ','>                      Special Token Class
// 'c'                     <id, 'c'>                       Identifier
// ';'                     <stc, ';'>                      Special Token Class
// 'a'                     <id, 'a'>                       Identifier
// '='                     <stc, '='>                      Special Token Class
// '='                     <op, '='>                       Operator
// 'b'                     <id, 'b'>                       Identifier
// '*'                     <stc, '*'>                      Special Token Class
// '*'                     <op, '*'>                       Operator
// 'c'                     <id, 'c'>                       Identifier
// ';'                     <stc, ';'>                      Special Token Class
// 'printf'                        <id, 'printf'>                  Identifier
// '('                     <stc, '('>                      Special Token Class
// '"the value of a is %d"'                        <id, '"the value of a is %d"'>                  Identifier
// ','                     <stc, ','>                      Special Token Class
// 'a'                     <id, 'a'>                       Identifier
// ')'                     <stc, ')'>                      Special Token Class
// ';'                     <stc, ';'>                      Special Token Class
// 'getch'                 <id, 'getch'>                   Identifier
// '('                     <stc, '('>                      Special Token Class
// ')'                     <stc, ')'>                      Special Token Class
// ';'                     <stc, ';'>                      Special Token Class
// '}'                     <stc, '}'>                      Special Token Class
// Total number of tokens = 35