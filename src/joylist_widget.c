/** \file   joylist_widget.c
 * \brief   List joystick devices
 *
 */

#include <gtk/gtk.h>
#include "joy_linux.h"

#include "joylist_widget.h"


#define NUM_JOYS    8


/** \brief  Model columns
 */
enum {
    COL_DEV,
    COL_NAME,
    COL_AXES,
    COL_BUTTONS
};

static GtkListStore *jlist_model = NULL;
static GtkWidget *jlist_view = NULL;
static GtkWidget *jlist_widget = NULL;


static GtkListStore *joylist_model_create(void)
{
    GtkListStore *store;
    GtkTreeIter iter;
    unsigned int i;

    store = gtk_list_store_new(
            4,
            G_TYPE_STRING,
            G_TYPE_STRING,
            G_TYPE_INT,
            G_TYPE_INT);

    for (i = 0; i < NUM_JOYS; i++) {
        joy_info_t *joy = joylist_get_joyinfo(i);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                COL_DEV,        joy->dev,
                COL_NAME,       joy->name,
                COL_AXES,       joy->axes,
                COL_BUTTONS,    joy->buttons,
                -1);
    }
    return store;
}


static GtkWidget *joylist_view_create(GtkListStore *model)
{
    GtkWidget *view;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(view), TRUE);
    gtk_widget_set_vexpand(view, TRUE);

    /* col 0: device node */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(
            "device", renderer,
            "text", 0 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    /* col 1: device name */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(
            "name", renderer,
            "text", 1 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    /* col 2: axes */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(
            "axes", renderer,
            "text", 2 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    /* col 3: buttons */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(
            "buttons", renderer,
            "text", 3 , NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);



    return view;
}


GtkWidget *joylist_widget_create(void)
{
    jlist_widget = gtk_grid_new();

    joylist_create();
    jlist_model = joylist_model_create();
    jlist_view = joylist_view_create(jlist_model);
    gtk_grid_attach(GTK_GRID(jlist_widget), jlist_view, 0, 0, 1, 1);

    gtk_widget_show_all(jlist_widget);
    return jlist_widget;
}



