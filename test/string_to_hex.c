#include <stdio.h>
#include <string.h>

int main(void)
{
	int i = 0;
	char str[] = "哈利巴多";
	int str_len = strlen(str);
	for (i = 0; i < str_len; i++) {
		printf("0x%02x,\t", str[i]);
	}
	return 0;
}