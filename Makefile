VERSION = 0.5
CC = gcc
CFLAGS = -fPIC -Wall
LIBS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0 xcb`
OBJPATH = ./build
SRCPATH = ./src
TARGET = olmos
LIBTARGET = libolmos.so
SOURCES = ol_string.c ol_regex.c ol_desktop.c ol_module.c ol_strv_builder.c ol_window.c
HFILES = $(addprefix ${SRCPATH}/,${SOURCES:.c=.h})
OBJECTS = ${SOURCES:.c=.o}
OBJFILES = $(addprefix ${OBJPATH}/,${OBJECTS})

.SILENT:
.PHONY: clean prebuild

install: ${OBJPATH}/${LIBTARGET} ${HFILES}
	cp -v $< /usr/lib
	mkdir -p /usr/include/${TARGET}
	cp -v ${HFILES} /usr/include/${TARGET}

uninstall:
	rm -fv /usr/lib/${LIBTARGET}
	rm -frv /usr/include/${TARGET}

build: prebuild ${OBJECTS}
	@echo "Archiving: ${OBJPATH}/${LIBTARGET}"
	${CC} -shared -o ${OBJPATH}/${LIBTARGET} ${OBJFILES}
#	ar rcs ${OBJPATH}/${LIBTARGET} ${OBJFILES}

%.o: ${SRCPATH}/%.c
	@echo "Compiling: $@"
	${CC} ${CFLAGS} -o ${OBJPATH}/$@ -c $< ${LIBS}

install2: ${OBJPATH}/${LIBTARGET}
	rm -f ${HOME}/Dev/DE/libolmosui/lib/${LIBTARGET}
	cp $^ ${HOME}/Dev/DE/libolmosui/lib

showlib:
	ar -t ${OBJPATH}/${LIBTARGET}

prebuild:
	mkdir -p ${OBJPATH}

clean:
	rm -frv ${OBJPATH}
