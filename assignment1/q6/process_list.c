#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/sched/signal.h>

MODULE_AUTHOR("Vedant Saini");
MODULE_DESCRIPTION("Iterate through process list and print PID, STATE, NAME of each running process");

static int __init process_list_init(void){
	struct task_struct *task;
	rcu_read_lock();
	pr_info("PID\tSTATE\tNAME\n");
	for_each_process(task){
		pr_info("%d\t%ld\t%s\n", task->pid, task->state, task->comm);
	}
	rcu_read_unlock();
	return 0;
}

static void __exit process_list_exit(void){
	printk(KERN_INFO "Kaam khatam paisa hazam!\n");
}


module_init(process_list_init);
module_exit(process_list_exit);

