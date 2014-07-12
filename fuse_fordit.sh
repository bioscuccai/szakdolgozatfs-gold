#!/bin/sh

g++ `pkg-config fuse --cflags --libs` szakdolgozatfs*.cpp -o szd -I/usr/include/qt4/QtCore -I/usr/include/qt4 -lQtCore