#include<stdio.h>
#include<string.h>
#include<ctype.h>
int error=0,i=0;
char input[100];
void E();
void Eprime();
void T();
void Tprime();
void F();
void E()
{
T();
Eprime();
}
void Eprime()
{
if(i<strlen(input) && input[i]=='+')
{
i++;
T();
Eprime();
}
}
void T()
{
F();
Tprime();
}
void Tprime()
{
if(i<strlen(input) && input[i]=='*')
{
i++;
F();
Tprime();
}
}
void F()
{
if(i<strlen(input) && input[i]=='(')
{
i++;
E();
if(i<strlen(input) && input[i]==')')

i++;
else
error=1;
}
else if(i<strlen(input) &&  isalpha(input[i]))
{
i++;
while(isalnum(input[i]) || input[i]=='_')
i++;
}
else
{
error=1;
}
}
int main()
{
printf("enter the arithmetic expression\n");
fgets(input,sizeof(input),stdin);
input[strcspn(input,"\n")]='\0';
E();
if(i==strlen(input) && error==0)
{
printf("accepted\n");
}
else
{
printf("rejected\n");
}
return 0;
}
 

