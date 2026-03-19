#!/bin/sh

set -eu

PREFIX=${PREFIX:-"$HOME/.local"}
BINDIR=${BINDIR:-"$PREFIX/bin"}
MANDIR=${MANDIR:-"$PREFIX/share/man/man1"}

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

make -C "$script_dir"

install -d "$BINDIR"
install -m 755 "$script_dir/morse" "$BINDIR/morse"

install -d "$MANDIR"
install -m 644 "$script_dir/morse.1" "$MANDIR/morse.1"

printf 'Installed morse to %s\n' "$BINDIR/morse"
printf 'Installed man page to %s\n' "$MANDIR/morse.1"
printf 'Add %s to PATH if needed.\n' "$BINDIR"
printf 'Add %s to MANPATH if needed.\n' "${PREFIX}/share/man"
