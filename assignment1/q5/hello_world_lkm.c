#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>

MODULE_AUTHOR("Vedant Saini");
MODULE_DESCRIPTION("kernel module hello world");

static int __init hello_world_lkm_init(void){
	printk(KERN_INFO "Hello world\n");
	return 0;
}

static void __exit hello_world_lkm_exit(void){
	printk(KERN_INFO "Bye!\n");
}


module_init(hello_world_lkm_init);
module_exit(hello_world_lkm_exit);

