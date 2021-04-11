#include <stdio.h>
#include <string.h>

void setup() {
    setvbuf(stdin, (char *)NULL, _IONBF, 0);
    setvbuf(stdout, (char *)NULL, _IONBF, 0);
    setvbuf(stderr, (char *)NULL, _IONBF, 0);
}

int main()
{
	setup();

	char buf[0x64];
	char Check[0x128] = "Hello";
	
	printf("buf Test:");

	scanf("%s",buf);

	if(strcmp(Check, "Hello") == 0){
		printf("Hello\n");
	}
	else{
		printf("Prob{Fake_Flag}\n");
	}
	return 0;
}
