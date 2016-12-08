#!/bin/sh

expect -c "
set timeout 1
spawn sudo -u $1 vncpasswd
expect \"Password:\"
send \"$2\r\"
expect \"Verify:\"
send \"$2\r\"
interact
"
