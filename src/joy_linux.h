/** \file   joy_linux.h
 * \brief   Kernel joystick inteface for Linux - header
 *
 */

#ifndef HAVE_JOY_LINUX_H
#define HAVE_JOY_LINUX_H

#include <stdbool.h>
#include <linux/joystick.h>

/** \brief  Joystick info structure
 */
typedef struct joy_info_s {
    char dev[1024];     /* kernel device name */
    char name[1024];    /* joystick name */
    int axes;           /* number of axes */
    int buttons;        /* number of buttons */
    int fd;             /* file descriptor */
} joy_info_t;


void joylist_create(void);
void joylist_destroy(void);

joy_info_t *joylist_get_joyinfo(unsigned int index);
bool joy_poll(unsigned int index, struct js_event *event);

#endif
