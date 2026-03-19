# morser

A small command-line Morse code encoder and decoder written in C.

## Build

```sh
make
```

Run tests:

```sh
make test
```

Build a specific version string:

```sh
make VERSION=0.1.0
```

## Install

```sh
sudo make install
```

This installs:

- `morser` to `/usr/local/bin`
- `morser.1` to `/usr/local/share/man/man1`
- `LICENSE` to `/usr/local/share/licenses/morser`

Install without `sudo` under `~/.local`:

```sh
make install PREFIX="$HOME/.local"
```

Or use the helper script:

```sh
sh ./install.sh
```

By default, the helper installs the license to `~/.local/share/licenses/morser/LICENSE`.

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

Show version:

```sh
morser --version
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

## License

`morser` is licensed under the MIT License. See [`LICENSE`](LICENSE).

## Releases

The binary version comes from the `VERSION` variable in `Makefile`.
For a release, update it if needed, commit, then create an annotated tag:

```sh
git add -A
git commit -m "Release v0.1.0"
git tag -a v0.1.0 -m "Release v0.1.0"
git push origin main
git push origin v0.1.0
```
