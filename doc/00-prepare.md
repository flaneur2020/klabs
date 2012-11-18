# Before Start

## Setup the envrionment in Ubuntu

```
export KERNEL_VERSION=`uname -r`
export KERNEL_PATH=/usr/src/linux-headers-$KERNEL_VERSION
sudo apt-get install linux-headers-$KERNEL_VERSION
sudo ln -nsf /lib/modules/$KERNEL_VERSION/build $KERNEL_PATH
```

## Troubleshootings

```
Nov 18 12:52:42 ub kernel: [10664.805086] hello: disagrees about version of symbol module_layout
```

Check your kernel source's version, it may be not match with your running kernel.

## References

+ [Setup Ubuntu for Building Kernel Modules](1)

[1] http://dinomite.net/blog/2007/setting-up-ubuntu-for-building-kernel-modules/
