#!/usr/bin/env sh

######################################################################
# @author      : kistenklaus (karlsasssie@gmail.com)
# @file        : run
# @created     : Sonntag Jun 23, 2024 14:24:04 CEST
#
# @description : 
######################################################################

canzero gen power_board12 src/canzero
cmake -Bbuild
make -C build
alacritty -e ./build/power-board12&



