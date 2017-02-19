bin_PROGRAMS = gameloop
 
gameloop_SOURCES = gameloop.c
gameloop_CFLAGS = $(SDL2_CFLAGS) $(GLIB_CFLAGS)  $(LIBSTU_CLAGS)
gameloop_LDFLAGS = -mconsole -mwindows
gameloop_LDADD = $(SDL2_LIBS) $(GLIB_LIBS) $(LIBSTU_LIBS) -lSDL2_image #-lwinmm 
