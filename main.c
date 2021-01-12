#define _CRT_SECURE_NO_WARNINGS 
#define MAX_LENGTH 100
#define MAX_LETTERS 10
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>

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
			return Letters[i].digit;
	return -1;
}

bool first_symbol(char s)
{
	for (int i = 0; i < MAX_LETTERS; i++)
		if (Letters[i].symbol == s)
			return Letters[i].isFirst;
	return false;
}

void get_array_of_letters(char* str)
{
	int i;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] > 64 && str[i] < 91)
		{
			if (find_symbol(str[i]) == -1)
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
					Letters[find_symbol(str[i])].isFirst = true;
			}
		}
	}

	for (i = 9; i > numberOfLetters - 1; i--)
		Letters[i].digit = i;
}

int check_sum(char* str)
{
	int sum = 0, tmp = 0, answer = 0, digit = 0, i = 0;

	for (i; str[i] != '='; i++)
	{
		if (str[i] > 64 && str[i] < 91)
		{
			digit = find_symbol(str[i]);

			if (digit == 0)
				if (first_symbol(str[i]))
					return 0;

			tmp = tmp * 10 + digit;
		}
		else
		{
			sum += tmp;
			tmp = 0;
		}
	}

	for (i; i < strlen(str); i++)
	{
		if (str[i] > 64 && str[i] < 91)
		{
			digit = find_symbol(str[i]);

			if (digit == 0)
				if (first_symbol(str[i]))
					return 0;
			answer = answer * 10 + find_symbol(str[i]);
		}
	}

	if (answer == sum)
		return 1;

	variants++;
	return 0;
}

void swap(int i, int j)
{
	int tmp = Letters[i].digit;
	Letters[i].digit = Letters[j].digit;
	Letters[j].digit = tmp;
}

void solution(char* str)
{
	while (1)
	{
		if (check_sum(str))
			return;

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
			printf("%d", find_symbol(str[i]));
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