#include<stdio.h>

int a[10];

void f(int idx){
  if(idx==7){
    for(int i=0;i<=7;i++){
      printf("%d",a[i]);
    }
    printf("\n");
    return;
  }
  int temp=2*a[idx]-a[idx-1];
  if(temp>=9) return;
  for(int i=9;i>temp;i--){
    a[idx+1]=i;
    f(idx+1);
  }
}

int main(){
  for(int q=1;q<=9;q++){
    for(int j=1;j<=9;j++){
      a[0]=q;
      a[1]=j;
      f(1);
    }
  }
}
