#!/bin/bash

set -xe

CFLAGS="-std=c11 -o interactive interactive.c"

gcc $CFLAGS
