#include <stdio.h>


int isTmax(int x) {
  printf("Parameter,%x\n", x + 0x01);
  printf("Mask, %x\n", 1 << 31);
  printf("inside the function 1, %d\n",(x + 0x01)^(1 << 31));
  printf("inside the function 2, %d\n",!((x + 0x01)^(1 << 31)));
  return !((x + 0x01)^(1 << 31));
}

int main(){
    
    printf("Function return, %d\n", isTmax(0x7fffffff));
    // printf("%d\n",1 << 31);
    // printf("%d\n",2147483647 + 0x01);
    // printf("%d\n",(2147483647 + 0x01 == 1 << 31) );
    printf("Outside the function,%d\n", !((2147483647 + 0x01)^(1 << 31)));
    return 0;
}