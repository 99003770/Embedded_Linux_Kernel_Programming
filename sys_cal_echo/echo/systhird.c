#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>


SYSCALL_DEFINE2(mysyscall3, const char __user *,ch,char __user *,gett)
{
   char buffer[100],reve[100];
   int a;
   int i;
   int j;
   int length=0;
   a=copy_from_user(buffer,ch,50);
   if(a)
   {
      printk("copy");
      return -EFAULT;
   }
   while(buffer[length] != '\0')
   	length=length+1;
    j=length-1;
   
   for(i=0;i<length;i++)
   {
     reve[i] = buf[j];
    j--;
   }
   reve[length]='\0';
   a=copy_to_user(gett,reve,50);
   if(a)
   {
    return -EFAULT;
   }
   printk("%s",reve);
   return 0;
}
