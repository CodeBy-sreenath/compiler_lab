%{
#include<stdio.h>
int vcount=0,ccount=0;
%}
%%
[aeiouAEIOU]    {vcount++;}
[a-zA-Z]        {ccount++;}
%%
void main()
{
printf("enter the string\n");
yylex();
printf("the number of vowels are %d\n",vcount);
printf("the total number of consonents are %d\n",ccount);
}
int yywrap()
{
return 1;
}
