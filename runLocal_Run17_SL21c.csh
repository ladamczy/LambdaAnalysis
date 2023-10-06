#!/bin/tcsh

#starver SL21d
starver SL21c

# -- set maker mode
#    0 - kAnalyze, 
#    1 - kWrite
#    2 - kRead
#    3 - kQA
set makerMode=0

./compile_SL21c.csh

root4star -l -b -q './StRoot/macros/loadSharedHFLibraries.C'
root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("./picoLists/local_st_rpList_SL21c.list","st_rp",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'
