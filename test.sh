#!/usr/bin/expect --

USER=$1
PW=$2

set timeout 1
spawn sudo -u $USER vncpasswd
expect "Password:"
send "$PW\r"
expect "Verify:"
send "$PW\r"
interact
