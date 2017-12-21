#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "perclib.h"


int main(int argc, char** argv){

	int L, Nsims, size;
	double p_min, p_max , dp, p;

	char filename[LEN];
	int *reticolo;
	int sim;
	int nIter, isPerc, numHoles;


	int seed;
	int maxClusterSize, numCluster;
	unsigned long long int sumClustersSquare;
	int *clusterSize;
	FILE *seedfile;
	FILE *fp;

  syntax(argc, argv); //nb controlla il define per il numero di parametri (A in perclib.h)


	//assegnazione delle variabili passate da riga di comando e controllo
	L = atoi(argv[1]);

	p_min = atof(argv[2]);

	check_prob(p_min);


	p_max = atof(argv[3]);

	check_prob(p_max);


	dp = atof(argv[4]);

	check_prob(dp);


	Nsims = atoi(argv[5]);




  //inizializza seed da /dev/urandom

  seedfile = fopen("/dev/urandom","r");

	check_file(seedfile);

  fread(&seed, sizeof(int), 1, seedfile);

  srand48(seed);

  fclose(seedfile);




  //operazioni preliminari

  	//dimensione del reticolo
  	size = L*L;

  	//creazione reticolo e array per cluster
  	reticolo = (int *)calloc(size, sizeof(int));

  	clusterSize = (int *)calloc(size, sizeof(int));


		check_array_int(reticolo);

		check_array_int(clusterSize);


		sprintf(filename, "percolazione_%d_%.3lf_%.3lf_%d.dat", L, p_min, p_max, Nsims);

  	fp = fopen(filename,"w");

		check_file(fp);



    //begin percolation


    	p = p_min;

    	while(p <= p_max){ //ciclo sulle probabilità


    		fprintf(fp,"#N Simulation\tN Holes\tPercolates?\tSum cluster square\tN Clusters\tMaximum cluster size\tN iteration\tSize\tProbability\n");

    		for( sim = 0; sim < Nsims ; sim++){ //ciclo sulle simulazioni


    			printf("\rSimulo la traiettoria: %d\tprobabilità: %lf", sim, p);



					//genero reticolo e buchi
					numHoles = generate_holes(reticolo, size, p);

					//label del reticolo
					nIter = labeling(reticolo, size, L);

					//controlla se la configurazione percola (ie sull'ultima riga)
					isPerc = check_perc(reticolo, size, L);

					//misura la grandezza dei cluster nei reticoli
					cluster_size(reticolo, clusterSize, size);

					//conta il numero di cluster
  				numCluster = cluster_count(clusterSize, size);

					//trova la dimensione massima dei cluster
					maxClusterSize = cluster_max(clusterSize, size);

					//numero cluster quadrato medio
					sumClustersSquare = cluster_square(clusterSize, size);


					fprintf(fp,"%d\t\t%d\t\t%d\t\t%llu\t\t%d\t\t%d\t\t\t%d\t\t%d\t\t%lf\n",sim, numHoles , isPerc , sumClustersSquare , numCluster , maxClusterSize , nIter , size, p);

				}

    	fprintf(fp,"\n");

			//aumento la probabilita'
    	p += dp;

    	}

    	fprintf(stderr,"\n");
    	fclose(fp);

    	return(0);
    }
