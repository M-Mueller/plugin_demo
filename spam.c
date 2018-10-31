#include "spam.h"

#include <png.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void spam()
{
	// add some external dependency that should be copied
	// into the package by linuxdeployqt
	png_sig_cmp("bla", 0, 0);

	printf("Loading foo plugin\n");

	// dirty way of getting a relative path to the plugin independend
	// of the current working directory
	char plugin_path[PATH_MAX];
	ssize_t len = readlink("/proc/self/exe", plugin_path, sizeof(plugin_path)-1);
	if (len == -1)
	{
		printf("readlink failed");
		exit(1);
	}
	plugin_path[len-4] = '\0'; // remove 'demo' from path
	strcat(plugin_path, "/../lib/spam/libfoo.so");

	char* error;
	dlerror(); //clear error stack

	void* lib = dlopen(plugin_path, RTLD_LAZY);
	error = dlerror();
	if (error != NULL)
	{
		printf("Error: %s\n", error);
		exit(1);
	}

	// call a function on the plugin
	typedef void (*PLUGIN_FUNC)();
	PLUGIN_FUNC foo = (PLUGIN_FUNC)dlsym(lib, "foo");
	error = dlerror();
	if (error != NULL)
	{
		printf("Error: %s\n", error);
		exit(1);
	}
	foo();
}
