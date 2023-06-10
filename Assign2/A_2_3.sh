#!/bin/bash
echo "Proceccessor Information: "
grep "vendor_id" /proc/cpuinfo | uniq
grep "model name" /proc/cpuinfo | uniq
grep "cpu MHz" /proc/cpuinfo | uniq
grep "cache size" /proc/cpuinfo | uniq
