#!/bin/bash
lcov -c -d out -o coverage.info
genhtml coverage.info -o coverage