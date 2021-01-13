#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 100
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <math.h>

struct Letter
{
	char symbol;
	int digit;
	bool isFirst;
} Letters[10];

int numberOfLetters = -1;
long int variants = 0;

int find_symbol(char s)
{
	for (int i = 0; i < 10; i += 2)
	{
		if (Letters[i].symbol == s)
			return i;
		if (Letters[i + 1].symbol == s)
			return i + 1;
	}
	return -1;
}

void swap(int i, int j)
{
	int tmp = Letters[i].digit;
	Letters[i].digit = Letters[j].digit;
	Letters[j].digit = tmp;
}

void get_array_of_letters(char* str, int length)
{
	int i, idx;
	char c;

	for (i = 0; i < length; i++)
	{
		c = str[i];
		if (c > 64 && c < 91)
		{
			idx = find_symbol(c);

			if (idx == -1)
			{
				numberOfLetters++;
				if (i == 0 || str[i - 1] == ' ')
					Letters[numberOfLetters].isFirst = true;
				Letters[numberOfLetters].symbol = c;
				Letters[numberOfLetters].digit = numberOfLetters;
			}
			else
			{
				if (i == 0 || str[i - 1] == ' ')
					Letters[idx].isFirst = true;
			}
		}
	}

	for (i = 9; i > numberOfLetters; i--)
		Letters[i].digit = i;

	swap(0, 1);
}

int check_sum(char* str, int length)
{
	int i = 0 , sum = 0, tmp = 0, answer = 0, idx = 0;
	int pow = 1;
	char c;

	for (i = length - 1; (c = str[i]) != ' '; i--)
	{
		idx = find_symbol(c);

		if (Letters[idx].digit == 0)
			if (Letters[idx].isFirst)
			{
				swap(idx, idx + 1);
				return 0;
			}

		answer += Letters[idx].digit * pow;
		pow *= 10;
	}

	for (i = 0; (c = str[i]) != '='; i++)
	{
		if (c > 64 && c < 91)
		{
			idx = find_symbol(c);

			if (Letters[idx].digit == 0)
				if (Letters[idx].isFirst)
				{
					swap(idx, idx + 1);
					return 0;
				}

			tmp = tmp * 10 + Letters[idx].digit;
		}
		else
		{
			sum += tmp;
			if (sum > answer)
				return 0;
			tmp = 0;
		}
	}

	if (answer == sum)
		return 1;

	variants++;
	return 0;
}

void solution(char* str, int length)
{
	int lastLetterValue = 0;

	while (1)
	{
		if(lastLetterValue != Letters[numberOfLetters].digit)
			if (check_sum(str, length))
				return;

		lastLetterValue = Letters[numberOfLetters].digit;

		int j = 8;
		int k = 9;

		while (j != -1 && Letters[j].digit >= Letters[j + 1].digit)
			j--;

		while (Letters[j].digit >= Letters[k].digit)
			k--;

		swap(j, k);

		int l = j + 1;
		int r = 9;

		while (l < r)
			swap(l++, r--);
	}
}

void print_answer(char* str, int length)
{
	char c;

	for (int i = 0; i < length; i++)
	{
		c = str[i];
		if (c > 64 && c < 91)
			printf("%d", Letters[find_symbol(c)].digit);
		else
			printf("%c", c);
	}
}

int main()
{
	char string[MAX_LENGTH];
	gets(string);
	
	int length = strlen(string);

	LARGE_INTEGER freq, t1, t2;
	double el_t;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&t1);

	get_array_of_letters(string, length);
	solution(string, length);

	QueryPerformanceCounter(&t2);
	el_t = t2.QuadPart - t1.QuadPart;
	el_t = el_t / freq.QuadPart;

	print_answer(string, length);

	printf("\n\nThe time to solve the rebus: %f seconds \n", el_t);
	printf("\nThe solution variant number: %ld", variants);

	return 0;
}