#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <asm/barrier.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#include <asm-generic/errno-base.h>
#include <linux/wait.h>

/*
 * System Timer base address
 *
 * Note: Phys. SoC address 0x7Ennnnnn (as given in data sheet) gets mapped
 *       to 0x20nnnnnn by built-in MMU
 *
 * */
#define TIMER_PAGE_BASE 0x20003000
#define TIMER_OFFSET 	4

#define	M_DEVICE_NAME	"timeTrigger10ms"

static dev_t 			timer_dev_number;
static struct cdev 		*driver_object;
static struct class 	*timer_class;
static struct device 	*timer_dev;
static int 				timer_irq;
static char 			*devname = "timeTrigger";
static wait_queue_head_t sleeping_for_ir;

static void 			*timer_pf; /* the page frame containing the timer */
static unsigned long 	*timer_clo;
static unsigned long 	*timer_cmp1; /* use cmp1, since cmp0 is used by GPU! */

static unsigned int 	irqNum;
static unsigned long	timerValue;

struct timedInterrupt{
	unsigned int	irqNum;
	unsigned long	timer;
};

static irqreturn_t rpi_timer_isr( int irq, void *data )
{
	/* wake up read function to retrieve new data */
	wake_up( &sleeping_for_ir );

	return IRQ_HANDLED;
}

static irqreturn_t hard_isr( int irq, void *dev_id )
{
	timerValue = *( (unsigned long*)(timer_pf+0x4) );
	*timer_cmp1 += 10000;

	/* counts rising edges since last read */
	irqNum++;

	printk("hard_irq on irq %d at dev %p\n",irq, dev_id);

	/* release timer interrupt flag */
	test_and_set_bit(1,timer_pf);

	return IRQ_WAKE_THREAD;
}

static int config_timerCmp( void )
{
	int err, rpi_irq;

	rpi_irq = 1;	/* Interrupt no.1 => maps to System Timer Compare register 1 */
	printk("gpio_to_irq returned %d\n", rpi_irq);
	if (rpi_irq < 0) {
		printk("gpio_to_irq failed %d\n", rpi_irq);
		return -1;
	}
	err = request_threaded_irq( rpi_irq, hard_isr, rpi_timer_isr, IRQF_TIMER, devname, driver_object);
	printk("driver_object: %p\n", driver_object);
	if (err) {
		printk("request_irq failed with %d\n", err);
		return -1;
	}
	printk("Module 'timeTrigger' successfully configured\n");
	return rpi_irq;
}

static ssize_t driver_read( struct file *instanz, char __user *user,
		size_t count, loff_t *offset )
{
	unsigned long not_copied, to_copy;
	struct timedInterrupt timerStruct;

	irqNum = 0;	/* reset indicator variable */

	/* wait for timer event and wake up caller process */
	wait_event_interruptible( sleeping_for_ir, irqNum);

	timerStruct.irqNum = irqNum;
	timerStruct.timer = timerValue;

	/* copy data to user-space */
	to_copy = min( count, sizeof(struct timedInterrupt) );
	not_copied = copy_to_user(user, &(timerStruct), to_copy);

	return to_copy-not_copied;
}

static struct file_operations fops = {
		.owner= THIS_MODULE,
		.read= driver_read,
};

static int __init mod_init( void )
{
	dev_info(timer_dev, "mod_init");
	init_waitqueue_head( &sleeping_for_ir );

	if( alloc_chrdev_region(&timer_dev_number,0,1,M_DEVICE_NAME)<0 )
		return -EIO;

	driver_object = cdev_alloc(); /* Reserve character file handler */

	if( driver_object==NULL )
		goto free_device_number;

	driver_object->owner = THIS_MODULE;
	driver_object->ops = &fops;

	if( cdev_add(driver_object,timer_dev_number,1) )
		goto free_cdev;

	timer_class = class_create( THIS_MODULE, M_DEVICE_NAME );

	if( IS_ERR( timer_class ) ) {
		pr_err( "timerTrigger: no udev support\n");
		goto free_cdev;
	}
	timer_dev = device_create( timer_class, NULL, timer_dev_number, NULL, "%s", M_DEVICE_NAME );

	if ( IS_ERR(timer_dev) )
		goto free_class;

	timer_irq = config_timerCmp();
	if (timer_irq < 0) {
		goto free_device;
	}

	/* get the mapping for the page frame containing the timer */
	timer_pf = ioremap(TIMER_PAGE_BASE, SZ_4K);
	/* and set the pointer to the timer compare register 0 */
	timer_clo  = timer_pf + 0x4;
	timer_cmp1 = timer_pf + 0x10;
	*timer_cmp1 = *timer_clo + 10000;
	pr_info("bcm2708_usec initialized; timer @ %pK to value %lu\n", timer_cmp1, *timer_cmp1);

	return 0;

	/* ERROR HANDLING (below) */
	free_device:
	device_destroy( timer_class, timer_dev_number );
	free_class:
	class_destroy( timer_class );
	free_cdev:
	kobject_put( &driver_object->kobj );
	free_device_number:
	unregister_chrdev_region( timer_dev_number, 1 );
	/* if the timer was mapped (final step of successful module init) */
	if (timer_pf)
		/* release the mapping */
		iounmap(timer_pf);
	return -EIO;
}

static void __exit mod_exit( void )
{
	dev_info(timer_dev, "mod_exit");

	/* if the timer was mapped (final step of successful module init) */
	if (timer_pf)
		/* release the mapping */
		iounmap(timer_pf);

	device_destroy( timer_class, timer_dev_number );
	class_destroy( timer_class );
	cdev_del( driver_object );
	unregister_chrdev_region( timer_dev_number, 1 );
	free_irq(timer_irq, driver_object);
	return;
}

module_init( mod_init );
module_exit( mod_exit );
MODULE_LICENSE("GPL");
