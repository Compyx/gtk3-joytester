/** \file   axissliderwidget.c
 * \brief   Slider showing joystick axis value
 *
 */

#include <gtk/gtk.h>

#include "axissliderwidget.h"


#define SLIDER_COL  1
#define SLIDER_ROW  0



GtkWidget *axis_slider_widget_new(int axis)
{
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *level;
    gchar buffer[256];

    grid = gtk_grid_new();

    /* add label */
    g_snprintf(buffer, sizeof(buffer), "Axis %d", axis);
    label = gtk_label_new(buffer);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    /* add level bar */
    level = gtk_level_bar_new_for_interval(0.0, (double)G_MAXUINT16);
    gtk_level_bar_set_value(GTK_LEVEL_BAR(level), (double)(G_MAXUINT16 /2));
    gtk_widget_set_hexpand(level, TRUE);
    gtk_grid_attach(GTK_GRID(grid), level, SLIDER_COL, SLIDER_ROW, 1, 1);

    return grid;
}


void axis_slider_widget_update(GtkWidget *widget, gint16 value)
{
    GtkWidget *slider = gtk_grid_get_child_at(
            GTK_GRID(widget),
            SLIDER_COL,
            SLIDER_ROW);
    if (slider != NULL) {
        gtk_level_bar_set_value(GTK_LEVEL_BAR(slider), (double)(value + (G_MAXUINT16 / 2)));
    }
}
