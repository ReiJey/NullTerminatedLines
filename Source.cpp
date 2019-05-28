#include<iostream>
#include<Windows.h>
using namespace std;

//#define CASE_FUNCTIONS
//#define Palindrom_Check

void InputLine(char szStr[], const int n);
int  StrLen(char szStr[]);      //Определить количество символов в строке.
void UpperCase(char szStr[]);	//Переводит строку в верхний регистр.
void LowerCase(char szStr[]);	//Переводит строку в нижний  регистр.
void Capitalize(char szStr[]);	//Первую букву каждого слова в предложении делает заглавной.
bool isLowLetter(char symbol);
bool isLowRusLetter(char symbol);

void Shrink(char szStr[]);		    //Удаляет лишние пробелы между словами в предложении.
void RemoveSpaces(char szStr[]);    //Удаляет все пробелы между словами.
bool isPalindrome(char szStr[]);	//Проверяет, является ли данная строка палиндромом.
bool isNumber(char szStr[]);	    //Проверяет, является строка числом. Строка является числом, если содержит только цифры.
int  StringToInt(char szStr[]);
bool isBinNumber(char szStr[]);
bool isHexNumber(char szStr[]);  	//Проверяет, является строка шестнадцатеричным числом. Строка является Hex-числом, если содержит только цифры и буквы ABCDEF либо abcdef.
int Bin2Dec(char szStr[]);
int Hex2Dec(char szStr[]);

void main()
{
	setlocale(LC_ALL, "");
	system("CHCP 1251");
	system("CLS");
	/*cout << (int)'A' << "\t" << (int)'a' << endl;
	cout << 'A' - 'a' << endl;*/
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

#if def Palindrom_Check
	Shrink(szStr);
	cout << szStr << endl;
	cout << isPalindrome(szStr) << endl;
	cout << szStr << endl;
#endif

	/*cout << isNumber(szStr) << endl;
	cout << StringToInt(szStr) << endl;*/

	cout << "Bin check: ";
	cout << isBinNumber(szStr) << endl;
	cout << "Hex check: ";
	cout << isHexNumber(szStr) << endl;
	cout << "Bin2Dec: ";
	cout << Bin2Dec(szStr) << endl;
	cout << "Hex2Dec: ";
	cout << Hex2Dec(szStr) << endl;
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

bool isNumber(char szStr[])
{
	if ((szStr[0]<'0' || szStr[0]>'9') && szStr[0] != '-' && szStr[0] != '+')
		for (int i = 1; szStr[i]; i++)
		{
			if ((szStr[i]<'0' || szStr[i] > '9') && szStr[i] != '-' && szStr[i] != '+')return false;
		}
	return true;
}

int StringToInt(char szStr[])
{
	if (!isNumber(szStr))return 0;
	int decimal = 0;
	bool signed_number = false;
	if (szStr[0] == '+' || szStr[0] == '-')signed_number = true;
	for (int i = signed_number ? 1 : 0; szStr[i]; i++)
	{
		decimal *= 10;
		decimal += szStr[i] - 48;
	}
	if (szStr[0] == '-')decimal = -decimal;
	return decimal;
}

bool isBinNumber(char szStr[])
{
	int n = StrLen(szStr);
	char* buffer = new char[n + 1]{};
	for (int i = 0; szStr[i]; i++) buffer[i] = szStr[i];
	RemoveSpaces(buffer);
	for (int i = 0; buffer[i]; i++)
	{
		if (buffer[i] != '0' && buffer[i] != '1')
		{
			delete[] buffer;
			return false;
		}
	}
	delete[] buffer;
	return true;
}

bool isHexNumber(char szStr[])
{
	for (int i = 0; szStr[i]; i++)
	{
		if
			(
				!(szStr[i] >= '0' && szStr[i] <= '9') &&
				!(szStr[i] >= 'A' && szStr[i] <= 'F') &&
				!(szStr[i] >= 'a' && szStr[i] <= 'f')
				)
		{
			return false;
		}
	}
	return true;
}

int Bin2Dec(char szStr[])
{
	if (!isBinNumber(szStr))
	{
		cout << "Error: Not Binary" << endl;
		return 0;
	}
	int capacity = StrLen(szStr);
	int decimal = 0;  // Десятичное число
	int weight = 1;   // Весовой коэффициент
	for (int i = capacity - 1; i >= 0; i--)
	{
		if (szStr[i] == ' ') continue;
		decimal += (szStr[i] - 48)*weight;
		weight *= 2;
	}
	return decimal;
}

int Hex2Dec(char szStr[])
{
	if (!isHexNumber(szStr))
	{
		cout << "Error: Not Hex" << endl;
		return 0;
	}
	int decimal = 0;  // Десятичное число
	int weight = 1;   // Весовой коэффициент
	for (int i = StrLen(szStr) - 1; i >= 0; i--)
	{
		int digit;
		if (szStr[i] >= 'a')digit = szStr[i] - 87;
		else if (szStr[i] >= 'A')digit = szStr[i] - 55;
		else digit =szStr[i] - 48;
		decimal += digit*weight;
		weight *= 16;
	}
	return decimal;
}