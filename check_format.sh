#!/bin/sh
file_to_check=$1
#format_cmd="clang-format -fallback-style=/usr/local/etc/.clang-format"
format_cmd="clang-format"
$format_cmd $file_to_check | diff - $file_to_check
