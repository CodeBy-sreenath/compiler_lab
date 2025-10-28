#include<stdio.h>
#include<string.h>
#include<ctype.h>
int k=0,i=0,j=0,c=0,z=0;
char a[16],act[20],ac[20],stk[20];
void check();
void main()
{
puts("the grammer is E->E+E\n E->E*E\n E->(E)\n E->id");
puts("enter the input\n");
scanf("%s",a);
c=strlen(a);
strcpy(act,"SHIFT->");
puts("stack\tinput\taction");
for(j=0,i=0,k=0;j<c;j++,i++,k++)
{
if(a[j]=='i' && a[j+1]=='d')
{
stk[i]=a[j];
stk[i+1]=a[j+1];
stk[i+2]='\0';
a[j]=' ';
a[j+1]=' ';
printf("$%s\t%s\t%s\n",stk,a,act);
check();
}
else
{
stk[i]=a[j];
stk[i+1]='\0';
a[j]=' ';
printf("$%s\t%s\t%s\n",stk,a,act);
check();
}
}
}
void check()
{
strcpy(ac,"REDUCE TO E");
for(z=0;z<c;z++)
if(stk[z]=='i' && stk[z+1]=='d')
{
stk[z]='E';
stk[z+1]='\0';
printf("%s\t%s\t%s\n",stk,a,ac);
j++;
}
for(z=0;z<c;z++)
if(stk[z]=='E' && stk[z+1]=='+' && stk[z+2]=='E')
{
stk[z]='E';
stk[z+1]='\0';
stk[z+2]='\0';
printf("%s\t%s\t%s\n",stk,a,ac);
i=i-2;
}
for(z=0;z<c;z++)
if(stk[z]=='E' && stk[z+1]=='*' && stk[z+2]=='E')
{
stk[z]='E';
stk[z+1]='\0';
stk[z+2]='\0';
printf("%s\t%s\t%s\n",stk,a,ac);
i=i-2;
}
for(z=0;z<c;z++)
if(stk[z]=='(' && stk[z+1]=='E' && stk[z+2]==')')
{
stk[z]='E';
stk[z+1]='\0';
stk[z+2]='\0';
printf("%s\t%s\t%s\n",stk,a,ac);
i=i-2;
}
}
