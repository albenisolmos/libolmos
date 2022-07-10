#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "ol_string.h"
#include "ol_desktop.h"

char ** ol_desktop_get_apps_list(guint *len_list)
{
	DIR *dr;
	struct dirent *de;
	char *app_paths[] = {"/usr/share/applications"};
	char **list = malloc(sizeof(char *));
	size_t len_app_paths = sizeof(app_paths) / sizeof(char*);
	guint j = 0;
	(*len_list) = 0;

	for (guint i = 0; i < len_app_paths; i++)
	{
		dr = opendir(app_paths[i]);
		j = 0;

		if (dr == NULL) {
			g_message("Could not open current directory: %s", app_paths[i]);
			continue;
		}

		while ((de = readdir(dr)) != NULL) {
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
				continue;

			list = realloc(list, sizeof(char*) * j + 1);
			list[j] = ol_str_clone(de->d_name);

			(*len_list)++;
			j++;
		}

		closedir(dr);
	}

	return list;
}
