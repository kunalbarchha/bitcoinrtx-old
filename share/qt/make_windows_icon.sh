#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/bitcoinrtx.png
ICON_DST=../../src/qt/res/icons/bitcoinrtx.ico
convert ${ICON_SRC} -resize 16x16 bitcoinrtx-16.png
convert ${ICON_SRC} -resize 32x32 bitcoinrtx-32.png
convert ${ICON_SRC} -resize 48x48 bitcoinrtx-48.png
convert bitcoinrtx-16.png bitcoinrtx-32.png bitcoinrtx-48.png ${ICON_DST}

