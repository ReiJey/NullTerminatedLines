#include<iostream>
#include<Windows.h>
using namespace std;

//#define CASE_FUNCTIONS

void InputLine(char szStr[], const int n);
int  StrLen(char szStr[]);
void UpperCase(char szStr[]);	//Переводит строку в верхний регистр.
void LowerCase(char szStr[]);	//Переводит строку в нижний  регистр.
void Capitalize(char szStr[]);	//Первую букву каждого слова в предложении делает заглавной.
bool isLowLetter(char symbol);
bool isLowRusLetter(char symbol);

void Shrink(char szStr[]);		//Удаляет лишние пробелы между словами в предложении.
void RemoveSpaces(char szStr[]);
bool isPalindrome(char szStr[]);	//Проверяет, является ли данная строка палиндромом.
bool isNumber(char szStr[]);	//Проверяет, является строка числом. Строка является числом, если содержит только цифры.
bool isHexNumber(char szStr[]);	//Проверяет, является строка шестнадцатеричным числом. Строка является Hex-числом, если содержит только цифры и буквы ABCDEF либо abcdef.


void main()
{
	setlocale(LC_ALL, "");
	system("CHCP 1251");
	system("CLS");
	cout << (int)'A' << "\t" << (int)'a' << endl;
	cout << 'A' - 'a' << endl;
	/*char szStr[] = {'H', 'e', 'l', 'l', 0};
	cout << szStr << endl;
	char szStr1[] = "Hell";
	cout << szStr1 << endl;*/
	const int n = 256;	//Размер строки
	char szStr[n] = {};
	cout << "Введите строку: ";
	//InputLine(szStr, n);
	//cin >> szStr;
	cin.getline(szStr, n);
#if def CASE_FUNCTIONS
	cout << szStr << endl;
	cout << sizeof(szStr) << endl;
	UpperCase(szStr);
	cout << szStr << endl;
	Capitalize(szStr);
	cout << szStr << endl;
#endif // CAS

	cout << szStr << endl;
	Shrink(szStr);
	cout << szStr << endl;

	cout << isPalindrome(szStr) << endl;

}

void InputLine(char szStr[], const int n)
{
	//cout << typeid(szStr).name() << endl;
	SetConsoleCP(1251);
	cin.getline(szStr, n);
	SetConsoleCP(867);
}

int  StrLen(char szStr[])
{
	int i = 0;
	for (; szStr[i]; i++);
	return i;
}

void UpperCase(char szStr[])
{
	for (int i = 0; szStr[i]; i++)
		/*if
		(
		szStr[i] >= 'a' && szStr[i] <= 'z' ||
		szStr[i] >= 'а' && szStr[i] <= 'я'
		)
		szStr[i] -= 32;*/
		if (isLowLetter(szStr[i]) || isLowRusLetter(szStr[i]))szStr[i] -= 32;
}

void LowerCase(char szStr[])
{
	for (int i = 0; szStr[i]; i++)
	{
		if (szStr[i] >= 'A' && szStr[i] <= 'Z' ||
			szStr[i] >= 'А' && szStr[i] <= 'Я')
			szStr[i] += ' ';
	}
}

void Capitalize(char szStr[])
{
	LowerCase(szStr);
	if (isLowLetter(szStr[0]) || isLowRusLetter(szStr[0]))szStr[0] -= 32;
	for (int i = 0; szStr[i]; i++)
	{
		if (szStr[i - 1] == ' ' && (isLowLetter(szStr[i]) || isLowRusLetter(szStr[i])))
			szStr[i] -= 32;
	}
}

bool isLowLetter(char symbol)
{
	if (symbol >= 'a' && symbol <= 'z')return true;
	else return false;
}

bool isLowRusLetter(char symbol)
{
	if (symbol >= 'а' && symbol <= 'я')return true;
	else return false;
}

void Shrink(char szStr[])
{
	for (int i = 0; szStr[i]; i++)
	{
		while (szStr[i] == ' ' && szStr[i + 1] == ' ')
		{
			for (int j = i + 1; szStr[j]; j++)
			{
				szStr[j] = szStr[j + 1];
			}
		}
	}
}

void RemoveSpaces(char szStr[])
{
	for (int i = 0; szStr[i]; i++)
	{
		while (szStr[i] == ' ')

			for (int j = i; szStr[j]; j++)
			{
				szStr[j] = szStr[j + 1];
			}

	}
}

bool isPalindrome(char szStr[])
{
	int size = StrLen(szStr);
	char* buffer = new char[size + 1]{};
	for (int i = 0; i < size; i++)buffer[i] = szStr[i];
	LowerCase(buffer);
	RemoveSpaces(buffer);
	size = StrLen(buffer);
	for (int i = 0; i < size / 2; i++)
	{
		if (buffer[i] != buffer[size - 1 - i])
		{
			delete[] buffer;
			return false;
		}
	}
	delete[] buffer;
	return true;
}
