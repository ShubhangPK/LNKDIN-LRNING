#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main()
{
	wchar_t wstring[] = L"I * to code\n";

	setlocale(LC_ALL,"en_US.UTF-8");
	wstring[2] = 0x2665;
	fputws(wstring,stdout);

	return(0);
}

