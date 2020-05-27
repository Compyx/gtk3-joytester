# gtk3-joytester

Gtk3 joystick code testing for VICE, or rather Linux joystick code testing which may someday land in VICE.

Currently this code is completely unusable. Widgets are unfinished/missing, the joystick polling is backwards and the Meson/Ninja stuff is missing any checks for non-gtk3 headers.
It also needs a lot more CFLAGS to adhere to my 'standard'.


## Building

To build this meson/ninja is required. See https://mesonbuild.com/ for details.

Basically make sure pip3 is installed (the python3 package manager) and then do `pip3 install meson`, this should pull in all required stuff for Meson/Ninja. I personally run that with `sudo` so it gets installed system-wide.


Once that is done, run `meson builddir`, which runs meson and creates a separate builddir (meson requires this). When that succeeds, `cd builddir` and `ninja` to build.
If all goes well, the binary can be run with `./gtk3-joytester`.




