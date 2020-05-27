/** \file   joyevent_widget.h
 * \brief   Display joystick events - header
 *
 */

#ifndef JOYEVENT_WIDGET_H
#define JOYEVENT_WIDGET_H

#include <gtk/gtk.h>
#include <stdbool.h>

GtkWidget *joyevent_widget_create(unsigned int index);
bool joyevent_widget_update(unsigned int index);

#endif
