#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define __NR_testcall 399

int main(){
int ret;
ret=syscall(__NR_testcall, "Hi! Danish");
printf("%d\n",ret);
if(ret<0)
	perror("testcall");
return 0;
}
