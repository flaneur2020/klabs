#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/random.h>
#include <asm/uaccess.h>

#define MOE_BUFFER_MAX_SIZE	64
#define MOE_COUNT 4 
#define PROCFS_NAME "Moe"

static struct proc_dir_entry *moe_proc_file;
static char moe_buffers[MOE_COUNT][MOE_BUFFER_MAX_SIZE] = {
    "●ω●\n", 
    "( ´ ▽ ` )ﾉ\n",
    "[]~(￣▽￣)~*\n",
    " ✪ω✪\n",
};

static int 
procfile_read(char *buffer,
              char **buffer_location,
              off_t offset,
              int buffer_length,
              int *eof,
              void *data) 
{
    char *moe_buffer;

    moe_buffer = moe_buffers[random32() % MOE_COUNT];
    if (offset + buffer_length > MOE_BUFFER_MAX_SIZE) {
        buffer_length = MOE_BUFFER_MAX_SIZE - offset;
        buffer_length = buffer_length < 0 ? 0: buffer_length;
    }
    memcpy(buffer, moe_buffer+offset, buffer_length);
    return buffer_length;
}

static int __init init_procfs(void)
{
    moe_proc_file = create_proc_entry(PROCFS_NAME, 0644, NULL);
    if (moe_proc_file == NULL) {
        remove_proc_entry(PROCFS_NAME, NULL);
        printk(KERN_ALERT "Error: Could not initialize /proc/%s", PROCFS_NAME);
        return -ENOMEM;
    }
    moe_proc_file->read_proc = procfile_read;
    moe_proc_file->write_proc = NULL;
    moe_proc_file->uid = 0;
    moe_proc_file->gid = 0;
    moe_proc_file->size = 37;

    printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);	
    return 0;
}

static void __exit exit_procfs(void)
{
    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}

module_init(init_procfs);
module_exit(exit_procfs);
