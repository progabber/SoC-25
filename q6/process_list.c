#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>

MODULE_AUTHOR("Vedant Saini");
MODULE_DESCRIPTION("Process list");

static int __init process_list_init(void){
	printk(KERN_INFO "Hello world\n");
	return 0;
}

static void __exit process_list_exit(void){
	printk(KERN_INFO "Bye!\n");
}


module_init(process_list_init);
module_exit(process_list_exit);

