#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/time.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/miscdevice.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>

static ssize_t led_write(struct file *file, const char __user *buf, size_t len, loff_t *pos);
static int led_open(struct inode *inode, struct file *file);
static ssize_t led_read(struct file *file, char __user *buf, size_t len, loff_t *pos);
static int led_release(struct inode *inodep, struct file *filp);

int gpio_led;
int gpio_isr;
int irq_number;

static const struct of_device_id led_of_match[] = {
    {.compatible = "gpio-led"},
    {.compatible = "gpio-isr"},
    {}};


MODULE_DEVICE_TABLE(of, led_of_match);


static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .read = led_read,
    .open = led_open,
    .release = led_release};

static const struct file_operations isr_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .read = led_read,
    .open = led_open,
    .release = led_release};

struct miscdevice led_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "my_led",
    .fops = &led_fops,
};

struct miscdevice isr_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "my_isr",
    .fops = &isr_fops,
};

/****************************************************************************************
 * Function implementation
 ****************************************************************************************/
static ssize_t led_write(struct file *file, const char __user *buf, size_t len, loff_t *pos)
{
    uint8_t rec_buf;

    if (copy_from_user(&rec_buf, buf, len) > 0)
    {
        pr_err("ERROR: Not all the bytes have been copied from user\n");
    }

    if (rec_buf == '1')
    {
        // set the GPIO value to HIGH
        gpio_direction_output(gpio_led, 1); // Bắt đầu với LED tắt
    }
    else if (rec_buf == '0')
    {
        // set the GPIO value to LOW
        gpio_direction_output(gpio_led, 0); // Bắt đầu với LED tắt
    }
    else
    {
        pr_err("Unknown command : Please provide either 1 or 0 %d\n", rec_buf);
    }
    return 1;
}

static int led_open(struct inode *inode, struct file *file)
{

    pr_info("%s %d\n", __func__, __LINE__);
    return 0;
}

static int led_release(struct inode *inodep, struct file *filp)
{
    pr_info("%s %d\n", __func__, __LINE__);
    return 0;
}

static ssize_t led_read(struct file *file, char __user *buf, size_t len, loff_t *pos)
{
    pr_info("%s %d\n", __func__, __LINE__);
    return 0;
}

static irqreturn_t gpio_isr_handler(int irq, void *dev_id)
{
    pr_info("GPIO Interrupt occurred!\n");
    return IRQ_HANDLED;  // ISR đã xử lý ngắt
}
// ---------------------------------------------------------------------------------------------

int led_driver_probe(struct platform_device *pdev)
{
    int ret = 0;
    struct device *dev;
    const struct of_device_id *match;

    pr_info("%s %d\n", __func__, __LINE__);
    dev = &pdev->dev;

    match = of_match_device(of_match_ptr(led_of_match), dev);
    pr_info("match : %s\n", match->compatible);

    if (!match)
    {
        dev_err(dev, "Device not supported\n");
        return -EINVAL;
    }

    // Cấu hình GPIO cho LED
    if (strcmp(match->compatible, "gpio-led") == 0)
    {
        //--------------------------------------- GPIO CONFIG LED----------------------------------------------------------------------//
        // Tìm số GPIO từ node
        gpio_led = of_get_named_gpio(dev->of_node, "gpio-led", 0);
        if (gpio_led < 0)
        {
            dev_err(dev, "Failed to get gpio-led\n");
            return gpio_led;
        }
        // Yêu cầu quyền điều khiển GPIO
        ret = gpio_request(gpio_led, "LED");
        if (ret)
        {
            dev_err(&pdev->dev, "Failed to request GPIO %d\n", gpio_led);
            return ret;
        }

        // Đặt GPIO thành output
        ret = gpio_direction_output(gpio_led, 1); // Bắt đầu với LED tắt
        if (ret)
        {
            dev_err(&pdev->dev, "Failed to set GPIO direction\n");
            gpio_free(gpio_led);
            return ret;
        }

        pr_info("LED driver probed successfully, GPIO: %d\n", gpio_led);

        //--------------------------------------- register port----------------------------------------------------------------------//
        ret = misc_register(&led_device);
        if (ret)
        {
            gpio_free(gpio_led); // Giải phóng GPIO LED nếu không đăng ký được
            pr_err("can't misc_register gpio_led\n");
            return -1;
        }
    }
    //--------------------------------------- GPIO CONFIG GPIO ISR----------------------------------------------------------------------//
    else if (strcmp(match->compatible, "gpio-isr") == 0)
    {
        // Tìm số GPIO từ node
        gpio_isr = of_get_named_gpio(dev->of_node, "gpio-isr", 0);
        if (gpio_isr < 0)
        {
            dev_err(dev, "Failed to get gpio-isr\n");
            return gpio_isr;
        }
        // Yêu cầu quyền điều khiển GPIO
        ret = gpio_request(gpio_isr, "LED");
        if (ret)
        {
            dev_err(&pdev->dev, "Failed to request GPIO %d : gpio_isr\n", gpio_isr);
            return ret;
        }

        // Đặt GPIO thành INPUT
        ret = gpio_direction_input(gpio_isr);
        if (ret)
        {
            dev_err(&pdev->dev, "Failed to set GPIO direction\n");
            gpio_free(gpio_isr);
            return ret;
        }

        pr_info("ISR driver probed successfully, GPIO: %d\n", gpio_isr);
        // create callback isr
        irq_number = gpio_to_irq(gpio_isr);
        ret = request_irq(irq_number, gpio_isr_handler, IRQF_TRIGGER_FALLING, "gpio_irq", NULL);
        if (ret)
        {
            dev_err(dev, "Failed to request IRQ\n");
            gpio_free(gpio_isr);
            return ret;
        }
        //--------------------------------------- register port----------------------------------------------------------------------//
        ret = misc_register(&isr_device);
        if (ret)
        {
            gpio_free(gpio_isr); // Giải phóng GPIO ISR nếu không đăng ký được
            pr_err("can't misc_register gpio_isr\n");
            return -1;
        }
    }
    else
    {
        pr_err("Not Match  %s\n", match->compatible);
    }

    return 0;
}

int led_driver_remove(struct platform_device *pdev)
{
    struct device *dev;
    const struct of_device_id *match;
    pr_info("%s %d\n", __func__, __LINE__);

    dev = &pdev->dev;

    match = of_match_device(of_match_ptr(led_of_match), dev);
    pr_info("match : %s\n", match->compatible);

    if (!match)
    {
        dev_err(dev, "Device not supported\n");
        return -EINVAL;
    }

    if (strcmp(match->compatible, "gpio-led") == 0)
    {
        // Giải phóng GPIO
        if (gpio_is_valid(gpio_led))
        {
            gpio_free(gpio_led);
            misc_deregister(&led_device);
        }
        pr_info("LED driver removed successfully, GPIO: %d\n", gpio_led);
    }
    else if (strcmp(match->compatible, "gpio-isr") == 0)
    {
        if (gpio_is_valid(gpio_isr))
        {
            gpio_free(gpio_isr);
            misc_deregister(&isr_device);
        }
        pr_info("ISR driver removed successfully, GPIO: %d\n", gpio_isr);
    }

    return 0;
}

static struct platform_driver led_driver = {
    .probe = led_driver_probe,
    .remove = led_driver_remove,
    .driver = {
        .name = "led",
        .of_match_table = of_match_ptr(led_of_match),
    }};

module_platform_driver(led_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blink Led kernel module");