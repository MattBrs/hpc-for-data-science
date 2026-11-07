#!/bin/bash

#PBS -l select=2:ncpus=2:mem=2gb
#PBS -l place=pack
#PBS -l walltime=0:00:30
#PBS -q shortCPUQ

set -e
cd "$PBS_O_WORKDIR"

module load MPICH/3.4.2-GCC-10.3.0

echo "Job: $PBS_JOBID"
echo "Allocated slots: "
cat "$PBS_NODEFILE"

mpiexec -n 4 home/matteo.brusarosco/mpi-wrapper.sh ./<program>
