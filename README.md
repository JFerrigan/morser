# morser

A small command-line Morse code encoder and decoder written in C.

## Build

```sh
make
```

## Install

```sh
sudo make install
```

This installs:

- `morser` to `/usr/local/bin`
- `morser.1` to `/usr/local/share/man/man1`

Install without `sudo` under `~/.local`:

```sh
make install PREFIX="$HOME/.local"
```

Or use the helper script:

```sh
sh ./install.sh
```

If needed, add these to your shell config:

```sh
export PATH="$HOME/.local/bin:$PATH"
export MANPATH="$HOME/.local/share/man:$MANPATH"
```

## Usage

Encode text:

```sh
morser "SOS 123"
```

Decode Morse:

```sh
morser --decode "... --- ... / .---- ..--- ...--"
```

Show help:

```sh
morser --help
```

Round-trip encode and decode in one line:

```sh
morser -d "$(morser 'SOS 123')"
```

## Man Page

After installation:

```sh
man morser
```

## Uninstall

```sh
sudo make uninstall
```

For a user-local install:

```sh
make uninstall PREFIX="$HOME/.local"
```
