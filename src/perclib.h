//file header per le funzioni di "base" non inerenti al random walk
#ifndef perclib_H_
#define perclib_H_

#define PARS 3  //controllare e decidere numero di parametri da immettere
#define LEN 40



//-----------------------------------------------prototipi delle funzioni---------------------------------------------------//


void syntax(int, char**);

void check_array_int(int *);			//checks that array (type int) has been allocated

void check_array_double(double *);		//checks that array (type double) has been allocated

void clear_array_int(int *, int);		//clears array (type int)

void clear_array_double(double *, int);		//clears array (type double)




#endif

/*END perclib.h*/
