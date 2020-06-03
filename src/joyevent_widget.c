/** \file   joyevent_widget.c
 * \brief   Display joystick events
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <linux/joystick.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "joy_linux.h"
#include "axissliderwidget.h"

#include "joyevent_widget.h"


static const char *labels[] = {
    "device path",
    "device name",
    "timestamp",
    "value",
    "type",
    "axis/button number"
};



static bool poll_joystick(unsigned int index);


static GtkWidget *joydevice_label = NULL;
static GtkWidget *joyname_label = NULL;
static GtkWidget *joytimestamp_label = NULL;
static GtkWidget *joybutton_label = NULL;
static GtkWidget *joyevent_label = NULL;
static GtkWidget *joyvalue_label = NULL;

static unsigned int joyindex = 0;


static GtkWidget *axis_widgets[8];


static gchar *get_event_type_desc(unsigned int e)
{
    gchar *event_desc[3] = { "BUTTON", "AXIS", "INIT" };
    gchar *event_list[4] = { NULL, NULL, NULL, NULL };

    unsigned int event_types[3] = {
        JS_EVENT_BUTTON,
        JS_EVENT_AXIS,
        JS_EVENT_INIT };
    int i;
    int s;

    for (i = 0, s = 0; i < 3; i++) {
        if (e & event_types[i]) {
            event_list[s++] = event_desc[i];
        }
    }
    return g_strjoinv(" | ", event_list);
}


static GtkWidget *create_label(const gchar *text)
{
    GtkWidget *label = gtk_label_new(text);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    g_object_set(label, "margin-left", 16, NULL);
    return label;
}


GtkWidget *joyevent_widget_create(unsigned int index)
{
    GtkWidget *grid;
    GtkWidget *label;
    size_t i;
    joyindex = index;
    int a;
    joy_info_t *joyinfo = joylist_get_joyinfo(index);


    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 16);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 8);

    label = gtk_label_new(NULL);
    g_object_set(label, "margin-left", 16, NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Joystick events</b>");

    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 3, 1);

    for (i = 0; i < sizeof labels / sizeof labels[0]; i++) {
        gtk_grid_attach(GTK_GRID(grid), create_label(labels[i]), 0, i + 1, 1 , 1);
    }

    joydevice_label = create_label(joyinfo->dev);
    gtk_grid_attach(GTK_GRID(grid), joydevice_label, 1, 1, 1, 1);
    joyname_label = create_label(joyinfo->name);
    gtk_grid_attach(GTK_GRID(grid), joyname_label, 1, 2, 2, 1);
    joytimestamp_label = create_label("<none>");
    gtk_grid_attach(GTK_GRID(grid), joytimestamp_label, 1, 3, 2, 1);

    joyvalue_label = create_label("<none>");
    gtk_grid_attach(GTK_GRID(grid), joyvalue_label, 1, 4, 1, 1);


    joyevent_label = create_label("<none>");
    gtk_grid_attach(GTK_GRID(grid), joyevent_label, 1, 5, 1, 1);

    joybutton_label = create_label("<none>");
    gtk_grid_attach(GTK_GRID(grid), joybutton_label, 1, 6, 1, 1);

    for (a = 0; a < 8; a++) {
        axis_widgets[a] = axis_slider_widget_new(a);
        gtk_grid_attach(GTK_GRID(grid), axis_widgets[a], 0, 7 + a, 2, 1);
    }

    gtk_widget_show_all(grid);
    return grid;
}


bool joyevent_widget_update(unsigned int index)
{
    return poll_joystick(index);
}



static bool poll_joystick(unsigned int index)
{
    struct js_event e;
    gchar buffer[1024];

    if (!joy_poll(index, &e)) {
        return false;
    }

    /* handle timestamp */
    g_snprintf(buffer, sizeof(buffer), "$%04x", e.time);
    gtk_label_set_text(GTK_LABEL(joytimestamp_label), buffer);

    /* handle event value */
    g_snprintf(buffer, sizeof(buffer), "$%02x", e.value);
    gtk_label_set_text(GTK_LABEL(joyvalue_label), buffer);

    /* handle event type */
    gchar *s = get_event_type_desc(e.type);
    gtk_label_set_text(GTK_LABEL(joyevent_label), s);
    g_free(s);

    /* handle event number */
    g_snprintf(buffer, sizeof(buffer), "$%02x", e.number);
    gtk_label_set_text(GTK_LABEL(joybutton_label), buffer);

    if (e.type & JS_EVENT_AXIS) {
        if (e.number < 8) {
            g_print("axis 0: value %d\n", e.value);
            axis_slider_widget_update(axis_widgets[e.number], e.value);
        }
    }

    return true;
}

