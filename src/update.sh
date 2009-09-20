#! /bin/bash
#cd ../bin/
#rm -rf -v maps/
#cd ../src/
# mkdir bin/
# cd src
cp -rvu maps/ ../bin/
make
echo "Updating Translations:"
lupdate src.pro
echo "Updating Translations finished"
