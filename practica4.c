#include <stdio.h>
//MPI
#include "mpi.h"

double proceso(double width1, double sum1,long RECTAS1) {
    
    double height,mid,area;
    double width = width1;
    double sum = sum1;
    long RECTAS = RECTAS1;
    for (long i = 0; i < RECTAS; i++) {
                mid = (i + 0.5) * width;
                height = 4.0 / (1.0 + mid * mid);
                sum += height;
            }
            area = width * sum;
            
    
    return area;
}

void main() {

    long RECTAS = 20000000;
    
            double sum = 0.0;
            double width = 1.0 / (double) RECTAS;
            double areaCalculada,total;
            int source;



            int my_rank, cnn_sz, n = 1024, local_n;


            MPI_Init(NULL,NULL);
            MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
            MPI_Comm_size(MPI_COMM_WORLD, &cnn_sz);
            
            

            areaCalculada = proceso(width,sum, RECTAS);
            if(my_rank != 0) {
            printf("Soy el pid %d \n",my_rank);
            MPI_Send(&areaCalculada, 1, MPI_DOUBLE,0, 0, MPI_COMM_WORLD);
            } else {
                printf("Soy el pid igual a cero %d \n",my_rank);
                total =areaCalculada;
                for(source = 1; source < cnn_sz; source++) {
                    MPI_Recv(&areaCalculada, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    
                    total=areaCalculada;
                }
            }
    
            if(my_rank == 0) {

                printf("Resultado = %f \n", total);

            }
            MPI_Finalize();
            
}

            

