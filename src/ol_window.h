#ifndef __OL_WINDOW_H__
#define __OL_WINDOW_H__

#include <gtk/gtk.h>

void ol_window_move( GdkWindow *self, guint32 x, guint32 y );
void ol_window_resize( GdkWindow *self, guint32 width, guint32 height );

#endif
