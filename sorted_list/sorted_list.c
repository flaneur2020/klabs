#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/list.h>


MODULE_DESCRIPTION("sorted_list");
MODULE_AUTHOR("fleuria");
MODULE_LICENSE("GPL");

struct sdentry {
    int value;
    struct list_head list; 
};

struct sdentry sdlist;

/* ----------------------------------------------- */

static int sdinit(struct sdentry *listp) {
    listp->value = 0;
    INIT_LIST_HEAD(&listp->list);
    return 0;
}

static int sdinsert(struct sdentry *listp, int value) {
    struct sdentry *entry;
    struct sdentry *new_entry;
    int inserted = 0;

    new_entry = kmalloc(sizeof(struct sdentry), GFP_KERNEL);
    if (new_entry == NULL) {
        printk(KERN_ERR "sdinsert(): kmalloc() failed\n");
        return -1;
    }
    new_entry->value = value;
    // 
    list_for_each_entry(entry, &listp->list, list) {
        if (value < entry->value) {
            list_add_tail(&new_entry->list, &entry->list);
            inserted = 1;
            break;
        }
    }
    if (list_empty(&listp->list) || value < (list_entry(&listp->list, struct sdentry, list)->value)) {
        list_add(&new_entry->list, &listp->list);
    }
    else if (! inserted) {
        list_add_tail(&new_entry->list, &listp->list);
    } 
    return 0;
}

static int sdpop(struct sdentry *listp, int *value) {
    struct sdentry *head_entry;

    if (list_empty(&listp->list)) {
        return 0;
    }
    head_entry = list_entry(listp->list.next, struct sdentry, list);
    list_del(&head_entry->list);
    *value = head_entry->value;
    kfree(head_entry);
    return 1;
}

/* ----------------------------------------------- */


static int __init sdlist_init(void)
{
    struct sdentry *entry;
    sdinit(&sdlist);
    sdinsert(&sdlist, 2);
    sdinsert(&sdlist, 3);
    sdinsert(&sdlist, 5);
    sdinsert(&sdlist, 4);
    sdinsert(&sdlist, 1);
    list_for_each_entry(entry, &sdlist.list, list) {
        printk("%d ", entry->value);
    }
    printk("\n");

    return 0;
}

static void __exit sdlist_exit(void)
{
    int value = 0; 

    while (sdpop(&sdlist, &value)) {
        printk(KERN_INFO "poped %d\n", value);
    }
}

module_init(sdlist_init);
module_exit(sdlist_exit);
