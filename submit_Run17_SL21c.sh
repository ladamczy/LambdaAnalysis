#!/bin/bash

#max. line is 22173 in file list SL21d
#max. line is 444695 in file list SL20d
#to test submit

sed -n '1,50000 p' ./picoLists/picoList_Run17_SL21c.list > picoList_submit.list

#sort ./picoLists/sublists/picoList_test.list > ./picoLists/sublists/picoList_test_09.list

#rm ./picoLists/sublists/picoList_test.list


path=`pwd -P`
path=$( echo $path | sed 's|//|/|g' )


echo executing submitPicoHFMaker.csh f0r picoList_test.list inside $path

starver SL21c

#re-compile under correct library
./compile_SL21c.csh

#for list generated directly by sed ad the top of this macro
csh starSubmit/submitPicoHFMaker_SL21c.csh $path picoList_submit.list

#for pre-generated sublists
#csh starSubmit/submitPicoHFMaker.csh $path ./picoLists/sublists/picoList_test_08.list
