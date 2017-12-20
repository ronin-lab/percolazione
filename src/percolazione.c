#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



//check variables and reorder

int L , n , size;
double p_min, p_max , dp,p;
char nomefile[255];
int *reticolo = NULL;

int main(int argc, char** argv){
	int count1,i,sim;
	int nIter,n_changes, isPerc, numHoles;
	double state;
	unsigned long long int sumClustersSquare;
	int seed;
	int maxClusterSize, numCluster;
	int *clusterSize = NULL;
	FILE *urandom =NULL;
	FILE *fp=NULL;

  syntax(argc, argv); //nb controlla il define per il numero di parametri (A in perclib.h)

  //inserire cosa passare da riga di comando
  //inserire funzione che controlla che l'input vada bene


  //inizializza seed da /dev/urandom

  urandom = fopen("/dev/urandom","r");
  //inserire funzione check_file che fa questo check
  if(urandom == NULL){
    fprintf(stderr,"Impossibile leggere il seed...\n");
    return(ERROR);
  }
  fread(&seed, sizeof(int),1,urandom);
  srand48(seed);
  fclose(urandom);

  //operazioni preliminari

  	//dimensione del reticolo
  	size = L*L;
  	//creazione reticolo e sacchetto della tombola
  	reticolo = (int *)calloc(size, sizeof(int));
  	clusterSize = (int *)calloc(size, sizeof(int));

    //c'e' la funzione check_array_int per questo
  	if( (clusterSize == NULL) || (reticolo == NULL)){
  		fprintf(stderr,"Impossibile allocare la memoria necessaria, termino ora\n");
  		return(ERROR);
  	}
    //usare funzione check_file
  	fp = fopen(nomefile,"w");
  	if(fp == NULL){
  		fprintf(stderr,"Impossibile allocare la memoria necessaria, termino ora\n");
  		return(ERROR);
  	}

    //CORE
    	p = p_min;
    	while(p <= p_max){ //ciclo sulle probabilità

        //vedere se ha senso fare tutto su un unico file, soprattutto su gnuplot
    			fprintf(fp,"#(1)Simulazione\t(2)N Buchi\t(3)Percola?\t(4)SumCluster²\t(5)numClusters\t(6)maxClusterSize\t(7)nIter\t(8)Taglia\t(9)Probabilità\n");
    		for( sim = 1; sim <= n ; sim++){ //ciclo sulle simulazione

          //non serve troppo scrivere su output (e soprattutto su stderr non ha senso)
    			fprintf(stderr,"\rSimulo la traiettoria: %d\tprobabilità: %lf",sim,p);
    			fflush(stderr);

    			//preparazione del reticolo e generazione dei buchi come variabile binomiale
          //fare una funzione genera_buchi per questo for
          numHoles = 0;
          for(i = 0 ; i < size ; i++){

    				state = drand48();

    				if(state <= p){
    					reticolo[i]=i;
    					numHoles++;
    				}else{
    					reticolo[i]=-1;
    				}
    			}

    			//etichettamente
          //funzione labeling per questa roba (tutto il do{}while)
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

    			//Controllo della percolazione
          //altra funzione check_perc
    			isPerc = 0;
    			for(i = L*(L-1) ; i < size ; i++){
    				if( (reticolo[i] < L) && (reticolo[i]!=-1) ){
    					isPerc = 1;
    				}
    			}

    			//calcolo della dimensione del cluster
          //altra funzione check_cluster_size o simile
    			for(i = 0; i < size ; i++){
    				if(reticolo[i] >=0){
    					clusterSize[reticolo[i]]++;
    				}
    			}

    			//conto di quanti cluster sono presenti e dimensione del cluster più grande
    			maxClusterSize = -1;
    			numCluster = 0;
    			for(i=0; i < size ; i++){
    				if(clusterSize[i] > maxClusterSize){
    					maxClusterSize = clusterSize[i];
    				}

    				if(clusterSize[i] != 0 ){
    					numCluster++;
    				}
    			}

    			//grandezza media dei cluster
    			sumClustersSquare = 0;
    			for( i = 0 ; i < size; i++){
    				sumClustersSquare += clusterSize[i] * clusterSize[i];
    				clusterSize[i]=0;
    			}
    			fprintf(fp,"%d\t\t%d\t\t%d\t\t%llu\t\t%d\t\t%d\t\t\t%d\t\t%d\t\t%lf\n",sim, numHoles , isPerc , sumClustersSquare , numCluster , maxClusterSize , nIter , size, p);
    		}
    	fprintf(fp,"\n");
    	p += dp;
    	}
    	fprintf(stderr,"\n");
    	fclose(fp);

    	return(SUCCESS);
    }
