#!/bin/bash
rm -rf html/
rm -rfv *.stackdump
find . -name *.gcda | xargs rm -fv
rm -rfv coverage/
rm -fv coverage.info