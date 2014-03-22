#undef PDEBUG
#ifdef HELLOWORLD_DEBUG
#	ifdef __KERNEL__
#		define PDEBUG(fmt, args...) printk(KERN_DEBUG "helloworld: " fmt, ## args)
#	else
#		define PDEBUG(fmt, args...) fprintk(stderr, fmt, ## args)
#	endif
#else
#	define PDEBUG(fmt, args...) /* debugging turned of */
#endif
