#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/cdev.h>

static struct task_struct *task1;
static struct task_struct *task2;
int i=0;
static int thread_one(void *pargs){
	while(!kthread_should_stop())
{
	printk("Thread A--%d\n",i++);
	msleep(1000); //ssleep, usleep
}
do_exit(0);
return 0;
}
  static int thread_two(void *pargs){
	int j;
	while(!kthread_should_stop())
{
	printk("Thread B--%d\n",j++);
	msleep(1000); //ssleep, usleep
}
do_exit(0);
return 0;
}
static int __init tdemo_init(void)
{
task1=kthread_run(thread_one, NULL, "thread_A");
//kthread_create + wake_up_process
task2=kthread_run(thread_two, NULL, "thread_B");
printk("Pseudo Driver Sample...Welcome\n");
return 0;
}
static void __exit tdemo_exit(void)
{
if(task1)
kthread_stop(task1);
if(task2)
kthread_stop(task2);
}
module_init(tdemo_init);
module_exit(tdemo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("Parameter demo Module");
