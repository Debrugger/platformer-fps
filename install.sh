#!/bin/bash 
# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
CFG_NAME=".platformer-fps"

echo "Program is located in $SCRIPTPATH"
#echo "[app info]" > $HOME/$CFG_NAME
echo "location=$SCRIPTPATH" > $HOME/$CFG_NAME
