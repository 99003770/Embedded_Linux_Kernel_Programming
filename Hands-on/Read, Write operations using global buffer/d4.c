//Additional Headers
#include <linux/init.h>

#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/fs.h>

#include <linux/cdev.h>

#include <linux/device.h>

#include <linux/slab.h>

#include <linux/uaccess.h>
#define MAX_SIZE 1024

//Global
unsigned char *pbuffer;
int rd_offset=0;
int wr_offset=0;
int buflen=0;
int wcount;
int ret;
int rcount;
int pseudo_open(struct inode* inode , struct file* file)

{

	printk("Pseudo--open method\n");

	return 0;

}

int pseudo_close(struct inode* inode , struct file* file)

{

	printk("Pseudo--release method\n");

	return 0;

}

ssize_t pseudo_read(struct file * file, char __user * buf , size_t size, loff_t * off)

{

if(buflen==0)
//wr_offset-rd_offset==0
{
	printk("buffer is empty\n");
	return 0;
}
rcount = size;
if(rcount > buflen)
rcount = buflen;
//min of buflen, size
ret=copy_to_user(pbuffer, buf + rd_offset, rcount);
if(ret)
{
	printk("copy to user failed\n");
	return -EFAULT;
}
rd_offset+=rcount;
buflen -= rcount;
	printk("Pseudo--read method\n");
	return 0;

}

ssize_t pseudo_write(struct file * file, const char __user * buf , size_t size, loff_t * off)

{

	printk("Pseudo--write method\n");
	//Write method:-
if(wr_offset >= MAX_SIZE)
{
	printk("buffer is full\n");
	return -ENOSPC;
}
wcount = size;
if(wcount > MAX_SIZE - wr_offset)
wcount = MAX_SIZE - wr_offset;
//min
ret=copy_from_user(pbuffer, buf + wr_offset, wcount);
if(ret)
{
	printk("copy from user failed\n");
	return -EFAULT;
}
wr_offset += wcount;
buflen += wcount;
	printk("Succesfully copied, WR_OFFSET=%d,BUFLEN=%d\n",wr_offset, buflen);
	return 0;

}

struct cdev cdev;

int ndevices=1;

struct file_operations fops = {

.open		= pseudo_open,

.release 	= pseudo_close,

.write 	= pseudo_write,

.read 		= pseudo_read

};

 

dev_t pdevid;

 

static int __init psuedo_init(void)

{

  int ret;

  int i=0;

  ret=alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");

  if(ret) {

	printk("Pseudo: Failed to register driver\n");

	return -EINVAL;

	}
  pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);

  cdev_init(&cdev, &fops);

  kobject_set_name(&cdev.kobj,"pdevice%d",i);

  ret = cdev_add(&cdev, pdevid, 1);

  printk("Successfully registered,major=%d,minor=%d\n",

  MAJOR(pdevid), MINOR(pdevid));

  printk("Pseudo Driver Sample..welcome\n");

  return 0;

}

static void __exit psuedo_exit(void) {

cdev_del(&cdev);

unregister_chrdev_region(pdevid, ndevices);

printk("Pseudo Driver Sample..Bye\n");

}

 

module_init(psuedo_init);

module_exit(psuedo_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR("Danish Alam");

MODULE_DESCRIPTION("Register Char Driver");

