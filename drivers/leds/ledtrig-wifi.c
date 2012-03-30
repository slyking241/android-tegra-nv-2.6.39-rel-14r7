/*
 * Wifi LED Trigger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/leds.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include "leds.h"

static void wifi_trig_activate(struct led_classdev *led_cdev);
static struct led_trigger wifi_led_trigger = {
	.name     = "wifi",
	.activate = wifi_trig_activate,
};
static int last_state=0;

void set_wifi_led(int set)
{

     led_trigger_event(&wifi_led_trigger, set?LED_FULL:LED_OFF);
     last_state=set;
     
}


static void wifi_trig_activate(struct led_classdev *led_cdev)
{

    led_trigger_event(&wifi_led_trigger,last_state?LED_FULL:LED_OFF);
}


static int __init wifi_trig_init(void)
{
	return led_trigger_register(&wifi_led_trigger);
}

static void __exit wifi_trig_exit(void)
{
	led_trigger_unregister(&wifi_led_trigger);
}

module_init(wifi_trig_init);
module_exit(wifi_trig_exit);

MODULE_AUTHOR("antibyte>");
MODULE_DESCRIPTION("Wifi LED trigger");
MODULE_LICENSE("GPL");
