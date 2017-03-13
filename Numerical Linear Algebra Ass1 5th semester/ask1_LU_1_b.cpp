/***************************************************************************************************************************
* University/Faculty	: National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor	: Numerical Linear Algebra - Tzaferis Filippos
* File name				: ask1_LU_1_b.cpp
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
double ** userInput_A_inverted(int);

int list_specificMatrices_inverted();
double ** matrix_4X4(int*);
double ** matrix_4X4_inverted(int);
double ** PeiMatrix_NXN(int*);
double ** PeiMatrix_NXN_inverted(int);
double ** HilbertMatrix_NXN(int*);
double ** HilbertMatrix_NXN_inverted(int);

double ** randomInput_A(int*);
double ** randomInput_A_inverted(int);

double ** fileInput_A_inverted(int*, double***);

double ** LU_inverted(double**, double**, int, int);

double ** allocateMatrix(int, int);
int factorial(int);
void LU_factorizationMethod(double **, double ***, double ***, int);
double apprRelativeFault(double*, double*, int);
double apprRelativeModulo(double**, double*, double*, int);
double maxNorm(double*, int);
double maxMatrixNorm(double**, int);
double apprRelativeFault_inverted(double**, double**, int);
double apprRelativeModulo_inverted(double**, double**, double**, int);



int main(int argc, char* argv[]){
//main of ask1_LU_1_a.cpp

	int back2menu, n, random_boolean=0;
	double **A, **A_inverted;

	printf("\nCOMPUTATION OF INVERTED MATRICES USING LU DECOMPOSITION METHOD (WITH PARTIAL PIVOTING)\n");

	while(1){

		back2menu = 0;

		switch(menu()){
			case 1:	A = userInput_A(&n);
					A_inverted = userInput_A_inverted(n);
					break;

			case 2: switch(list_specificMatrices_inverted()){
						case 1:	A = matrix_4X4(&n);
								A_inverted = matrix_4X4_inverted(n);
								break;
						case 2:	A = PeiMatrix_NXN(&n);
								A_inverted = PeiMatrix_NXN_inverted(n);
								break;
						case 3:	A = HilbertMatrix_NXN(&n);
								A_inverted = HilbertMatrix_NXN_inverted(n);
								break;
						case 4: back2menu = 1;
								break;
						default:break;
					}
					break;

			case 3: A = randomInput_A(&n);
					A_inverted = randomInput_A_inverted(n);
					random_boolean = 1;
					break;

			case 4:	A = fileInput_A_inverted(&n, &A_inverted);
					break;

			case 5: printf ("\n\n\tHOPE THAT YOU ENJOYED USING MY PROGRAM FOR COMPUTATING INVERTED MATRICES \
					\n\tUSING LU DECOMPOSITION METHOD (WITH PARTIAL PIVOTING) \
					\n\n\t REGARDS NIKOLAOS BEGETIS UNDERGRADUATE STUDENT OF DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS, UNIVERSITY OF ATHENS \
					\n\n\t2011-2012\n");
					return 0;
					
			default:break;
		}
		if(back2menu!=1){
			if (random_boolean == 0)
				LU_inverted(A, A_inverted, n, 0);
			else
				LU_inverted(A, A, n, 1);
		}
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
		\n\t4. File input: you are about to give a text file with your matrices in it. The file name must have the name:'ask1_LU_1_b.txt' \
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

    printf("\nInsert Á matrix data below:\n");
    for(i=0 ; i<*n ; i++){
        for(j=0 ; j<*n ; j++){
			printf("A[%d][%d] = ", i, j);
			scanf ("%lf", &A[i][j]);
        }
    }

    return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** userInput_A_inverted(int n){
//data of matrix A_inverted are inserted by the user

	double **A_inverted;
	int i, j;

	A_inverted = allocateMatrix(n,n);

	printf("\nInsert Á^-1 matrix data below:\n");
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<n ; j++){
			printf("A^-1[%d][%d] = ", i, j);
			scanf ("%lf", &A_inverted[i][j]);
		}
	}
	return A_inverted;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int list_specificMatrices_inverted(){
//menu for the 2nd selection of the main manu

	int matrix_no;
	do{
		printf("\n\nSpecific matrices LIST \
		\nSwitch the specific matrix to compute the inverted matrix as given from exercise ask1_LU.1.b: \
		\n\t1. Matrix of dimensions 4X4 (adjustment 1.b.1) \
		\n\t2. Pei Matrix of dimensions NXN, where N given by you with values 100,500,1000 (adjustment 1.b.2) \
		\n\t3. Hilbert Matrix of dimensions NXN, where N given by you with values 10,50,100 (adjustment 1.b.3)\n \
		\n\n\t4. Select if you want to return to MAIN MENU.\n");
		printf("INPUT: ");
		scanf("%d", &matrix_no);
	} while((matrix_no<1)||(matrix_no>4));
	return matrix_no;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** matrix_4X4(int *n){
//returns the a specific matrix (adjustment 1.b.1)

	double **A;

	*n=4;

	A = allocateMatrix(4, 4);

	A[0][0]=5;	A[0][1]=7;	A[0][2]=6;	A[0][3]=5;
	A[1][0]=7;	A[1][1]=10;	A[1][2]=8;	A[1][3]=7;
	A[2][0]=6;	A[2][1]=8;	A[2][2]=10;	A[2][3]=9;
	A[3][0]=5;	A[3][1]=7;	A[3][2]=9;	A[3][3]=10;

    return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** matrix_4X4_inverted(int n){
//returns the a specific matrix (adjustment 1.b.1)

	double **A;

	A = allocateMatrix(n, n);

	A[0][0]=68;	A[0][1]=-41;A[0][2]=-17;A[0][3]=10;
	A[1][0]=-41;A[1][1]=25;	A[1][2]=10;	A[1][3]=-6;
	A[2][0]=-17;A[2][1]=10;	A[2][2]=5;	A[2][3]=-3;
	A[3][0]=10;	A[3][1]=-6;	A[3][2]=-3;	A[3][3]=2;

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** PeiMatrix_NXN(int *n){
//returns the a specific matrix (adjustment 1.b.2)

	double **A;
	int i, j;

	printf("Give Pei matrix[NXN] dimension N(e.g. 100,500,1000) : ");
	scanf("%d",n);

	A = allocateMatrix(*n, *n);

	for(i=0 ; i<*n ; i++)
		for (j=0 ; j<*n ; j++)
			(i==j)?A[i][j]=*n:A[i][j]=1;
   return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** PeiMatrix_NXN_inverted(int n){
//returns the a specific matrix (adjustment 1.b.2)

	double **A;
	int i, j;

	A = allocateMatrix(n, n);

	for(i=0 ; i<n ; i++)
		for (j=0 ; j<n ; j++)
			(i==j)?A[i][j]=(double)2/((double)2*(double)n-(double)1) : A[i][j] = -(double)1/(((double)n-(double)1)*((double)2*(double)n-(double)1));
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** HilbertMatrix_NXN(int *n){
//returns the a specific matrix (adjustment 1.b.3)

	double **A;
	int i, j;


	printf("Give Hilbert matrix[NXN] dimension N(e.g. 10,50,100) : ");
	scanf("%d",n);

   A = allocateMatrix(*n, *n);

	for (i=1 ; i<*n+1 ; i++)                   //begins with 1 to n+1 to avoid problems of floating exception
		for (j=1 ; j<*n+1 ; j++)
			A[i-1][j-1]= 1/((double)i+(double)j-(double)1);
   return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** HilbertMatrix_NXN_inverted(int n){
//returns the a specific matrix (adjustment 1.b.3)

	double **A;
	int i, j;

   A = allocateMatrix(n, n);

	for(i=0 ; i<n ; i++)
		for(j=0; j<n; j++)
			A[i][j] = (double)(pow(-1,i+j)*factorial(n+i-1)*factorial(n+j-1)) / (double)((i+j-1)*pow(factorial(i-1)*factorial(j-1),2)*factorial(n-i)*factorial(n-j));
			//the function pow is included from the <math> library
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** randomInput_A(int *n){
//data of matrix A are randomly selected and inserted (adjustment 1.a.5)

	double **A;
    int i,j;

	srand(time(NULL));

    printf("Give matrix[NXN] dimension N : ");
    scanf("%d",n);

	A = allocateMatrix(*n, *n+1);				//the one more column corresponds to the b vector

	//randomly selected data for matrix A below
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++)
			A[i][j]=rand()%100;

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** randomInput_A_inverted(int n){
//data of matrix A_inverted are randomly selected and inserted (adjustment 1.b.4)

	double **A_inverted;
	int i, j;

	A_inverted = allocateMatrix(n,n);

	//randomly selected data for X vector below so that X is (1,1,...,1,1)^T

	return A_inverted;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** fileInput_A_inverted(int *n, double ***A_inverted){
//data of matrix A_inverted are inserted from file(adjustment 1.b.5)

   	double **A;
	int i,j;
	FILE *file;

	if((file=fopen("ask1_LU_1_b.txt", "r"))==NULL){
		perror("FILE ERROR : Either the file with name 'ask1_LU_1_b.txt' does not exist or it is placed in a wrong directory");
		exit(0);			//not return 0..
	}

	fscanf(file, "%d", n);					//the first line in file includes only the number of A dimensions
	printf("Dimensions given from the file are %dX%d\n", *n, *n);

	A = allocateMatrix(*n,*n);

	(*A_inverted) = allocateMatrix(*n,*n);

	//reading data from file and import them in matrix A below
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++)
			fscanf(file,"%lf",&A[i][j]);

	//reading data from file and import them in matrix A_inverted below
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++)
			fscanf(file,"%lf",&(*A_inverted)[i][j]);

   fclose(file);
   return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** LU_inverted(double **A, double **A_inverted, int n, int random){
//computation of A^-1 with LU method(with partial pivoting)

	double **U, **L, *x, **y, *z, *b, **A_inverted_local;
	double sum, normA, normA_inverted;
	double cputime;
    struct timeval t1, t2;
	int i,j,k;


	b = (double*)malloc(n*sizeof(double));
	z = (double*)malloc(n*sizeof(double));
	x = (double*)malloc(n*sizeof(double));
	U = allocateMatrix(n,n);
	L = allocateMatrix(n,n);
	A_inverted_local = allocateMatrix(n,n);

	for(k=0 ; k<n ; k++)
		b[k]=0;


	gettimeofday(&t1, NULL);
	printf("\n\nExecution of LU method(with partial pivoting) to compute A^-1 matrix started...\n\n");


	for(k=0 ; k<n ; k++){
		b[k]=1;

		LU_factorizationMethod(A,&L,&U,n);

		//system solution for Lz=b
		z[0] = b[0]/L[0][0];
		for(i=1 ; i<n ; i++){
			sum=0;
			for(j=0 ; j<i ; j++)
				sum += z[j]*L[i][j];
			z[i] = (b[i]-sum)/L[i][i];
		}

		//system solution for Ux=z
		x[n-1] = z[n-1]/U[n-1][n-1];
		for(i=n-2 ; i>=0 ; i--){
			sum=0;
			for(j=n-1 ; j>i ; j--)
				sum += x[j]*U[i][j];
			x[i]=(z[i]-sum)/U[i][i];
		}

		//system solution for A^-1, just inverted...
		for(i=0 ; i<n ; i++)
			A_inverted_local[i][k]=x[i];

		b[k]=0;
	}

	if(random==0){

		printf("\nMatrix A :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
			printf("%7.2lf", A[i][j]);

		printf("\nMatrix A^-1 :\n");
		for(i=0;i<n; i++, printf("\n"))
			for(j=0; j<n; j++)
				printf("%7.2lf", A_inverted_local[i][j]);

		normA = maxMatrixNorm(A, n);
		normA_inverted = maxMatrixNorm(A_inverted_local, n);

		printf("\nThe approximate relative fault of A and A^-1 is : %.20lf\n", apprRelativeFault_inverted(A_inverted_local, A_inverted, n));
		printf("\nThe approximate relative modulo of A and A^-1 is : %.20lf\n", apprRelativeModulo_inverted(A, A_inverted_local, A_inverted, n));
		printf("Condition number of A matrix : %lf\n", normA*normA_inverted);
	}
	else if(random == 1){
		printf("\nMatrix A :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
				printf("%12.2lf", A[i][j]);

		printf("\n\nMatrix A^-1 :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
				printf("%12.2lf", A_inverted_local[i][j]);

		//y = A*A^-1-I
		y = allocateMatrix(n, n);
		for(i=0 ; i<n ; i++)
			for(j=0 ; j<n ; j++){
				y[i][j] = 0;
				for(k=0 ; k<n ; k++)
					y[i][j] += (A[i][k] * A_inverted_local[k][j]);
			}

		printf("\n\nMatrix A*A^-1 :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
				printf("%7.2lf", y[i][j]);

		printf("\n\nDue to the fact that in random matrices we don't know the × inverted vector faults are not computed, \
				\nas you can see, and so alternatively we compute the inverted matrix B=A^-1 and also the multiplication \
				\nof A*B = A*A^-1 so that we can proove that method LU worked well. We can reach to this conclusion if the \
				\nprinted A*B is the unit matrix(I).\n");
	}

	gettimeofday(&t2, NULL);

    cputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    cputime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	printf("\n\nExecution of LU method(with partial pivoting) to compute A^-1 matrix ended...\n\n");
	printf("Execution time of LU to compute A^-1 : %.4lf ms\n\n", cputime);


	for(i=0 ; i<n ; i++){
		free(U[i]);
		free(L[i]);
	}
	free(U);
	free(L);
	free(z);
	free(b);
	free(x);

	return A_inverted_local;
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

int factorial(int n){
//computes factorial

	int i, f;

	f=1;

	for(i=n ; i>0 ; i--)
		f *= i;

	return f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LU_factorizationMethod(double **A, double ***L, double ***U, int n){
//algorithm of LU for factorizing matrix A in L and U using partial pivoting

	double sum;
	int i, j, k;

	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++){
			(*L)[i][j]=0;
			(*U)[i][j]=0;
		}

	//factorization of A in L and U
	for(i=0 ; i<n ; i++){
		for(j=0 ; j<n ; j++){
			sum=0;
			if(i<=j){
				for(k=0 ; k<n ; k++)
					(k!=i)?sum+=(*L)[i][k]*(*U)[k][j]:NULL;
				(*U)[i][j] = A[i][j]-sum;
			}
			else{
				for(k=0 ; k<n ; k++)
					(k!=j)?sum+=(*L)[i][k]*(*U)[k][j]:NULL;
				(*L)[i][j] = (A[i][j]-sum)/(*U)[j][j];
			}
		}
	}

	//U triangular disjanction
	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++)
			(i>j)?(*U)[i][j]=0:NULL;

	//L triangular disjanction
	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++){
			if(i==j)
				(*L)[i][j]=1;
			else if(i<j)
				(*L)[i][j]=0;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double apprRelativeFault(double *x,double *X, int n){
//computation of approximate relative fault

	double  *x_rel_fault;
	double max1, max2;
	int i;

	x_rel_fault = (double*)malloc(n*sizeof(double));

	for(i=0 ; i<n ; i++)
		x_rel_fault[i]=X[i]-x[i];

	max1=maxNorm(x_rel_fault, n);
	max2=maxNorm(X, n);

	free(x_rel_fault);

	return (max1/max2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double apprRelativeModulo(double **A, double *x, double *X, int n){
//computation of approximate relative modulo

	double  *x_rel_modulo;
	double	sum, max1, max2;
    int i, j;

	x_rel_modulo = (double*)malloc(n*sizeof(double));

	for(i=0 ; i<n ; i++){
		sum=0;
        for(j=0 ; j<n ; j++)
			sum += A[i][j]*x[j];
        x_rel_modulo[i] = A[i][n]-sum;
    }

	max1=maxNorm(x_rel_modulo, n);
	max2=maxNorm(X, n);

	free(x_rel_modulo);

	return (max1/max2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double maxNorm(double* x, int n){
//computes the norm with max value

    double max;
    int i;

    max = fabs(x[0]);		//fabs is included from the math library and returns tha absolute value of the function parameter

	for(i=1 ; i<=n-1 ; i++)
		(fabs(x[i])>max)?max=fabs(x[i]):NULL;

	return max;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double maxMatrixNorm(double **A, int n){
//computes the norm with max value in a two-dimensional matrix

	double *matrix;
	double sum, max;
	int i, j;

	matrix = (double*)malloc(n*sizeof(double));

	for(i=0 ; i<n ; i++){
		sum=0;
		for(j=0 ; j<n ; j++)
			sum=sum+fabs(A[i][j]);
		matrix[i]=sum;
	}

	max=maxNorm(matrix,n);

	free(matrix);

	return max;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double apprRelativeFault_inverted(double **A_inv_local, double **A_inv, int n){
//computation of approximate relative fault of A_inversed

	double  **A_rel_fault;
	double max1, max2;
    int i, j;

	A_rel_fault = allocateMatrix(n,n);

	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++)
			A_rel_fault[i][j] = A_inv[i][j]-A_inv_local[i][j];

	max1=maxMatrixNorm(A_rel_fault, n);
	max2=maxMatrixNorm(A_inv, n);

	for (i=0 ; i<n ; i++)
		free(A_rel_fault[i]);
	free(A_rel_fault);

	return (max1/max2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double apprRelativeModulo_inverted(double **A, double **A_inv_local,double **A_inv, int n){
//computation of approximate relative modulo of A_inversed


    double  **A_rel_modulo, **I;
	double sum, max1, max2;
	int i, j, k;

    A_rel_modulo = allocateMatrix(n,n);
    I = allocateMatrix(n,n);

	//creating unit matrix I
	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++)
			(i==j)?I[i][j]=1:I[i][j]=0;

	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++){
			A_rel_modulo[i][j] = 0;
			for(k=0 ; k<n ; k++)
				A_rel_modulo[i][j] += A[i][k]*A_inv_local[k][j];
		}

	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++)
			A_rel_modulo[i][j] = A_rel_modulo[i][j]-I[i][j];

    max1 = maxMatrixNorm(A_rel_modulo, n);
    max2 = maxMatrixNorm(A_inv, n);

	for (i=0 ; i<n ; i++){
		free(I[i]);
		free(A_rel_modulo[i]);
	}
    free(I);
    free(A_rel_modulo);

    return (max1/max2);
}
