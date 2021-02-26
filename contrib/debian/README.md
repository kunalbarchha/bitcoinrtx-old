
Debian
====================
This directory contains files used to package bitcoinrtxd/bitcoinrtx-qt
for Debian-based Linux systems. If you compile bitcoinrtxd/bitcoinrtx-qt yourself, there are some useful files here.

## bitcoinrtx: URI support ##


bitcoinrtx-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcoinrtx-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcoinrtx-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoinrtx128.png` to `/usr/share/pixmaps`

bitcoinrtx-qt.protocol (KDE)

