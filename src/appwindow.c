/** \file   appwindow.c
 * \brief   Main application window
 *
 */

#include <gtk/gtk.h>

#include "joylist_widget.h"
#include "joyevent_widget.h"



static gboolean timeout_callback(GtkWidget *widget)
{
    joyevent_widget_update(1);
    return TRUE;
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

    g_timeout_add(100, (GSourceFunc)timeout_callback, NULL);


    return window;
}
