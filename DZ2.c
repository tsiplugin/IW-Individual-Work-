/*
Submit a solution for B- (Variant 6)
Задача B-6. Программа калькулятор для строк
Time limit:	14 s
Memory limit:	64 M
Разработайте программу-калькулятор, умеющую вычислять арифметические выражения над строками. 
На стандартный поток ввода программы подается входное выражение, а результат вычислений программа должна вывести на стандартный поток вывода.

Строка - это заключенный в двойные кавычки произвольный набор символов. 
Например,
"1", "123", "zz!@#111' ad x" - строки, 
'asd', "asddas - не строки. 
"" - пустая строка, допустимо. 


Поддерживаемые операции: '+' - конкатенация, '*' - умножение, '()' - задание приоритета вычислений.
Конкатенировать (складывать) можно только строки! Иначе необходимо вывести "[error]". 
Примеры: 
"123" + "456", ответ - "123456". 
"123" + a: ошибка, необходимо вывести "[error]". 

Умножать можно только строку на число! Иначе необходимо вывести "[error]". 
Примеры: 
"123" * 1, ответ - "123". 
"123" * 2, ответ - "123123". 
"123" * 3 ответ - "123123123" и т.д. 
"123" * a: ошибка, необходимо вывести "[error]". 

Между операциями и строками может быть произвольное количество пробелов - их необходимо пропускать. 
Например,
"11"     * 2 +     ( "22" + "33" ) - валидное выражение, результат тут будет "11112233". 
При вычислениях должны учитываться приоритеты операций (в том числе, заданные вручную при помощи круглых скобочек). 

В случае, если введенное выражение содержит ошибку (невалидное выражение), необходимо вывести в поток стандартного вывода сообщение "[error]" и завершить выполнение программы. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *packer(char *buffer, int size, int new_size)
{
	char *new_buffer;
	if((new_buffer=(char *)malloc(new_size*sizeof(char)))==NULL)
		return NULL;
	int i=0;
	for(i=0; i<size; i++)
		new_buffer[i]=buffer[i];
	return new_buffer;
}

int input(char **string)
{
	int size=4;
	char *oldbuffer=NULL;
	char *buffer=NULL;
	if((buffer=(char*)malloc(size*sizeof(char)))==NULL)
	{
		return 0;
	}
	int symbol=0;
	int count=0;
	//flag[0] - скобки
	//flag[1] - ввод строки
	//flag[2] - умножение
	//flag[3] -  ввод числа
	int flag[6]={0, 0, 0, 0};
	while((symbol=getchar())!='\n'&&symbol!=EOF)
	{
		if((symbol==' '||symbol=='\t')&&flag[1]==0)
		{
		}
		else if(flag[1]==0&&flag[2]==0&&flag[3]==0&&isdigit(symbol))
		{
			flag[4]=1;
			buffer[count++]=symbol;
		}
		else if(flag[4]==1&&(!isdigit(symbol)&&symbol!='*'))
		{
			size=0;
			break;
		}
		else if(flag[4]&&symbol=='*')
		{
			flag[4]=0;
			buffer[count++]=symbol;
		}
		else if((flag[2]==1&&flag[3]==0)&&((!isdigit(symbol))&&symbol!=' '&&symbol!='\t'))
		{
			count=0;
			break;
		}
		else if((flag[2]==1&&flag[3]==1)&&!isdigit(symbol))
		{
			flag[2]=0;
			flag[3]=0;
			buffer[count++]=symbol;
		}
		else if(symbol=='('&&flag[1]!=1)
		{
			buffer[count++]=symbol;
			flag[0]++;
		}
		else if(symbol==')'&&flag[0]>0&&flag[1]!=1)
		{
			buffer[count++]=symbol;
			flag[0]--;
		}
		else if(symbol==')'&&flag[0]==0&&flag[1]!=1)
		{
			count=0;
			break;
		}
		else if(symbol=='"'&&flag[1]==0)
		{
			buffer[count++]=symbol;
			flag[1]=1;
		}
		else if(symbol=='"'&&flag[1]==1)
		{
			buffer[count++]=symbol;
			flag[1]=0;
		}
		else if((symbol==' '||symbol=='\t')&&flag[1]==0)
		{
		}
		else if(flag[1]==1)
		{
			buffer[count++]=symbol;
		}
		else if(symbol=='+')
		{
			buffer[count++]=symbol;
		}
		else if(symbol=='*'&&flag[3]==0)
		{
			buffer[count++]=symbol;
			flag[2]=1;
		}
		else if(isdigit(symbol)&&flag[2]==1)
		{
			buffer[count++]=symbol;
			flag[3]=1;
		}
		else
		{
			count=0;
			break;
		}
		
		if(count==size)
		{
			size*=2;
			oldbuffer=buffer;
			if((buffer=packer(buffer, size/2, size))==NULL)
			{
				count=0;
				break;
			}
			free(oldbuffer);	
		}
	}
	buffer[count]='\0';
	(*string)=buffer;
	if(flag[0]!=0||flag[1]!=0||(flag[2]==1&&flag[3]==0))
	{
		return 0;
	}
	else
	{
		return count;
	}
}

char *plus(char *str1, char *str2)
{
	if(str1==NULL)
	{
		return NULL;
	}
	if(str2==NULL)
	{
		return NULL;
	}
	char *string=NULL;
	if(str1[0]=='\0')
	{
		char *string;
		if((string=(char*)malloc((strlen(str2)+1)*sizeof(char)))==NULL)
		{	
			return NULL;
		}
		strcpy(string, str2);
		return string;
	}
	if(str2[0]=='\0')
	{
		if((string=(char*)malloc((strlen(str1)+1)*sizeof(char)))==NULL)
		{	
			return NULL;
		}
		strcpy(string, str1);
		return string;
	}
	int size1=strlen(str1);
	int size2=strlen(str2);
	if((string=(char*)malloc((size1+size2+1)*sizeof(char)))==NULL)
	{
		return NULL;
	}
	
	int i=0;
	for(i=0; i<size1; i++)
		string[i]=str1[i];
	for(i=0; i<size2; i++)
		string[size1+i]=str2[i];
	string[size1+size2]='\0';
	return string;	
}

char *power(char *str, int number)
{
	if(str==NULL)
	{
		return NULL;
	}
	char *string=NULL;
	int size=strlen(str);
	if((string=(char*)malloc((size*number+1)*sizeof(char)))==NULL)
		return NULL;
	int i=0;
	for(i=0; i<number; i++)
		strcpy(string+size*i, str);
	string[size*number]='\0';
	return string;	
}


char *parse(char* string)
{
	if(string==NULL)
	{
		return NULL;
	}
	int i=0;
	char* oldstring=NULL;
	int size=strlen(string);
	//flag[0] - ввод строки
	//flag[1] - скобки
	int flag[2]={0,0};
	//Ситуация, когда ввод начинается с числа
	if(isdigit(string[0]))
	{
		int j=0;
		int number=0;
		while(isdigit(string[j]))
		{
			number*=10;
			number+=string[j]-'0';
			j++;
		}
		j++;
		for(i=j; i<size; i++)
		{
			if(string[i]=='"'&&flag[0]==0)
			{
					flag[0]=1;
			}
			else if(string[i]=='"'&&flag[0]==1&&flag[1]!=0)
			{
				flag[0]=0;
			}
			else if(string[i]=='"'&&flag[0]==1&&flag[1]==0)
			{
				if(string[i+1]=='+')
				{
					char *str1=NULL;
					char *str2=NULL;
					if((str1=(char*)malloc((i-j+2)*sizeof(char)))==NULL)
					{
						return NULL;
					}
					if((str2=(char*)malloc((size-i-1)*sizeof(char)))==NULL)
					{
						free(str1);
						return NULL;
					}
					int k=j;
					for(k=j; k<i+1; k++)
					{
						str1[k-j]=string[k];
					}
					str1[i-j+1]='\0';
					for(k=i+2; k<size; k++)
					{
						str2[k-i-2]=string[k];
					}
					str2[size-i-2]='\0';
					str1=parse(str1);
					char *str3=power(str1, number);
					free(str1);
					str2=parse(str2);
					oldstring=string;
					string=plus(str3, str2);
					free(str2);
					free(str3);
					free(oldstring);
					return string;
				}
				else if(string[i+1]=='\0')
				{
					char *str=NULL;
					if((str=(char*)malloc((size-j-1)*sizeof(char)))==NULL)
					{
						return NULL;
					}
					int k=j;
					for (k=j; k<size; k++)
					{
						str[k-j]=string[k];
					}
					str[size-j]='\0';
					str=parse(str);
					oldstring=string;
					string=power(str, number);
					free(str);
					free(oldstring);
					return string;
				}	
				else
				{
					return NULL;
				}
			}	
			else if(string[i]==')'&&flag[0]==0&&flag[1]!=1)
			{
				flag[1]--;
			}
			else if(string[i]=='('&&flag[0]==0)
			{
				flag[1]++;
			}
			else if(string[i]==')'&&flag[0]==0&&flag[1]==1)
			{
				if(string[i+1]=='+')
				{
					char *str1=(char*)malloc(i-j+2);
					char *str2=(char*)malloc(size-i-1);
					int k=j;
					for(k=j; k<i+1; k++)
					{
						str1[k-j]=string[k];
					}
					str1[i-j+1]='\0';
					for(k=i+2; k<size; k++)
					{
						str2[k-i-2]=string[k];
					}
					str2[size-i-2]='\0';
					str1=parse(str1);
					char *str3=power(str1, number);
					free(str1);
					str2=parse(str2);
					oldstring=string;
					string=plus(str3, str2);
					free(str2);
					free(str3);
					free(oldstring);
					return string;
				}
				else 
				{
					char *str=(char*)malloc(size-j+1);
					int k=j;
					for (k=j; k<size; k++)
					{
						str[k-j]=string[k];
					}
					str[size-j]='\0';
					str=parse(str);
					oldstring=string;
					string=power(str, number);
					free(str);
					free(oldstring);
					return string;
				}
			}
		}
	}
	
	
	
	for(i=0; i<size; i++)
	{
		if(string[i]=='"'&&flag[0]==0)
		{
			flag[0]=1;
		}
		else if(string[i]=='"'&&flag[0]==1&&flag[1]!=0)
		{
			flag[0]=0;
		}
		else if(string[i]=='"'&&flag[0]==1&&flag[1]==0)
		{
			if(string[i+1]=='\0')
			{
				oldstring=string;
				if((string=(char*)malloc((size-1)*sizeof(char)))==NULL)
				{
					return NULL;
				}
				int j=1;
				for(j=1; j<size-1; j++)
					string[j-1]=oldstring[j];
				string[j-1]='\0';
				free(oldstring);
				break;
			}
			else if(string[i+1]=='+')
			{
				char *str1;
				char *str2;
				if((str1=(char*)malloc((i+2)*sizeof(char)))==NULL)
				{
					return NULL;
				}
				if((str2=(char*)malloc((size-i+1)*sizeof(char)))==NULL)
				{
					return NULL;
				}
				int k=0;
				for(k=0; k<=i; k++)
					str1[k]=string[k];
				str1[i+1]='\0';
				for(k=i+2; k<=size; k++)
					str2[k-i-2]=string[k];
				oldstring=string;
				free(oldstring);
				str1=parse(str1);
				str2=parse(str2);
				string=plus(str1, str2);
				free(str1);
				free(str2);
				break;
			}
			else if(string[i+1]=='*')
			{	
				int j=2;
				int number=0;
				char *str1;
				char *str2;
				while(isdigit(string[i+j]))
				{
					number*=10;
					number+=string[i+j]-'0';
					j++;
				}
				if((str1=(char*)malloc((i+2)*sizeof(char)))==NULL)
				{	
					return NULL;
				}
				int k=0;
				for(k=0; k<=i; k++)
					str1[k]=string[k];
				str1[i+1]='\0';
				oldstring=string;
				if(string[i+j]=='+')
				{
					if((str2=(char*)malloc((size-i-j)*sizeof(char)))==NULL)
					{	
						return NULL;
					}		
					for(k=i+j+1; k<=size; k++)
						str2[k-i-j-1]=string[k];
					str1=parse(str1);
					str2=parse(str2);
					char *str3=power(str1, number);
					free(str1);
					string=plus(str3, str2);
					free(str3);
					free(str2);
				}
				else
				{
					str1=parse(str1);
					string=power(str1, number);
					free(str1);
				}
				free(oldstring);
				break;
			}
		}
		else if(string[i]=='('&&flag[0]==0)
		{
			flag[1]++;
		}
		else if(string[i]==')'&&flag[0]==0&&flag[1]==1)
		{
			if(string[i+1]=='\0')
			{
				oldstring=string;
				if((string=(char*)malloc((size-1)*sizeof(char)))==NULL)
				{
					return NULL;
				}
				int j=0;
				for(j=1; j<size-1; j++)
					string[j-1]=oldstring[j];
				string[j-1]='\0';
				free(oldstring);
				string=parse(string);
				break;
			}
			else if(string[i+1]=='+')
			{
				char *str1;
				char *str2;
				if((str1=(char*)malloc((i+2)*sizeof(char)))==NULL)
				{
					return NULL;
				}
				if((str2=(char*)malloc((size-i+1)*sizeof(char)))==NULL)
				{
					return NULL;
				}
				int k=0;
				for(k=0; k<=i; k++)
					str1[k]=string[k];
				str1[i+1]='\0';
				for(k=i+2; k<=size; k++)
					str2[k-i-2]=string[k];
				oldstring=string;
				free(oldstring);
				str1=parse(str1);
				str2=parse(str2);
				string=plus(str1, str2);
				free(str1);
				free(str2);
				break;
			}			else if(string[i+1]=='*')
			{	
				int j=2;
				int number=0;
				char *str1;
				char *str2;
				while(isdigit(string[i+j]))
				{
					number*=10;
					number+=string[i+j]-'0';
					j++;
				}
				if((str1=(char*)malloc((i+2)*sizeof(char)))==NULL)
				{	
					return NULL;
				}
				int k=0;
				for(k=0; k<=i; k++)
					str1[k]=string[k];
				str1[i+1]='\0';
				oldstring=string;
				if(string[i+j]=='+')
				{
					if((str2=(char*)malloc((size-i-j)*sizeof(char)))==NULL)
					{	
						return NULL;
					}		
					for(k=i+j+1; k<=size; k++)
						str2[k-i-j-1]=string[k];
					str1=parse(str1);
					str2=parse(str2);
					char *str3=power(str1, number);
					free(str1);
					string=plus(str3, str2);
					free(str3);
					free(str2);
				}
				else
				{
					str1=parse(str1);
					string=power(str1, number);
					free(str1);
				}
				free(oldstring);
				break;
			}
		}
		else if(string[i]==')'&&flag[0]==0&&flag[1]!=1)
		{
			flag[1]--;
		}
	}
	return string;
}


int main(void)
{
	char* buffer=NULL;

	if(input(&buffer)==0)
	{
		printf("[error]");
		free(buffer);
		return 0;
	}
	if((buffer=parse(buffer))==NULL)
	{
		printf("[error]");
		free(buffer);
		return 0;
	}
	char *result=NULL;
	if((result=(char*)malloc(strlen(buffer)+3))==NULL);
	int i=0;
	result[i]='"';
	for(i=0;i<strlen(buffer)+1; i++)
	{
		result[i+1]=buffer[i];
	}
	result[i++]='"';
	result[i]='\0';
	printf("%s", result);
	free(result);
	free(buffer);
	return 0;
}
