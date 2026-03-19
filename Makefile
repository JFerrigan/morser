CC ?= cc
CFLAGS ?= -Wall -Wextra -O2
CPPFLAGS ?=
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man/man1
LICENSEDIR ?= $(PREFIX)/share/licenses/$(TARGET)
TARGET ?= morser
SRC := morser.c
MANPAGE := morser.1
VERSION ?= 0.1.0
LICENSE_FILE := LICENSE

CPPFLAGS += -DVERSION=\"$(VERSION)\"

.PHONY: all install uninstall clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/morser
	install -d $(DESTDIR)$(MANDIR)
	install -m 644 $(MANPAGE) $(DESTDIR)$(MANDIR)/$(MANPAGE)
	install -d $(DESTDIR)$(LICENSEDIR)
	install -m 644 $(LICENSE_FILE) $(DESTDIR)$(LICENSEDIR)/$(LICENSE_FILE)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/morser
	rm -f $(DESTDIR)$(MANDIR)/$(MANPAGE)
	rm -f $(DESTDIR)$(LICENSEDIR)/$(LICENSE_FILE)

clean:
	rm -f $(TARGET)
