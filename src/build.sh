#!/bin/bash
#xmessage 'blah'
cd ~/Projekte/oh/openhanse/src
#pwd > /tmp/xmessagepwd
#xmessage -file /tmp/xmessagepwd
#rm /tmp/xmessagepwd

#qmake src.pro > /tmp/oh.err

rm /tmp/oh.err
killall OpenHanse

qmake > /tmp/oh.err && make 2>> /tmp/oh.err >> /tmp/oh.err
#&& make 2>&1 >> /tmp/oh.err
# make 2>&1 >> /tmp/oh.err

#cat make.err qmake.err > /tmp/oh.err


if [ "$?" = 0 ]
then
cp -rvu maps/ ../bin/
xmessage -buttons Exit:0,StartOH:1 -center -file /tmp/oh.err 
if [ "$?" = 1 ]
then
cd ../bin/
echo "\n\nBegin log:\n" >> debugging.log
date >> debugging.log
./OpenHanse 2>> debugging.log >> debugging.log
fi
else
xmessage -buttons Exit:0 -center -file /tmp/oh.err 

fi