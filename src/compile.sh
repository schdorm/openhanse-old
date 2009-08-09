#! /bin/bash
echo "*****************************"
echo "Begin to compile OpenHanse..."
echo "*****************************"
echo

#echo "Configuring ..."
#[ -d $HOME/.OpenHanse ] || mkdir $HOME/.OpenHanse 
#if [ -d ../bin/ ];
#then
#[ -d ../bin/maps/ ] && rm -r ../bin/maps/
#else
#mkdir ../bin/
#fi
#cp -r maps/ ../bin/maps
#echo "Done"
#echo

#echo "Creating Config file ..."
#back=$(pwd)
#cd ../bin/
#pwd > $HOME/.OpenHanse/dir.ohc
#cd "$back"
#echo "Done"

echo "make clean"
make clean
rm Makefile
echo "Done"

echo "run qmake"
qmake src.pro
echo "Done"

echo "Make"
make 2> ../bin/error.log
echo "Done"

sh update.sh

clear
echo "Errors while make:"
cat ../bin/error.log

