#include <string.h>
#include <stdlib.h>

void BufferOverflow (char *str)
{
	char buffer [20];
	strcpy(buffer, str);
}

int main()
{
	char grande_string[128];
	int i;
	for(i=0; i<128; i++)
	{
		grande_string[i] = 'A';
	}
	BufferOverflow(grande_string);
 	exit(0);
}
