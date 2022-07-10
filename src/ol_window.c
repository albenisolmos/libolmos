#include "ol_window.h"

void ol_window_resize(GdkWindow *self, guint32 width, guint32 height) {
	//const static uint32_t values[] = { width, height };
	//xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
	gdk_window_resize(self, width, height);
}

void ol_window_move(GdkWindow *self, guint32 x, guint32 y) {
	gdk_window_move(self, x, y);
	//const static uint32_t values[] = { x, y};
	//xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
}
