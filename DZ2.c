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
#define QUOTES '"'
#define L_BRACKET '('
#define R_BRACKET ')'
#define EXPR '*'
#define ADDER '+'
#define BEG_SIZE 4

char *input()
{
	int size=BEG_SIZE;
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
	//flag[3] -  ввод числа после *
	//flag[4] - ввод числа перед *
	int flag[5]={0, 0, 0, 0, 0};
	while((symbol=getchar())!='\n'&&symbol!=EOF)
	{
		if(isspace(symbol) && flag[1]==0)
		{
		}
		else if(flag[1]==0 && flag[2]==0 && flag[3]==0 && isdigit(symbol))
		{
			flag[4]=1;
			buffer[count++]=symbol;
		}
		else if(flag[4]==1 && (!isdigit(symbol) && symbol!=EXPR))
		{
			count=0;
			break;
		}
		else if(flag[4]==1 && symbol==EXPR)
		{
			flag[4]=0;
			buffer[count++]=symbol;
		}
		else if((flag[2]==1 && flag[3]==0) && ((!isdigit(symbol)) && (!isspace(symbol))))
		{
			count=0;
			break;
		}
		else if((flag[2]==1 && flag[3]==1) && !isdigit(symbol))
		{
			flag[2]=0;
			flag[3]=0;
			buffer[count++]=symbol;
		}
		else if(symbol==L_BRACKET && flag[1]!=1)
		{
			buffer[count++]=symbol;
			flag[0]++;
		}
		else if(symbol==R_BRACKET && flag[0]>0 && flag[1]!=1)
		{
			buffer[count++]=symbol;
			flag[0]--;
		}
		else if(symbol==R_BRACKET && flag[0]==0 && flag[1]!=1)
		{
			count=0;
			break;
		}
		else if(symbol==QUOTES && flag[1]==0)
		{
			buffer[count++]=symbol;
			flag[1]=1;
		}
		else if(symbol==QUOTES && flag[1]==1)
		{
			buffer[count++]=symbol;
			flag[1]=0;
		}
		else if(isspace(symbol) && flag[1]==0)
		{
		}
		else if(flag[1]==1)
		{
			buffer[count++]=symbol;
		}
		else if(symbol==ADDER)
		{
			buffer[count++]=symbol;
		}
		else if(symbol==EXPR && flag[3]==0)
		{
			buffer[count++]=symbol;
			flag[2]=1;
		}
		else if(isdigit(symbol) && flag[2]==1)
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
			char *newbuffer=buffer;
			if((newbuffer=realloc(buffer, size))==NULL)
			{
				count=0;
				break;
			}
			buffer=newbuffer;	
		}
	}
	buffer[count]='\0';
	if((flag[0]!=0||flag[1]!=0||(flag[2]==1&&flag[3]==0))||count==0)
	{
		free(buffer);
		return NULL;
	}
	else
	{
		return buffer;
	}
}

char *plus(char *str1, char *str2)
{
	if(!str1)
	{
		return NULL;
	}
	if(!str2)
	{
		return NULL;
	}
	
	char *result=NULL;
	int size1=strlen(str1);
	int size2=strlen(str2);
	if((result=(char*)malloc((size1+size2+1)*sizeof(char)))==NULL)
	{
		return NULL;
	}
	
	strcpy(result, str1);
	strcpy(result+size1, str2);
	result[size1+size2]='\0';
	return result;	
}

char *power(char *string_to_power, int number)
{
	if(string_to_power==NULL)
	{
		return NULL;
	}
	char *result=NULL;
	int size=strlen(string_to_power);
	if((result=(char*)malloc((size*number+1)*sizeof(char)))==NULL)
		return NULL;
	int i=0;
	for(i=0; i<number; i++)
		strcpy(result+size*i, string_to_power);
	result[size*number]='\0';
	return result;	
}


char *parse(char* string)
{
	if(string==NULL)
	{
		return NULL;
	}
	int i=0;
	int iserror=0;
	int size=strlen(string);
	//flag[0] - ââîä ñòðîêè
	//flag[1] - ñêîáêè
	int flag[2]={0,0};
	if(isdigit(string[0]))
	{
		int j=0;
		int number=0;
		while(isdigit(string[j])&&j<size)
		{
			number*=10;
			number+=string[j]-'0';
			j++;
		}
		j++;
		for(i=j; i<size; i++)
		{
			if(string[i]==QUOTES && flag[0]==0)
			{
					flag[0]=1;
			}
			else if(string[i]==QUOTES && flag[0]==1 && flag[1]!=0)
			{
				flag[0]=0;
			}
			else if(string[i]==QUOTES && flag[0]==1 && flag[1]==0)
			{
				operation1:
				if(string[i+1]==ADDER)
				{
					char *factor=NULL;
					char *addend1=NULL;
					if((factor=(char*)malloc((i-j+2)*sizeof(char)))==NULL)
					{
						iserror=1;
						goto end;
					}
					if((addend1=(char*)malloc((size-i-1)*sizeof(char)))==NULL)
					{
						free(factor);
						iserror=1;
						goto end;
					}
					memcpy(factor, string+j, i+1-j);
					factor[i-j+1]='\0';
					memcpy(addend1, string+i+2, size-i-2);
					addend1[size-i-2]='\0';
					if((factor=parse(factor))==NULL)
					{
						free(addend1);
						iserror=1;
						goto end;
					}
					char *addend2=NULL;
					if((addend2=power(factor, number))==NULL)
					{
						free(addend1);
						free(factor);
						iserror=1;
						goto end;
					}
					free(factor);
					if((addend1=parse(addend1))==NULL)
					{
						free(addend2);
						iserror=1;
						goto end;
					}
					char *newstring=NULL;
					if((newstring=plus(addend2, addend1))==NULL)
					{
						free(addend1);
						free(addend2);
						iserror=1;
						goto end;
					}
					free(addend1);
					free(addend2);
					free(string);
					string=newstring;
					goto end;
				}
				else if(string[i+1]=='\0')
				{
					char *factor=NULL;
					if((factor=(char*)malloc((i-j+2)*sizeof(char)))==NULL)
					{
						iserror=1;
						goto end;
					}
					strcpy(factor, string+j);
					factor[size-j]='\0';
					if((factor=parse(factor))==NULL)
					{
						iserror=1;
						goto end;
					}
					char *newstring=string;
					if((newstring=power(factor, number))==NULL)
					{
						free(factor);
						iserror=1;
						goto end;
					}
					free(factor);
					free(string);
					string=newstring;
					goto end;
				}	
				else
				{
					iserror=1;
					goto end;
				}
			}	
			else if(string[i]==R_BRACKET && flag[0]==0 && flag[1]!=1)
			{
				flag[1]--;
			}
			else if(string[i]==L_BRACKET && flag[0]==0)
			{
				flag[1]++;
			}
			else if(string[i]==R_BRACKET && flag[0]==0 && flag[1]==1)
			{
				goto operation1;
			}
		}
	}
	else
	{
	for(i=0; i<size; i++)
	{
		if(string[i]==QUOTES && flag[0]==0)
		{
			flag[0]=1;
		}
		else if(string[i]==QUOTES && flag[0]==1&&flag[1]!=0)
		{
			flag[0]=0;
		}
		else if(string[i]==QUOTES && flag[0]==1&&flag[1]==0)
		{
			if(string[i+1]=='\0')
			{
				char *newstring=string;
				if((newstring=(char*)malloc((size-1)*sizeof(char)))==NULL)
				{
					iserror=1;
					break;
				}
				memcpy(newstring, string+1, size-2);
				newstring[size-2]='\0';
				free(string);
				string=newstring;
				break;
			}
			else if(string[i+1]==ADDER)
			{
				operation2:
				{
					char *addend1=NULL;
					char *addend2=NULL;
					if((addend1=(char*)malloc((i+2)*sizeof(char)))==NULL)
					{
						iserror=1;
							break;
					}
					if((addend2=(char*)malloc((size-i+1)*sizeof(char)))==NULL)
					{
						free(addend1);
						iserror=1;
						break;
					}
					memcpy(addend1, string, i+1);
					addend1[i+1]='\0';
					memcpy(addend2, string+i+2, size-i-1);
					addend2[size-i]='\0';
					if((addend1=parse(addend1))==NULL)
					{
						free(addend2);
						iserror=1;
						break;
					}
					if((addend2=parse(addend2))==NULL)
					{
						free(addend1);
						iserror=1;
						break;
					}
					char *newstring=NULL;
					if((newstring=plus(addend1, addend2))==NULL)
					{
						free(addend1);
						free(addend2);
						iserror=1;
						break;
					}
					free(addend1);
					free(addend2);
					free(string);
					string=newstring;
					break;
				}
			}
			else if(string[i+1]==EXPR)
			{	
				operation3:
				{	
					int j=2;
					int number=0;
					char *factor=NULL;
					while(isdigit(string[i+j])&&(i+j)<size)
					{
						number*=10;
						number+=string[i+j]-'0';
						j++;
					}
					if((factor=(char*)malloc((i+2)*sizeof(char)))==NULL)
					{
						iserror=1;
						break;
					}
					memcpy(factor, string, i+1);
					factor[i+1]='\0';
					char *newstring=NULL;
					if((factor=parse(factor))==NULL)
					{
						iserror=1;
						break;
					}
					if(string[i+j]==ADDER)
					{
						char *addend1=NULL;
						if((addend1=(char*)malloc((size-i-j)*sizeof(char)))==NULL)
						{
							free(factor);
							iserror=1;
							break;
						}	
						memcpy(addend1, string+i+j+1, size-i-j);
						if((addend1=parse(addend1))==NULL)
						{
							free(factor);
							iserror=1;
							break;
						}
						char *addend2;
						if((addend2=power(factor, number))==NULL)
						{
							free(factor);
							free(addend1);
							iserror=1;
							break;
						}
						free(factor);;
						if((newstring=plus(addend2, addend1))==NULL)
						{
							free(addend1);
							free(addend2);
							iserror=1;
							break;
						}
						free(addend1);
						free(addend2);
						free(string);
						string=newstring;
						break;
					}
					else
					{
						if((newstring=power(factor, number))==NULL)
						{
								free(factor);
							iserror=1;
							break;
						}
						free(factor);
						free(string);
						string=newstring;
						break;
					}
					break;
				}
			}
			else
			{
				iserror=1;
				break;
			}
		}
		else if(string[i]==L_BRACKET && flag[0]==0)
		{
			flag[1]++;
		}
		else if(string[i]==R_BRACKET && flag[0]==0 && flag[1]==1)
		{
			if(string[i+1]=='\0')
			{
				char *newstring=NULL;
				if((newstring=(char*)malloc((size-1)*sizeof(char)))==NULL)
				{
					iserror=1;
					break;
				}
				memcpy(newstring, string+1, size-2);
				newstring[size-2]='\0';
				if((newstring=parse(newstring))==NULL)
				{
					iserror=1;
					break;
				}
				free(string);
				string=newstring;
				break;
			}
			else if(string[i+1]==ADDER)
			{
				goto operation2;
			}
			else if(string[i+1]==EXPR)
			{
				goto operation3;
			}
			else
			{
				iserror=1;
				break;
			}
		}
		else if(string[i]==R_BRACKET && flag[0]==0 && flag[1]!=1)
		{
			flag[1]--;
		}
	}
	}
	end:
	if(iserror)
	{
		free(string);
		return NULL;
	}
	else
	{
		return string;
	}
}


int main(void)
{
	char* buffer=NULL;
	if((buffer=input())==NULL)
	{
		printf("[error]");
		return 0;
	}
	if((buffer=parse(buffer))==NULL)
	{
		printf("[error]");
		return 0;
	}
	char *result=NULL;
	int buf_size=strlen(buffer);
	//длина строки + 2 ковычки + '\0'
	if((result=(char*)malloc(buf_size+3))==NULL)
	{
		free(buffer);
		return 0;
	}

	result[0]='"';
	memcpy(result+1, buffer, buf_size);
	result[buf_size+1]='"';
	result[buf_size+2]='\0';
	printf("%s", result);
	free(result);
	free(buffer);
	return 0;
}
