/****************************************************************************************
 * Include Library
 ****************************************************************************************/
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
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/miscdevice.h>

#include "ssd1306.h"

static ssize_t user_ssd1306_write(struct file *file, const char __user *buf, size_t len, loff_t *pos);
static int user_ssd1306_open(struct inode *inode, struct file *file);
static ssize_t user_ssd1306_read(struct file *file, char __user *buf, size_t len, loff_t *pos);
static int user_ssd1306_release(struct inode *inodep, struct file *filp);

static const struct of_device_id ssd1306_of_match[] = {
    {.compatible = "solomon,ssd1306"},
    {},
};

static const struct file_operations ssd1306_fops = {
    .owner = THIS_MODULE,
    .write = user_ssd1306_write,
    .read = user_ssd1306_read,
    .open = user_ssd1306_open,
    .release = user_ssd1306_release};

struct miscdevice ssd1306_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "ssd1306",
    .fops = &ssd1306_fops,
};

/****************************************************************************************
 * Function implementation
 ****************************************************************************************/
static ssize_t user_ssd1306_write(struct file *file, const char __user *buf, size_t len, loff_t *pos)
{
  pr_info("%s %d\n", __func__, __LINE__);
  return 1;
}

static int user_ssd1306_open(struct inode *inode, struct file *file)
{

  pr_info("%s %d\n", __func__, __LINE__);
  return 0;
}

static int user_ssd1306_release(struct inode *inodep, struct file *filp)
{
  pr_info("%s %d\n", __func__, __LINE__);
  return 0;
}

static ssize_t user_ssd1306_read(struct file *file, char __user *buf, size_t len, loff_t *pos)
{
  pr_info("%s %d\n", __func__, __LINE__);
  return 0;
}
// ---------------------------------------------------------------------------------------------

int ssd1306_driver_probe(struct i2c_client *client)
{
  int ret = 0;
  pr_info("%s %d\n", __func__, __LINE__);

  ret = misc_register(&ssd1306_device);
  if (ret)
  {
    pr_err("can't misc_register\n");
    return -1;
  }

  SSD1306_DisplayInit(client);

  // Set cursor
  SSD1306_SetCursor(0, 0);

  // Write String to OLED
  SSD1306_String("TEST");

  return 0;
}

int ssd1306_driver_remove(struct i2c_client *client)
{
  pr_info("%s %d\n", __func__, __LINE__);
  SSD1306_SetCursor(50, 25);
  SSD1306_String("BYE!!!");

  msleep(1000);

  // Set cursor
  SSD1306_SetCursor(0, 0);
  // clear the display
  SSD1306_Fill(0x00);

  SSD1306_Write(true, 0xAE); // Entire Display OFF
  misc_deregister(&ssd1306_device);
  return 0;
}

static struct i2c_driver ssd1306_driver = {
    .probe_new = ssd1306_driver_probe,
    .remove = ssd1306_driver_remove,
    .driver = {
        .name = "ssd1306",
        .of_match_table = ssd1306_of_match,
    }};

module_i2c_driver(ssd1306_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blink Led kernel module");