#!/bin/bash
home_dir="$HOME"
os_type=`uname -s`
os_version=`grep -w "^VERSION_ID" /etc/os-release | awk -F '"' '{print $2}'`
os_release=`grep -w "^ID" /etc/os-release | awk -F '=' '{print $2}'`
kernel=`uname -r`
curr_path="$PATH"
echo "Home Direstory: $home_dir"
echo "OS type: $os_type"
echo "OS version: $os_version"
echo "OS release: $os_release"
echo "Kernel Version: $kernel"
echo "Current path: $curr_path"
