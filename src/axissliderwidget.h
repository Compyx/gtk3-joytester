/** \file   axissliderwidget.h
 * \brief   Slider showing joystick axis value - header
 *
 */

#ifndef HAVE_AXIS_SLIDER_WIDGET_H
#define HAVE_AXIS_SLIDER_WIDGET_H

#include <gtk/gtk.h>

GtkWidget * axis_slider_widget_new(int axis);
void        axis_slider_widget_update(GtkWidget *widget, gint16 value);

#endif
