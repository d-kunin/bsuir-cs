#!/bin/bash

echo "Files with single letter ext"
ls -f *.?

echo "Files ending with letter"
ls -f *[a-z]

echo "Files with space in name"
ls -f *\ *
