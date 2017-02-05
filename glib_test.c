#include <glib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	printf("GLib version: %d.%d.%d\n", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);
	return 0;
}
