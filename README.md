# libolmos

A library of utilities used by others olmos's projects.\
This library includes the next struct of funtionalities by file:

* ol_string.c: Extra functions to manipulate strings that isn't provided by `string.h`
* ol_regex.c: Functions to facilitate the use of regex tecnology from `regex.h`
* ol_desktop.c: Functions to facilitate the access of desktop data (Ex. An array of apps list) 
* ol_module.c: Functions to facilitate the use of [GModule](https://docs.gtk.org/gmodule/index.html)
* ol_strv_builder.c: Implementation of [GStrvBuilder](https://docs.gtk.org/glib/struct.StrvBuilder.html) because my installed version of glib hasn't it yet (i don't want to install a newest version from source :))
