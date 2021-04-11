#include<stdio.h>

void copy(char *x){
	char buf[1024];
	strcpy(buf,x);
	printf("%s\r\n",buf);
}

int main(int argc, char *argv[]){
	if(strlen(argv[1])>1024){
		printf("parameter must be 100 or less..exit.\n");
		exit(-1);
	}
	printf("Processing Copy\n");
	copy(argv[1]);
	printf("Copying Successful\n");
	return 0;
}
