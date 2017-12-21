#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "perclib.h"



void syntax(int argc, char* argv[]){


	if(argc != A){


		fprintf(stderr, "ERROR! Syntax %s <lato> <probabilita' minima di avere un buco> <probabilita' massima> <incremento di probabilita'> <numero simulazioni>\n", argv[0]);


		exit(EXIT_FAILURE);


	}


}


void check_array_int(int *array){


	if(array == NULL){


		fprintf(stderr, "Error! Dynamic memory allocation failed.\n");

		exit(EXIT_FAILURE);


	}


	return;


}

void check_array_double(double *array){


	if(array == NULL){


		fprintf(stderr, "Error! Dynamic memory allocation failed.\n");

		exit(EXIT_FAILURE);


	}


	return;


}

void check_prob(double p){

	if((p < 0) || (p > 1)){

		fprintf(stderr, "ERRORE! Valore errato di probabilita'.\n");

		exit(EXIT_FAILURE);

	}

}



void check_file(FILE *fp){

	if(fp == NULL){

		fprintf(stderr, "ERROR! File reading failed.\n");

		exit(EXIT_FAILURE);

	}

}


int generate_holes(int *reticolo, int size, double p){

	int numHoles, i;
	numHoles = 0;
	double state;

	for(i = 0 ; i < size ; i++){

		state = drand48();

		if(state <= p){
			reticolo[i]=i;
			numHoles++;
		}else{
			reticolo[i]=-1;
		}
	}
	return numHoles;
}


int labeling(int *reticolo, int size, int L){

	int nIter, i, n_changes;

	nIter=0;

	do{
		n_changes = 0;
		for(i = 0; i < size ; i++){
			if(reticolo[i] > 0){
				if((i+1<size) && (reticolo[i+1]>=0) && (reticolo[i+1]!=reticolo[i]) ){ //controllo del vicino di destra
					n_changes++;
					if(reticolo[i] > reticolo[i+1]){
						reticolo[i]=reticolo[i+1];
					}else{
						reticolo[i+1] = reticolo[i];
					}
				}

				if( ( i+L < size) && ( reticolo[i+L] >= 0 ) && ( reticolo[i+L] != reticolo[i] ) ){ //controllo del vicino di sopra
					n_changes++;
					if(reticolo[i] > reticolo[i+L]){
						reticolo[i]=reticolo[i+L];
					}else{
						reticolo[i+L] = reticolo[i];
					}
				}
			}
		}
		nIter++;
	}while(n_changes); //controlla le etichette finchè non ci sono più cambiamenti da fare

	return nIter;

}

int check_perc(int *reticolo, int size, int L){

	int isPerc, i;

	isPerc = 0;

	for(i = L*(L-1) ; i < size ; i++){

		if( (reticolo[i] < L) && (reticolo[i]!=-1) ){

			isPerc = 1;

		}

	}

	return isPerc;
}


void cluster_size(int *reticolo, int *clusterSize, int size){

	int i;

	for(i = 0; i < size ; i++){

		if(reticolo[i] >=0){

			clusterSize[reticolo[i]]++;

		}

	}

}



int cluster_max(int *clusterSize, int size){

	int maxClusterSize, i;

	maxClusterSize = -1;


	for(i=0; i < size ; i++){

		if(clusterSize[i] > maxClusterSize){

			maxClusterSize = clusterSize[i];

		}

	}

	return maxClusterSize;
}


int cluster_count(int *clusterSize, int size){

	int numCluster, i;

	numCluster = 0;

	for(i = 0; i<size; i++){

		if(clusterSize[i] != 0 ){

			numCluster++;

		}
	}
	return numCluster;
}


unsigned long long int cluster_square(int *clusterSize, int size){

	unsigned long long int sumClustersSquare;

	int i;

	sumClustersSquare = 0;
	for( i = 0 ; i < size; i++){
		sumClustersSquare += clusterSize[i] * clusterSize[i];
		clusterSize[i]=0;
	}

	return sumClustersSquare;
}
