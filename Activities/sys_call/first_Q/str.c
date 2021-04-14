#include <linux/syscalls.h>

#include <linux/kernel.h>

SYSCALL_DEFINE1(length,char*,str)

{

char s[]="Gaya Patna";             

int i;

for(i=0;s[i]!='\0';i++);

printk("Length of string is : %d",i);

return i;

}
