//build and run:
//mpicc -Wall -O3 pi.cc -o pi.exe && mpirun -np 4 ./pi 1000000

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "utils.h"

 

int main(int argc, char **argv)
{
 
  time_t now;
  time_t not_now;
  time_t cycles;
  rdtsc(now);
  int num_iter = 0;
  if (argc == 2)
  {
    num_iter = atoi(argv[1]);
    if (num_iter % 2)
    {
      printf("only even numbers allowed!\n");
    }
  }
  else
  {
    printf("parameter error, please run: %s #iterations\n", argv[0]);
    exit(0);
  }
  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);
  
  int batch_size = num_iter/world_size;
  
  if (batch_size % 2)
  {
    printf("only even batch size allowed!\n");
    exit(0);
  }
  
  double pi_part = 0;
  double div = (2*world_rank*batch_size) + 1; //beginnt mit +
  
//  printf("processor %s, rank %d out of %d processors, start div: %f, batch size: %d\n", processor_name, world_rank, world_size, div, batch_size);
  
  //Leibniz-Reihe
  for(int i = 0; i < (batch_size/2); i++)
  {
    //printf("#%d: div: %lf\n", world_rank, div);
    pi_part += 1.0/div;
    div+=2;
    //printf("#%d: div: %lf\n", world_rank, div);
    pi_part -= 1.0/div;
    div+=2;
  }
  
  MPI_Status status;
  
  if(world_rank == 0)
  {
    double pi_recv[world_size-1];
    double pi_total = pi_part;
    for (int i = 0; i<world_size-1; i++)
    {
      MPI_Recv(&pi_recv[i], 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
      pi_total += pi_recv[i];
    }
    pi_total *= 4.0;
    printf("pi_total: %.32lf\n", pi_total);
    double pi_diff = M_PI - pi_total;
    printf("pi_diff: %.32lf\n", pi_diff);
  }
  else
  {
    MPI_Send(&pi_part, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }
  
  //printf("%.32lf\n", pi_part);
  
  MPI_Finalize();
 
rdtsc(not_now);
cycles =+ not_now - now;
printf( "Cycles pro rank = %ld\n", cycles);  
   return 0;
}

