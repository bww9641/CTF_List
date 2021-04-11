#include<stdio.h>

int main(){
	long long *a;
	printf("Which Address do you want to modify? : ");
	scanf("%lld",&a);
	printf("Change Value to : ");
	scanf("%lld",a);
	printf("Succefully Changed!");
	return 0;
}
