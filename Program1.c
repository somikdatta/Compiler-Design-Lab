/*
* @author Somik Datta
* @version 1.0.0
* @description Program that accepts string containing two consecutive a's followed by two consecutive b's
*/

#include <stdio.h>

void STATE_A(char *, int);
void STATE_B(char *, int);
void STATE_C(char *, int);
void STATE_D(char *, int);
void STATE_E(char *, int);

int main()
{
    char str[30];
    printf("Transition Table For DFA :\n");
    printf("States\ta\tb\n");
    printf("->A\tB\tA\n");
    printf("  B\tC\tA\n");
    printf("  C\tC\tD\n");
    printf("  D\tB\tE\n");
    printf(" *E\tE\tE\n");
    printf("Enter the string: ");
    scanf("%s", str);
    printf("->A");
    STATE_A(str, 0);
    return 0;
}
void STATE_A(char *str, int ind)
{
    if (str[ind] == 'a')
    {
        printf("->%c->B", str[ind]);
        STATE_B(str, ind + 1);
    }
    else if (str[ind] == 'b')
    {
        printf("->%c->A", str[ind]);
        STATE_A(str, ind + 1);
    }
    else if (str[ind] == '\0')
    {
        printf("Not valid!!!\n");
    }
}
void STATE_B(char *str, int ind)
{
    if (str[ind] == 'a')
    {
        printf("->%c->C", str[ind]);
        STATE_C(str, ind + 1);
    }
    else if (str[ind] == 'b')
    {
        printf("->%c->A", str[ind]);
        STATE_A(str, ind + 1);
    }
    else if (str[ind] == '\0')
    {
        printf("Not valid\n");
    }
}
void STATE_C(char *str, int ind)
{
    if (str[ind] == 'a')
    {
        printf("->%c->C", str[ind]);
        STATE_C(str, ind + 1);
    }
    else if (str[ind] == 'b')
    {
        printf("->%c->D", str[ind]);
        STATE_D(str, ind + 1);
    }
    else if (str[ind] == '\0')
    {
        printf("Not valid\n");
    }
}
void STATE_D(char *str, int ind)
{
    if (str[ind] == 'a')
    {
        printf("->%c->B", str[ind]);
        STATE_B(str, ind + 1);
    }
    else if (str[ind] == 'b')
    {
        printf("->%c->E", str[ind]);
        STATE_E(str, ind + 1);
    }
    else if (str[ind] == '\0')
    {
        printf("\nNot valid\n");
    }
}
void STATE_E(char *str, int ind)
{
    if (str[ind] == 'a')
    {
        printf("->%c->E", str[ind]);
        STATE_E(str, ind + 1);
    }
    else if (str[ind] == 'b')
    {
        printf("->%c->E", str[ind]);
        STATE_E(str, ind + 1);
    }
    else if (str[ind] == '\0')
    {
        printf("\nString Accepted\n");
    }
}