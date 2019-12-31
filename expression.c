#include<stdio.h>
#include<math.h>
#include<string.h>

#define N 100

int length;

char arr[N];
int top;
void inittop()
{
	top=-1;
}
void push(char x)
{
	arr[++top]=x;
	
}
char pop()
{
	if(top==-1)
		printf("stack empty");
	char x=arr[top];
	top--;
	return x;
}
int validat(char exp[N])
{
	int i;
	//printf("length= %d\n",length);
	//printf("\n%s\n",exp);
	
	for(i=0;i<length;i++)
	{
		//printf("\n%c \t",exp[i]);
		if((exp[i]<'(')||(exp[i]>'9'))
		{
			printf("\n%c is not a number or operator\n",exp[i]);
			return 0;
		}
			
		if(exp[i]=='(')
		{
			arr[++top]=exp[i];
			//printf("hi in 1\n");
		}
			
		else if(exp[i]==')')
		{
			//printf("hi in 2 top=%d\n",top);
			if(top==(-1))
			{
				printf("\nbrackets are not in proper order\n");
				return 0;
			}
				
			pop();
		}
		//printf("hiiiiiiiiii");	
	}
	if(top!=-1)
	{
		printf("extra '(' added in expression\n");
		return 0;
	}
	if(exp[0]=='('||(exp[0]>=48&&exp[0]<=57)||exp[0]=='-')
			return 1;
	else
	{
		printf("\n First character %c not allowed\n",exp[0]);
		return 0;
	}
			
	return 1;
}
int getPriority(char x)
{
	switch(x){
		case '+':
		case '-':return 1;
		case '*':
		case '/':return 2;
	
		case '^':return 3;
		case '(':
		case ')':return 0;
	}
}
void eval(char* string)
{
	//printf("string =%s",string);
	int i;
	int l=strlen(string);
	//printf("string length=%d\n",l);
	for(i=0;i<l;i++)
	{
		
		arr[i]=NULL;
	}
	for(i=0;i<l;i++)
	{
		if(isdigit(string[i]))
			push(string[i]-'0');
		else{
			int val1=pop();
			int val2=pop();
			//printf("\n vals %d\t%d\n",val1,val2);
			switch(string[i])
			{
				case '+':push(val1+val2);
						 break;
				case '-':push(val2-val1);
						 break;
				case '*':push(val2*val1);
						 break;
				case '/':push(val2/val1);
						 break;
				case '^':push(pow(val2,val1));
						 break;
				default:printf("end\n");
			}
		}
	}
	printf("\nans=  %d",pop());
}
void prefix(char exp[N])
{	
	
	char prefix[length];
	exp[length]='\0';
	int j=0;
	int i;
	char input;
	for(i=0;i<length;i++)
		prefix[i]=NULL;

	for(i=0;i<length;i++)
	{
		//printf("\nhii in for \n");
		input=exp[i];
		if(isdigit(input))
			prefix[j++]=input;
		else if(input=='(')
			push(input);
		else if(input=='+'||input=='-'||input=='*'||input=='/'||input=='^')
		{
			//printf("\nhii in symbol\n");
				if(getPriority(arr[top])<getPriority(input))
				{
						//printf("\npririty less in stack\n");
						push(input);
				}
				
				else{
					//printf("\npririty greater in prefix\n");
				
					while((getPriority(arr[top])>=getPriority(input))&&top>-1)
					{
							//printf("\narr[top]= %c\n",arr[top]);
						prefix[j++]=pop();
						//printf("prefix = %s",prefix);
					}
				
						push(input);	
				}
		
		}
		else if(input==')')
		{
			//printf("\nhii in )\n");
			while(arr[top]!='(')
				prefix[j++]=pop();
			pop();
		}
			//printf("prefix = %s",prefix);
	}
	while(top>-1)
		prefix[j++]=pop();
	//printf("\nhii outside for\n");
	prefix[j]='\0';
	//printf("prefix = %s",prefix);
	eval(prefix);
}

int main()
{
	char exp[N];
	int i=0;
	inittop();
	//gets(exp);
	char ch;
	

   
	while(ch=_getch()!="\n" && ch!='q')
	{
		puts(ch);
		printf("hii");
		exp[i++]=ch;
		length=strlen(exp);
		if(validat(exp)==0)
		{
			i--;
			printf("not valid");
		}
	}
	//length=strlen(exp);
	if(validat(exp)==1)
	{
		printf("\nvalid expression\n");
		prefix(exp);
	
	}
	else{
		printf("\ninvalid expression\n");
	}
	
	return 0;
}

