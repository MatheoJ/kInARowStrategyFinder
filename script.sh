#!/bin/sh

#SBATCH --job-name=mulitple_jobs

#SBATCH --ntasks=2
#SBATCH --output=mulitple_jobs_%j.log
#SBATCH --licenses=sps

####################################
module load gcc
make
valgrind --tool=massif ./dist/prog 10 7 32 