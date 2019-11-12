#!/bin/bash

if [ "$1" = "--make_parameterization" ] ; then
    ./src/models/make_parameterization.py $2 $3
elif [ "$1" = "--make_error_plots" ] ; then
    python3 ./src/output_generation/plots_errors.py $2 $3 $4 $5
elif [ "$1" = "--make_optical_functions_plot" ] ; then
    python3 ./src/output_generation/plots_optics.py $2 $3 $4 $5
fi
