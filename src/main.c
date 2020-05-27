/** \file   main.c
 * \brief   Gtk3/GDK joystick handling tester
 *
 */

#include <gtk/gtk.h>


#include "appwindow.h"


/** \brief  Handler for the 'activate' event of the application
 *
 * \param[in]   app     application
 * \param[in]   data    extra event data (unused)
 */
static void on_activate(GtkApplication *app,
                        gpointer        data)
{
    g_print("%s:%d:%s() called.\n", __FILE__, __LINE__, __func__);

    GtkWidget *window = app_window_create(app);
    gtk_widget_show_all(window);
}





/** \brief  Application entry point
 *
 * \param[in]   argc    argument count
 * \param[in]   argv    argument vector
 *
 * \return  exit status
 */
int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new(
            "nl.compyx.gtk3-joytester",
            G_APPLICATION_FLAGS_NONE);

    g_signal_connect(G_OBJECT(app), "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    /* TODO: cleanup */

    return status;
}

