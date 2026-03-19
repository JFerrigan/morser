CC ?= cc
CFLAGS ?= -Wall -Wextra -O2
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man/man1
TARGET ?= morser
SRC := morser.c
MANPAGE := morser.1

.PHONY: all install uninstall clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/morser
	install -d $(DESTDIR)$(MANDIR)
	install -m 644 $(MANPAGE) $(DESTDIR)$(MANDIR)/$(MANPAGE)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/morser
	rm -f $(DESTDIR)$(MANDIR)/$(MANPAGE)

clean:
	rm -f $(TARGET)
