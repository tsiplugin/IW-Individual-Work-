#include <stdio.h>
#define ALPHABET1 "0123456789abcdefghijklmnopqrstuvwxyz"
#define ALPHABET2 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

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

void work(int base, long long numint)
{
	int i=0;
	long long result[64];
	while(numint!=0)
	{
		result[i]=numint%base;
		numint=numint/base;
		i++;
	}
	while(i>=1)
			printf("%c", ALPHABET1[result[--i]]);
}

long long input(int *base2)
{
	int base1, i, help[126];
	for(i=0; i<126; i++)
		help[i]=-1;
	long long num=0;
	char string_num[64];
	if(scanf("%d %d ", &base1, base2)<2)
		return(-1);
	if((base1<=(*base2))||(base1>36)||(base1<3)||((*base2)<2)||((*base2)>35))
		return(-1);
	scanf("%s", string_num);
	for(i=0; i<base1; i++)
		help[(int)(ALPHABET1[i])]=i, help[(int)(ALPHABET2[i])]=i;
	for(i=0; string_num[i]; i++)
	{
		if((help[(int)(string_num[i])])!=-1)
			num*=base1, num+=help[(int)(string_num[i])];
		else
			return -1;
	}
	return num;
}

int main(void)
{
	int base;
	long long num;
	num=input(&base);
	if(num==-1)
		printf("[error]");
	else
		work(base, num);
	return 0;
}
