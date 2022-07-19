#!/bin/sh

#SBATCH --job-name=mulitple_jobs

#SBATCH --ntasks=2
#SBATCH --output=mulitple_jobs_%j.log
#SBATCH --licenses=sps

####################################
module load gcc
MALLOC_ARENA_MAX=glibc.malloc.arena_max=0
make
./dist/prog 10 7 