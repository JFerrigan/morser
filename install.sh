#!/bin/sh
# SPDX-License-Identifier: MIT

set -eu

PREFIX=${PREFIX:-"$HOME/.local"}
BINDIR=${BINDIR:-"$PREFIX/bin"}
MANDIR=${MANDIR:-"$PREFIX/share/man/man1"}
LICENSEDIR=${LICENSEDIR:-"$PREFIX/share/licenses/morser"}

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

make -C "$script_dir"

install -d "$BINDIR"
install -m 755 "$script_dir/morser" "$BINDIR/morser"

install -d "$MANDIR"
install -m 644 "$script_dir/morser.1" "$MANDIR/morser.1"

install -d "$LICENSEDIR"
install -m 644 "$script_dir/LICENSE" "$LICENSEDIR/LICENSE"

printf 'Installed morser to %s\n' "$BINDIR/morser"
printf 'Installed man page to %s\n' "$MANDIR/morser.1"
printf 'Installed license to %s\n' "$LICENSEDIR/LICENSE"
printf 'Add %s to PATH if needed.\n' "$BINDIR"
printf 'Add %s to MANPATH if needed.\n' "${PREFIX}/share/man"
