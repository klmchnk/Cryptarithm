#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 100
#define MAX_LETTERS 10
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
} Letters[MAX_LETTERS];

int numberOfLetters = 0;
long int variants = 0;

int find_symbol(char s)
{
	for (int i = 0; i < MAX_LETTERS; i++)
		if (Letters[i].symbol == s)
			return i;
	return -1;
}

void swap(int i, int j)
{
	int tmp = Letters[i].digit;
	Letters[i].digit = Letters[j].digit;
	Letters[j].digit = tmp;
}

void get_array_of_letters(char* str)
{
	int i, idx;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] > 64 && str[i] < 91)
		{
			idx = find_symbol(str[i]);

			if (idx == -1)
			{
				if (i == 0 || str[i - 1] == ' ')
					Letters[numberOfLetters].isFirst = true;
				Letters[numberOfLetters].symbol = str[i];
				Letters[numberOfLetters].digit = numberOfLetters;
				numberOfLetters++;
			}
			else
			{
				if (i == 0 || str[i - 1] == ' ')
					Letters[idx].isFirst = true;
			}
		}
	}

	for (i = 9; i > numberOfLetters - 1; i--)
		Letters[i].digit = i;

	swap(0, 1);
}

int check_sum(char* str)
{
	int i = 0 , sum = 0, tmp = 0, answer = 0, idx = 0;
	
	for (i = strlen(str) - 1; str[i] != ' '; i--)
	{
		idx = find_symbol(str[i]);

		if (Letters[idx].digit == 0)
			if (Letters[idx].isFirst)
			{
				swap(idx, idx + 1);
				return 0;
			}

		answer += Letters[idx].digit * pow(10, strlen(str) - 1 - i);
	}

	for (i = 0; str[i] != '='; i++)
	{
		if (str[i] > 64 && str[i] < 91)
		{
			idx = find_symbol(str[i]);

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

void solution(char* str)
{
	int lastLetterValue = 0;

	while (1)
	{
		if(lastLetterValue != Letters[numberOfLetters - 1].digit)
			if (check_sum(str))
				return;

		lastLetterValue = Letters[numberOfLetters - 1].digit;

		int j = MAX_LETTERS - 2;
		int k = MAX_LETTERS - 1;

		while (j != -1 && Letters[j].digit >= Letters[j + 1].digit)
			j--;

		while (Letters[j].digit >= Letters[k].digit)
			k--;

		swap(j, k);

		int l = j + 1;
		int r = MAX_LETTERS - 1;

		while (l < r)
			swap(l++, r--);
	}
}

void print_answer(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] > 64 && str[i] < 91)
			printf("%d", Letters[find_symbol(str[i])].digit);
		else
			printf("%c", str[i]);
	}
}

int main()
{
	char string[MAX_LENGTH];
	gets(string);

	LARGE_INTEGER freq, t1, t2;
	double el_t;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&t1);

	get_array_of_letters(string);
	solution(string);

	QueryPerformanceCounter(&t2);
	el_t = t2.QuadPart - t1.QuadPart;
	el_t = el_t / freq.QuadPart;

	print_answer(string);

	printf("\n\nThe time to solve the rebus: %f seconds \n", el_t);
	printf("\nThe solution variant number: %ld", variants);

	return 0;
}