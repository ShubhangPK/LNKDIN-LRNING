#include <locale.h>
#include <wchar.h>

int main()
{
	wchar_t howdy[] = {
		0x41f, 0x440, 0x438, 0x432,
		0x435, 0x442, 0x021, '\n', '\0'
	};
	int x;

	setlocale(LC_ALL,"en_US.UTF-8");

	for( x=0; howdy[x]; x++)
		putwchar(howdy[x]);

	return(0);
}
