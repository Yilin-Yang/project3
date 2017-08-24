#!/bin/bash
################################################################################
# BRIEF:	Installs dependencies for Project3.
# EFFECTS:	Installs the Eigen library, the Boost library, CMake, and
# 			CCMake.
################################################################################

INSTALLCMD="sudo apt-get install -y"

$INSTALLCMD libeigen3-dev
$INSTALLCMD libboost-test-dev
$INSTALLCMD cmake
$INSTALLCMD cmake-curses-gui
