#!/bin/bash
echo "Welcome to KDB+ on Docker"
echo "alias q='QHOME=~/q rlwrap -r ~/q/l64/q'" >> ~/.bash_aliases
source ~/.bashrc


echo $#

if [ "$#" -eq 0 ]; then
    exec "rlwrap" -r "$QBIN" "/root/qscripts/example.q" -p 1234
else
    # Run the provided command
    exec "$@"
fi
exec "$@"


