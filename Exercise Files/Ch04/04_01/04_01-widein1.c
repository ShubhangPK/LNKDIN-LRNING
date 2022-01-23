#include <locale.h>
#include <wchar.h>

int main()
{
	wchar_t wch;

	setlocale(LC_CTYPE,"en_US.UTF-8");

	wprintf(L"What would you like to eat? ");
	wch = getwchar();
	wprintf(L"%lc sounds yummy!\n",wch);

	return(0);
}

