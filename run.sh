#!/usr/bin/env bash
#SBATCH --partition=bench
#SBATCH --nodes 8
module load mpi/openmpi-x86_64

echo "2 Knoten 1 Rank"
mpirun -n 2 -N 1 ./pi.exe 1000064

echo "2 Knoten 2 Rank"
mpirun -n 4 -N 2 ./pi.exe 1000064

echo "2 Knoten 4 Rank"
mpirun -n 8 -N 4 ./pi.exe 1000064

echo "2 Knoten 8 Rank"
mpirun -n 16 -N 8 ./pi.exe 1000064

echo "4 Knoten 1 Rank"
mpirun -n 4 -N 1 ./pi.exe 1000064

echo "4 Knoten 2 Rank"
mpirun -n 8 -N 2 ./pi.exe 1000064

echo "4 Knoten 4 Rank"
mpirun -n 16 -N 4 ./pi.exe 1000064

echo "4 Knoten 8 Rank"
mpirun -n 32 -N 8 ./pi.exe 1000064

echo "8 Knoten 1 Rank"
mpirun -n 8 -N 1 ./pi.exe 1000064

echo "8 Knoten 2 Rank"
mpirun -n 16 -N 2 ./pi.exe 1000064

echo "8 Knoten 4 Rank"
mpirun -n 32 -N 4 ./pi.exe 1000064

echo "8 Knoten 8 Rank"
mpirun -n 64 -N 8 ./pi.exe 1000064
