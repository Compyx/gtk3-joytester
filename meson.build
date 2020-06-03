# vim: set syntax=meson:

# declare project name
project('gtk3-joyster', 'c',
         version: '0.1',
         default_options: ['c_std=c99'])

# only required for glib_compile_resource and similar, which I don't use (yet)
# import('gnome')

# set Gtk3 dependency
dep_gtk3 = dependency('gtk+-3.0')

# declare include directories
incdirs = include_directories('.', 'src')

# declare source dirs
src = ['src/main.c',
       'src/appwindow.c',
       'src/joy_linux.c',
       'src/joylist_widget.c',
       'src/joyevent_widget.c',
       'src/axissliderwidget.c']

# declare executable and its sources and libraries
executable('gtk3-joytester',
           sources: src,
           include_directories: incdirs,
           dependencies: [dep_gtk3])
