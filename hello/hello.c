#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>

MODULE_DESCRIPTION("Hello");
MODULE_AUTHOR("fleuria");
MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
    pr_info("miao?");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "bye miao(w\n");
}

module_init(hello_init);
module_exit(hello_exit);
