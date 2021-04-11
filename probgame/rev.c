#include<stdio.h>

int main(){
  long long a,b,c,d,e,f,g,h,i,j,res;
  for(a=0;a<=9;a++){
    for(b=0;b<=9;b++){
      for(c=0;c<=9;c++){
        for(d=0;d<=9;d++){
          for(e=0;e<=9;e++){
            for(f=0;f<=9;f++){
              for(g=0;g<=9;g++){
                for(h=0;h<=9;h++){
                  for(i=0;i<=9;i++){
                    for(j=0;j<=9;j++){
                      int sw=0;
                      for(long long cnt=9;cnt>=1;cnt--){
                        res=j+i*10+h*100+g*1000+f*10000+e*100000+d*1000000+c*10000000+b*100000000+a*1000000000;
                        for(long long temp=cnt;temp>=1;temp--){
                          res/=10;
                        }
                        printf("%lld",res);
                        if(res%(10-cnt)){
                          sw=1;
                          break;
                        }
                      }
                      if(sw==1) continue;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
