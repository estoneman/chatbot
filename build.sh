#!/bin/bash

set -xe

CFLAGS="-std=c11 -o bot bot.c"

gcc $CFLAGS
