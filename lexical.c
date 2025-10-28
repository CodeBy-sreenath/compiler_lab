#include<stdio.h>
#include<string.h>
#include<ctype.h>
FILE *f1;
int i=0,linecount=1,num;
char str[20];
char c;
void main()
{
f1=fopen("hello.c","r");
while((c=getc(f1))!=EOF)
{
if(isdigit(c))
{
num=c-48;
c=getc(f1);
while(isdigit(c))
{
num=num*10+(c-48);
c=getc(f1);
}
printf("%d is a number\n",num);
}
else if(isalpha(c))
{
str[i++]=c;
c=getc(f1);
while(isdigit(c)||isalpha(c)||c=='$'||c=='_')
{
str[i++]=c;
c=getc(f1);
}
str[i++]='\0';
if(strcmp("for",str)==0||strcmp("while",str)==0||strcmp("d0",str)==0||strcmp("int",str)==0||strcmp("float",str)==0||strcmp("double",str)==0||strcmp("static",str)==0)
{
printf("%s is a keyword\n",str);
}
else
{
printf("%s is an identifier\n",str);
}
ungetc(c,f1);
i=0;
}
else if(c==' '||c=='\t')
{
}
else if(c=='\n')
{
linecount+=1;
}
else
{
printf("%c is a special symbol\n",c);
}
}
printf("the total line count is %d",linecount);
}