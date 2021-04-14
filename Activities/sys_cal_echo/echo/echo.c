#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#define __CR_testcall 401
int main() 
{
   printf("HELLO WORLD");
   int ret;
   char ch[200];
   ret=syscall(__CR_testcall,"Hello! Hi How r u?",ch);
   printf("\n echo string is %s\n", ch);
   if(ret<0)
     perror("testcall");
   return 0;
}
