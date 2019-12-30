# Information about software stack avaliable on lxplus
# http://lcginfo.cern.ch/
# Commands semantics:
# lcgenv stack_name platform package_name
# returns "export" commands which should be invoke to include package
# all of them are redirected to lcg.sh file, which should be executed before using
# of tools
# Before using lcgenv variable LCGENV_PATH should be set properly

export LCGENV_PATH=/cvmfs/sft.cern.ch/lcg/releases
lcgenv='/cvmfs/sft.cern.ch/lcg/releases/lcgenv/latest/lcgenv'
$lcgenv -p LCG_96python3 x86_64-centos7-gcc8-opt cpymad >> lcg.sh
$lcgenv -p LCG_96python3 x86_64-centos7-gcc8-opt jupyter >> lcg.sh
$lcgenv -p LCG_96python3 x86_64-centos7-gcc8-opt seaborn >> lcg.sh
$lcgenv -p LCG_96python3 x86_64-centos7-gcc8-opt ROOT >> lcg.sh