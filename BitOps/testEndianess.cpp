#include <stdio.h>

int main()
{
   union s
   {
     unsigned int i;
     unsigned char ch[4];
   };
 
  union s obj;
  obj.i=1u;
  printf("%d %d %d %d %d\n",obj.i,obj.ch[0],obj.ch[1],obj.ch[2],obj.ch[3]);

  unsigned int num = 0x01020304;
  unsigned char *myChar = (unsigned char *)&num;
  printf("num = %x mychar = %x\n",num,*myChar);
 
  
  return 1;
}


