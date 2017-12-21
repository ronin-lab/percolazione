//file header per le funzioni di "base" non inerenti al random walk
#ifndef perclib_H_
#define perclib_H_

#define A 6  //controllare e decidere numero di parametri da immettere
#define LEN 40



//-----------------------------------------------prototipi delle funzioni---------------------------------------------------//


void syntax(int, char**);

void check_array_int(int *);			//checks that array (type int) has been allocated

void check_array_double(double *);		//checks that array (type double) has been allocated

void check_file(FILE *);  //checks file is not NULL

void check_prob(double);  //controlla che la probabilita' immessa sia accettabile

int generate_holes(int *, int, double);  //genera reticolo

int labeling(int *, int, int); //crea labels

int check_perc(int *, int, int);   //controlla che la configurazione percoli

void cluster_size(int *, int *, int);   //dimensione dei cluster

int cluster_count(int *, int);   		//conto di quanti cluster sono presenti

int cluster_max(int *, int);      //ottiene la dimensione massima dei cluster

unsigned long long int cluster_square(int *, int);    			//grandezza media dei cluster


#endif

/*END perclib.h*/
