/***************************************************************************************************************************
* University/Faculty	: National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor	: Numerical Linear Algebra - Tzaferis Filippos
* File name				: ask3_CG.cpp
* Name/Surname			: Nikolaos Mpegetis
* A.M					: 1115200700281
****************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>


int menu();
double ** userInput_A(int*);
double * userInput_X(int);

int list_specificMatrices();
double ** PascalMatrix_8X8(int*, double**);
double ** PascalMatrix_NXN(int*, double**);
double ** Matrix_NXN(int*, double**);

double ** randomInput_A(int*);
double * randomInput_X(int);

double ** fileInput_Axb(int*, double**);

void CG(double**, double*, int);

double ** allocateMatrix(int, int);
double sign();
double factorial(int);
void CG_Method(double **, double **, int, int, int *);



//srand(time(NULL));

int main(int argc, char* argv[]){
//main of ask3_CG.cpp

	int back2menu, n;
	double **A, *X;

	printf("\nLINEAR SYSTEM RESOLUTION OF Ax = b SYSTEMS USING CG METHOD\n");

	while(1){

		back2menu = 0;

		switch(menu()){
			case 1:	A = userInput_A(&n);
					X = userInput_X(n);
					break;

			case 2: switch(list_specificMatrices()){
						case 1:	A = PascalMatrix_8X8(&n, &X);
								break;
						case 2:	A = PascalMatrix_NXN(&n, &X);
								break;
						case 3:	A = Matrix_NXN(&n, &X);
								break;
						case 4: back2menu = 1;
								break;
						default:break;
					}
					break;

			case 3: A = randomInput_A(&n);
					X = randomInput_X(n);
					break;

			case 4:	A = fileInput_Axb(&n, &X);
					break;

			case 5: printf ("\n\n\tHOPE THAT YOU ENJOYED USING MY PROGRAM FOR FINDING LINEAR SYSTEM SOLUTIONS \
					\n\tFOR SYSTEMS OF TYPE Ax = b USING THE CG METHOD. \
					\n\n\tREGARDS NIKOLAOS BEGETIS UNDERGRADUATE STUDENT OF DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS, UNIVERSITY OF ATHENS \
					\n\n\t2011-2012\n");
					return 0;

			default:break;
		}
	if(back2menu!=1)
		CG(A, X, n);
	}
}


/**
*		functions used in main ordered in sequence of their appearence
*/


int menu(){
//main menu

	int menuSelection;
	do{
		printf ("\n\nMAIN MENU \
		\nSwitch your method of giving a system: \
		\n\t1. User Input: you are about to insert the A matrix and the b vector directly from keyboard \
		\n\t2. Use specific matrices: you are about to switch from a list of given matrices \
		\n\t3. Use ramdom matrices: you are about to select only the size of the matrix you want and the matrix will be generated randomly \
		\n\t4. File input: you are about to give a text file with your matrices in it. The file name must have the name:'ask3_CG.txt' \
		\n\n\t5. Select if you want to quit.\n");
		printf("INPUT: ");
		scanf("%d", &menuSelection);
	}while((menuSelection<1)||(menuSelection>5));
	return menuSelection;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** userInput_A(int *n){
//data of matrix A and vector b are inserted by the user

	double **A;
    int i,j;

    printf("Give matrix[NXN] dimension N : ");
    scanf("%d",n);

    A = allocateMatrix(*n, *n+1);		//the one more column represents the b vector. this allowance has effect in the whole written program

    printf("\nInsert A matrix data below:\n");
    for(i=0 ; i<*n ; i++){
        for(j=0 ; j<*n ; j++){
			printf("A[%d][%d] = ", i, j);
			scanf ("%lf", &A[i][j]);
        }
    }

	printf("\nGive vector b data below:\n");
	for (i=0 ; i<*n ; i++){
		printf("b[%d] = ", i);
		scanf ("%lf", &A[i][*n]);
	}
    return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double * userInput_X(int n){
//data of matrix X are inserted by the user

	double *X;
	int i;

	X = (double*)malloc(n*sizeof(double));

	printf("\nGive vector X data below (e.g (1,1,1,1,1)^T for a 5X5 matrix) :\n");
	for (i=0 ; i<n ; i++){
		printf("X[%d] = ", i);
		scanf("%lf", &X[i]);
	}
	return X;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int list_specificMatrices(){
//menu for the 2nd selection(specific matrices) of the main manu

	int matrix_no;
	do{
		printf("\n\nSpecific matrices LIST \
		\nSwitch the specific matrix to solve a linear system as given from exercise ask3_CG: \
		\n\t1. Pascal Matrix of dimensions 8X8 (adjustment 2.a.4 from exercise 1) \
		\n\t2. Pascal Matrix of dimensions NXN, where N given by you with values 100,500,1000 and system solution: x=(1,1,...,1,1)^T(adjustment 2.a.5 from exercise 1) \
		\n\t3. Matrix of dimensions NXN, where N given by you with values 100,500,1000 and system solution: x=(1,1,...,1,1)^T (adjustment 2.a.6 from exercise 1) \
		\n\n\t4. Select if you want to return to MAIN MENU.\n");
		printf("INPUT : ");
		scanf("%d", &matrix_no);
	}while((matrix_no<1)||(matrix_no>4));
	return matrix_no;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** PascalMatrix_8X8(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.4 from exercise 1)

    double **A;

	*n=8;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=1;	A[0][1]=1;	A[0][2]=1;	A[0][3]=1;	A[0][4]=1;	A[0][5]=1;	A[0][6]=1;	A[0][7]=1;	A[0][8]=8;
    A[1][0]=1;	A[1][1]=2;	A[1][2]=3;	A[1][3]=4;	A[1][4]=5;	A[1][5]=6;	A[1][6]=7;	A[1][7]=8;	A[1][8]=36;
    A[2][0]=1;	A[2][1]=3;	A[2][2]=6;	A[2][3]=10;	A[2][4]=15;	A[2][5]=21;	A[2][6]=28;	A[2][7]=36;	A[2][8]=120;
    A[3][0]=1;	A[3][1]=4;	A[3][2]=10;	A[3][3]=20;	A[3][4]=35;	A[3][5]=56;	A[3][6]=84;	A[3][7]=120;A[3][8]=330;
    A[4][0]=1;	A[4][1]=5;	A[4][2]=15;	A[4][3]=35;	A[4][4]=70;	A[4][5]=126;A[4][6]=210;A[4][7]=330;A[4][8]=792;
    A[5][0]=1;	A[5][1]=6;	A[5][2]=21;	A[5][3]=56;	A[5][4]=126;A[5][5]=252;A[5][6]=462;A[5][7]=792;A[5][8]=1716;
    A[6][0]=1;	A[6][1]=7;	A[6][2]=28;	A[6][3]=84;	A[6][4]=210;A[6][5]=462;A[6][6]=924;A[6][7]=1716;A[6][8]=3432;
    A[7][0]=1;	A[7][1]=8;	A[7][2]=36;	A[7][3]=120;A[7][4]=330;A[7][5]=792;A[7][6]=1716;A[7][7]=3432;A[7][8]=6435;

    *X = (double*)malloc(*n*sizeof(double));

    (*X)[0]=1;	(*X)[1]=1;	(*X)[2]=1;	(*X)[3]=1;	(*X)[4]=1;	(*X)[5]=1;	(*X)[6]=1;	(*X)[7]=1;

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** PascalMatrix_NXN(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.5 from exercise 1)

	double **A;
	int i, j;

	printf("Give Pascal matrix[NXN] dimension N (e.g. 100,500,1000) : ");
	scanf("%d",n);


	*X = (double*)malloc(*n*sizeof(double));

	A = allocateMatrix(*n,*n+1);			//the one more column corresponds to the b vector

	//values for A Pascal Matrix
	for(i=1 ; i<=*n ; i++)					//begins with 1 to n+1 to avoid problems of floating exception
		for(j=1 ; j<=*n ; j++)
			A[i-1][j-1]= (factorial(i+j-2))/(factorial(i-1)*factorial(j-1));			//formula as given

	//values for X
	for(i=0 ; i<*n ; i++)
		(*X)[i]=1;

	//b computation
	for(i=0 ; i<*n ; i++){
		A[i][*n] = 0;					//initializes into zero all the values of b vector
		for(j=0 ; j<*n ; j++)
			A[i][*n] += A[i][j]*((*X)[j]);
	}
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** Matrix_NXN(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.6 from exercise 1)

	double **A;
	int i, j;

	printf("\nThe specific symmetric and positively defined matrix is designed with the following formula: \
			\n\tif the elements i,j of the matrix are on the diagonial then A[i][j] = N , N is the size of the matrix \
			\n\telse A[i][j] = 1/(i+j-1) \
			\n This pattern was given from the Cholesky method solvable matrices in adjustment 2.a.6 from exercise 1\n\n");

	printf("Give matrix[NXN] dimension N(e.g. 100,500,1000) : ");
	scanf("%d",n);

	*X = (double*)malloc(*n*sizeof(double));

	A = allocateMatrix(*n,*n+1);			//the one more column corresponds to the b vector

	//values for matrix A
	for(i=1 ; i<=*n ; i++)					//begins with 1 to n+1 to avoid problems of floating exception
		for(j=1 ; j<=*n ; j++)
			(i==j)? A[i-1][j-1]=*n : A[i-1][j-1]=(1/((double)i+(double)j-(double)1));


	//values for X
	for(i=0 ; i<*n ; i++)
		(*X)[i]=1;

	//b computation
	for(i=0 ; i<*n ; i++){
		A[i][*n] = 0;					//initializes into zero all the values of b vector
		for(j=0 ; j<*n ; j++)
			A[i][*n] += A[i][j]*(*X)[j];
	}
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** randomInput_A(int *n){
//data of matrix A are randomly selected and inserted

	srand(time(NULL));

	double **A;
    int i,j;

    printf("Give matrix[NXN] dimension N(e.g. 100,500,1000) : ");
    scanf("%d",n);

	A = allocateMatrix(*n, *n+1);							//the one more column corresponds to the b vector

	//values for matrix A
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++){
			if(i==j)
				A[i][j] = ((double)(rand()%101));			//matrix elements take from 0 to 100;
			else if(i<j){
				A[i][j] = sign()*((double)(rand()%101));	//matrix elements take from -100 to 100;
				A[j][i] = A[i][j];							// A is symmetric
			}
		}
		
	//randomly selected data for b vector below so that X is (1,1,...,1,1)^T
	for(i=0 ; i<*n ; i++){
			A[i][*n]=0.0;									//initializes into zero all the values of b vector
			for(j=0 ; j<*n ; j++)
				A[i][*n] += A[i][j];
	}

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double * randomInput_X(int n){
//data of matrix X are randomly selected and inserted

	double *X;
	int i;

	X = (double*)malloc(n*sizeof(double));

	//randomly selected data for X vector below so that X is (1,1,...,1,1)^T
	for (i=0 ; i<n ; i++)
		X[i] = 1;

	return X;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** fileInput_Axb(int *n, double **X){
//data of matrix A and vectors x and b are inserted from file(extra adjustment)

	double **A;
	int i,j;
	FILE *file;

	if((file=fopen("ask3_CG.txt", "r"))==NULL){
		perror("FILE ERROR : Either the file with name 'ask3_CG.txt' does not exist or it is placed in a wrong directory");
		exit(0);			//not return 0..
	}

	fscanf(file, "%d", n);					//the first line in file includes only the number of A dimensions
	printf("Dimensions given from the file are %dX%d\n", *n, *n);

	A = allocateMatrix(*n,*n+1);			//the one more column corresponds to the b vector

	(*X) = (double*)malloc(*n*sizeof(double));

	//reading data from file and import them in matrix A below
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++)
			fscanf(file,"%lf",&A[i][j]);

	//reading data from file and import them in vector b below
	for (i=0 ; i<*n ; i++)
		fscanf(file,"%lf",&A[i][*n]);

	//reading data from file and import them in vector X below
	for(i=0 ; i<*n ; i++)
		fscanf(file,"%lf",&(*X)[i]);

	fclose(file);
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CG(double **A, double *x, int n){
//linear system resolution of Ax=b with CG method

	double cputime;
    struct timeval t1, t2;
	int i, j, itmax, itcount=0;

	printf("Give the maximum number of iterations that you want to be applied so that a system solution will be computed \
			\n Suggestion : If you type a big number(e.g. 100) probably you will find a solution(e.g. if you chose a 10X10 matrix type 20) : ");
	scanf("%d", &itmax);

	printf("\n\nExecution of CG method for linear system Ax = b resolution started...\n\n");
	gettimeofday(&t1, NULL);
	CG_Method(A, &x, n, itmax, &itcount);
	gettimeofday(&t2, NULL);
	printf("\n\nExecution of CG method for linear systems Ax = b resolution ended...\n");

	cputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	cputime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	printf("\nMatrix A with vector b in last column :\n");
	for(i=0 ; i<n ; i++, printf("\n"))
		for (j=0 ; j<n+1 ; j++)
			printf("%7.1lf", A[i][j]);

	printf("\n\nLINEAR SYSTEM SOLUTION :\n");
	printf("\tx = ( ");
	for(i=0 ; i<n-1 ; i++)
		printf("%7.3lf, ", x[i]);
	printf("%7.3lf )^T\n\n", x[n-1]);

	(itcount < itmax) ? printf("\nAPPROXIMATE LINEAR SOLUTION FOR THE MATRIX WAS FOUND AFTER %d ITERATIONS\n", itcount) :
						printf("\nAPPROXIMATE LINEAR SOLUTION FOR THE MATRIX WAS NOT FOUND AMONG %d ITERATIONS. LAST APPROXIMATE SOLUTION WAS PRINTED.\n", itmax);
	
	printf("\nExecution time of CG system : %.4lf ms\n\n", cputime);

	//free matrices
    for(i=0 ; i<n ; i++)
		free(A[i]);
    free(A);
    free(x);
}


/**
*		functions used in the other functions ordered in sequence of their appearence
*/


double ** allocateMatrix(int n, int m){
//dynamic allocation of matrices

	double **A;
	int i,j;

	A=(double**)malloc(n*sizeof(double*));
	for(i=0;i<n;i++)
		*(A+i)=(double*)malloc(m*sizeof(double));

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double sign(){
//srand(time(NULL));

	if(rand()%2==0)
		return 1.0;
	else
		return -1.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double factorial(int n){
//computes factorial

	double f;		//because in the matrix_NXN and PascalMatrix_NXN some data are over 1000, and int can't hold such numberss 
	int i;
	
	f=1.0;

	for(i=n ; i>0 ; i--)
		f *= (double)i;

	return f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CG_Method(double **A, double **u, int n, int itmax, int *itcount){
//algorithm of CG

	long double e = 0.0000005;
	double *Au, *r, *p, *w, a=0.0, b=0.0, r_norm=0.0, r_norm2, pw_mult;
	int i, j;


	//Au, r, p, w, r, s matrix allocations
	Au = (double*)malloc(n*sizeof(double));
	r = (double*)malloc(n*sizeof(double));
	p = (double*)malloc(n*sizeof(double));
	w = (double*)malloc(n*sizeof(double));

	//initialization of Au, r, p, r, s
	for(i=0 ; i<n ; i++){
		(*u)[i] = A[i][n];
		Au[i] = 0.0;
		r[i] = 0.0;
		p[i] = 0.0;
		//w[i] = 0;
	}

	//assignements
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<n ; j++)
			Au[i] += A[i][j]*(*u)[j];
		r[i] = A[i][n]-Au[i];
		p[i] = r[i];
		r_norm += r[i]*r[i];
	}

	for( ; (*itcount)<itmax ; (*itcount)++){
		for(i=0 ; i<n ; i++){
			w[i] = 0.0;
			for(j=0 ; j<n ; j++)
				w[i] += A[i][j]*p[j];
		}
		
		pw_mult = 0.0;
		for(i=0 ; i<n ; i++)
			pw_mult += p[i]*w[i];

		a = ((double)r_norm)/((double)pw_mult);
		for(i=0 ; i<n ; i++){
			(*u)[i] += ((double)a*p[i]);
			r[i] -= a*w[i];
			//printf("--%lf--",(*u)[i]);
		}

		r_norm2 = 0.0;
		for(i=0 ; i<n ; i++)
			r_norm2 += r[i]*r[i];

		if(r_norm2 < e)
			break;
        else{
			b = (double)r_norm2/(double)r_norm;
			r_norm = r_norm2;
			for(i=0 ; i<n ; i++)
				p[i] = r[i]+((double)b*p[i]);
		}
	}
		
	free(Au);
    free(r);
    free(p);
    free(w);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

