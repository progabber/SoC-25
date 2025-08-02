#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
extern int good_to_go;
static int __init toggle_init(void) {
	good_to_go = 1;
	return 0;
}

static void __exit toggle_exit(void) {
	good_to_go = 0;
}
module_init(toggle_init);
module_exit(toggle_exit);

