#!/bin/bash

if [ "$#" -lt 1 ] || [ "$#" -lt 2 -a "$#" -gt 0 -a $1 = "0" ] || [ "$#" -lt 4 -a "$#" -gt 0 -a $1 != "0" ]; then
    echo "Wrong number of parameters - in order to run the script, you need to pass the following arguments in this order:"
    printf "What scripts should be executed (0 - only notebooks, 1 - only python scripts, 2 - both)\n"
    printf "Path to the optics generator folder\n"
    printf "Path to the xml file (only in case of running python scripts)\nPath to the output directory where results of python scripts will be saved"
    printf " (only in case of running python scripts)"
    exit 2
fi

if [ $1 != "0" -a $1 != "1" -a $1 != "2" ]; then
  echo "Wrong execution mode (should be either 0, 1 or 2)"
  exit 2
fi

if [ $1 != "0" ]; then
  xml=$(realpath $3)
fi
optics_gen=$(realpath $2)

cd $optics_gen
if [ $? -ne 0 ]; then
      echo "Wrong optics generator path"
      exit 2
fi

export PYTHONPATH=$PYTHONPATH:`pwd`/src
export PATH=$PATH:`pwd`
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/root_libs
cd notebooks

if [ $1 != "1" ]; then
  for i in *.ipynb
  do
    runipy $i
    exit
  done
fi

cd $2

if [ $1 != "0" ]; then
  python3 ./src/output_generation/plots_errors.py $xml $4
  python3 ./src/output_generation/plots_optics.py $xml $4
  echo shit
fi
