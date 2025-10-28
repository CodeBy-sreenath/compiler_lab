  GNU nano 8.0                                                                                                      count6.l                                                                                                                
%{
#include<stdio.h>
int lc=0,sc=0,wc=0,cc=0;
%}
%%
[\n]    {lc++;}
[\t]    {sc++;}
[" "]   {sc++;}
[^\n\t]+        {wc++; cc+=yyleng;}
%%
void main()
{
printf("enter the input\n");
yylex();
printf("the total line count is %d\n",lc);
printf("the total number of space is %d\n",sc);
printf("the total number of words is %d\n",wc);
printf("the total number of characters are %d\n",cc);
}
int yywrap()
{
return 1;
}

