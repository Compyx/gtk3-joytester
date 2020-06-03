/** \file   appwindow.c
 * \brief   Main application window
 *
 */

#include <gtk/gtk.h>

#include "joy_linux.h"
#include "joylist_widget.h"
#include "joyevent_widget.h"


/** \brief  I/O channel used to watch the kernel device
 *
 * Pretty much hardwired to /dev/input/js0 for now
 */
static GIOChannel *io_channel;

/** \brief  Event source ID
 *
 * Currenly not used, but perhaps useful later when watching multiple devices
 */
static guint source_id;

/** \brief  Info on the current joystick
 */
static joy_info_t *joy_info;


/** \brief  GIOFunc callback for events of \a chan
 *
 * \param[in,out]   chan    I/O channel triggering the event
 * \param[in]       cond    condition flags of the event
 * \param[in]       data    extra user data (unused)
 *
 * \return  TRUE if the event was handled
 */
static gboolean on_io_watch(GIOChannel *chan,
                            GIOCondition cond,
                            gpointer data)
{
    if (cond & G_IO_IN) {
        /* new data arrived */
        g_print("Got G_IO_IN\n");
        joyevent_widget_update(0);
        return TRUE;
    } else if (cond & G_IO_HUP) {
        /* device unplugged (TODO: check fd) */
        g_print("Got G_IO_HUP\n");
        return FALSE;
    }
    return TRUE;    /* ??? */
}



/** \brief  Create main application window
 *
 * \param[in]   app Main application
 *
 * \return  GtkWindow
 */
GtkWidget *app_window_create(GtkApplication *app)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GError *err = NULL;

    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    grid = gtk_grid_new();
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 16);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 16);
    g_object_set(grid, "margin-top", 8, NULL);
    g_object_set(grid, "margin-bottom", 8, NULL);
    g_object_set(grid, "margin-left", 16, NULL);
    g_object_set(grid, "margin-right", 16, NULL);


    label = gtk_label_new("Hello world!");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), joylist_widget_create(), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), joyevent_widget_create(0), 0, 2, 1, 1);

    gtk_container_add(GTK_CONTAINER(window), grid);


    /* Set up GLib IO watch on js0 */
    g_print("Getting joy info for index 0: ");
    joy_info = joylist_get_joyinfo(0);
    g_print("OK\n");

    g_print("Opening IO channel for '%s': ", joy_info->dev);
    io_channel = g_io_channel_unix_new(joy_info->fd);
    if (io_channel == NULL) {
        g_print("Failed\n");
        exit(1);
    }
    g_print("OK\n");

    /* disable input translation, get raw binary data */
    g_io_channel_set_encoding(io_channel, NULL, &err);

    g_print("Adding watch .. ");
    source_id = g_io_add_watch(io_channel,
                               G_IO_IN|G_IO_HUP,
                               on_io_watch,
                               NULL);
    g_print("OK\n");

    return window;
}
