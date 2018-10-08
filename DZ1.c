/*
Задача A-2. Задача о системах счисления
Time limit:	14 s
Memory limit:	64 M
Составить программу для перевода чисел из системы счисления по основанию P в систему счисления по основанию Q, где 2 меньше или равно Q меньше P меньше или равно 36. 
Значения P, Q и строковое представление S числа в исходной системе счисления вводятся с клавиатуры в следующем порядке: 
P Q S 

S не выходит за границы size_t. 

Процедура перевода не может использовать соответствующей функции системной библиотеки и должна быть оформлена в виде отдельной функции, на вход которой подаются значения P, Q и S, размещенные в динамической памяти. 
На выход функция должна возвращать строковое представление S1 числа в целевой системе счисления. 

Программа должна уметь обрабатывать ошибки во входных данных. 
В случае возникновения ошибки нужно вывести в поток стандартного вывода сообщение "[error]" (без кавычек) и завершить выполнение программы. 
*/

#include <stdio.h>
//Множество всех возможных символов в системе с основанием меньше или равным 36
#define ALPHABET1 "0123456789abcdefghijklmnopqrstuvwxyz"
#define ALPHABET2 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//Максимальное основание системы счисления
#define MAX 36
//Минимальное основание системы счисления
#define MIN 2

void work(int base_output, size_t number)
{
	if(base_output<2)
	{
		printf("[error]");
		return;
	}
	int i=0;
	int result[8*sizeof(size_t)];
	while(number!=0)
	{
		result[i]=number%base_output;
		number=number/base_output;
		i++;
	}
	while(i>0)
			printf("%c", ALPHABET1[result[--i]]);
}

int input_natural_in_interval(int *input, int min, int max)
{
	if(!scanf("%d", input))
		return 0;
	if(((*input)<min)||((*input)>max))
		return 0;
	return 1;
}

int input_number_in_system(int base_input, size_t *number)
{
	int i;
	char string_number[8*sizeof(size_t)+1];
	
	if(scanf("%s", string_number)==0)
		return 0;
	
	int meaning_of_symbols[128];
	for(i=0; i<128; i++)
		meaning_of_symbols[i]=-1;
	for(i=0; i<base_input; i++)
	{
		meaning_of_symbols[(int)(ALPHABET1[i])]=i;
		meaning_of_symbols[(int)(ALPHABET2[i])]=i;
	}

	for(i=0; string_number[i]; i++)
	{
		if((meaning_of_symbols[(int)(string_number[i])])!=-1)
		{
			(*number)*=base_input;
			(*number)+=meaning_of_symbols[(int)(string_number[i])];
		}
		else
		{
			i=0;
			break;
		}
	}
	if(i==0)
		return 0;
	return 1;
}

int main(void)
{
	int base_input=0, base_output=0;
	size_t number=0;

	if(!input_natural_in_interval(&base_input, MIN+1, MAX))
	{
		printf("[error]");
		return 0;
	}
	
	if(!input_natural_in_interval(&base_output, MIN, MAX-1))
	{
		printf("[error]");
		return 0;
	}
	
	if(base_output>=base_input)
	{
		printf("[error]");
		return 0;
	}
	
		
	if(input_number_in_system(base_input, &number))
		work(base_output, number);
	else 
			printf("[error]");

	return(0);
}
