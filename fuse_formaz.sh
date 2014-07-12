#!/bin/sh

dd if=/dev/zero of=$1 count=$2 bs=1M
./szd mnt r $1 2000 2000 b b
