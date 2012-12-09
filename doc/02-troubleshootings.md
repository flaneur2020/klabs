# Troubleshootings

```
$ sudo rmmod bad_kmod.ko
ERROR: module bad_kmod in use
$ sudo rmmod -f bad_kmod.ko
ERROR: removing bad_kmod: device or resource busy
```

Use a virtual machine.

Once you make a NULL dereference or other such mistake, you've put the kernel into an unknown state. A kernel OOPS kills the calling thread, so it'll never have a chance to reduce the reference count.

+ http://stackoverflow.com/questions/7663487/how-to-remove-a-failed-kernel-module
