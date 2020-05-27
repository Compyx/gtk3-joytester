/** \file   joy_linux
 * \brief   Kernel joystick inteface for Linux
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <linux/joystick.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "joy_linux.h"


/** \brief  Number of joystick devices to scan
 */
#define NUM_JOYS    8


/** \brief  List of joystick devices
 */
static joy_info_t joy_info_list[NUM_JOYS];


/** \brief  Get information on a joystick device
 */
joy_info_t *joylist_get_joyinfo(unsigned int index)
{
    assert(index < NUM_JOYS);
    return &joy_info_list[index];
}



void joylist_create(void)
{
    int fd;
    int i;
    char devname[1024];

    for (i = 0; i < NUM_JOYS; i++) {
        snprintf(devname, sizeof(devname), "/dev/input/js%d", i);
        fd = open(devname, O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "failed to open '%s'\n", devname);
        } else {
            char name[1024];
            char axes;
            char buttons;

            if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0) {
                name[0] = '\0';
            }
            if (ioctl(fd, JSIOCGAXES, &axes) < 0) {
                axes = -1;
            }
            if (ioctl(fd, JSIOCGBUTTONS, &buttons) < 0) {
                buttons = -1;
            }

            strncpy(joy_info_list[i].dev, devname, 1024);
            joy_info_list[i].dev[1023] = '\0';
            strncpy(joy_info_list[i].name, name, 1024);
            joy_info_list[i].name[1023] = '\0';
            joy_info_list[i].axes = axes;
            joy_info_list[i].buttons = buttons;

            printf("dev: %s, name: %s, axes: %d, buttons: %d\n",
                    devname, name, (int)axes, (int)buttons);
            joy_info_list[i].fd = fd;
        }
    }
}

