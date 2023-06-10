#!/bin/bash
echo "In bytes: "
du -b $@
echo "In Kilobytes or Megabytes: "
du -h $@
