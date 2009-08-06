#! /bin/bash
cd ../bin/
rm -rf -v maps/
cd ../src/
# mkdir bin/
# cd src
cp -r -v maps/ ../bin/maps/
make
