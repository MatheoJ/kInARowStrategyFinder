#!/bin/sh

#SBATCH --job-name=mulitple_jobs

#SBATCH --ntasks=2
#SBATCH --output=mulitple_jobs_%j.log
#SBATCH --licenses=sps

####################################
module load gcc
make
gdb --batch --command=test.gdb --args ./dist/prog 7 9 8 > out.txt
