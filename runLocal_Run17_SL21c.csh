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
// kWrite
//root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("st_rp_18149028_raw_0000009.picoDst.root","st_rp_18149028_raw_0000009",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'

//root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("./picoLists/local_testList_SL21c.list","output_test",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'
//mode 0/3
root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("./picoLists/local_K0K0List_SL21c.list","st_exK0K0_1",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'
//root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("./picoLists/local_st_rpList_SL21c.list","st_rp",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'
// mode 1
//root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("st_exK0K0_1.picoDst.root","st_exK0K0_1",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'
//mode 2
//root4star -l -b -q './StRoot/macros/runPicoLambdaAnaMaker.C("./picoLists/local_K0K0List_SL21c.list,"st_exK0K0_1",'$makerMode',"./picoLists/BadRunList_MB.list","picoHFtree","~/pwd/pico/",0,"SL21c",0)'
