#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main() {
	printf("MY MALLOC\n");
	int i = 0;
	char *str;
	write(1, "1\n", 2);
	str = malloc(1000);
	write(1, "2\n", 2);
	realloc(str, 2000);
}
