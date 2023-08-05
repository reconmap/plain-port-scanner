
**Plain Port Scanner** is a simple tool which scans a target host and reports a list of open and closed ports.

If you wan to build this software first launch ./configure and then a make install (with root privileges).

If you don't have root privileges, install the binaries on a differente folder: ./configure --prefix=<DEST_FOLDER> && make install

# Requirements

* autoconf
* make
* C17 compiler (GCC with GNU extensions)

## Build instructions

```sh
./autogen.sh
./configure
make
sudo make install
```
