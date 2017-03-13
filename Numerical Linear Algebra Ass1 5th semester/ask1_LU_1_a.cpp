/***************************************************************************************************************************
* University/Faculty	: National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor	: Numerical Linear Algebra - Tzaferis Filippos
* File name				: ask1_LU_1_a.cpp
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
double ** matrix_5X5(int*, double**);
double ** matrix_8X8(int*, double**);
double ** HilbertMatrix_10X10(int*, double**);
double ** matrix_NXN(int*, double**);

double ** randomInput_A(int*);
double * randomInput_X(int);

double ** fileInput_AX(int*, double**);

void LU(double**, double*, int);
double ** LU_inverted(double**, double**, int, int, int);

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

	int back2menu, n;
	double **A, *X;

	printf("\nLINEAR SYSTEM RESOLUTION OF Ax = b SYSTEMS USING LU DECOMPOSITION METHOD (WITH PARTIAL PIVOTING)\n");

	while(1){

		back2menu = 0;

		switch(menu()){
			case 1:	A = userInput_A(&n);
					X = userInput_X(n);
					break;

			case 2: switch(list_specificMatrices()){
						case 1:	A = matrix_5X5(&n, &X);
								break;
						case 2:	A = matrix_8X8(&n, &X);
								break;
						case 3:	A = HilbertMatrix_10X10(&n, &X);
								break;
						case 4:	A = matrix_NXN(&n, &X);
								break;
						case 5: back2menu = 1;
								break;
						default:break;
					}
					break;

			case 3: A = randomInput_A(&n);
					X = randomInput_X(n);
					break;

			case 4:	A = fileInput_AX(&n, &X);
					break;

			case 5: printf ("\n\n\tHOPE THAT YOU ENJOYED USING MY PROGRAM FOR FINDING LINEAR SYSTEM SOLUTIONS \
					\n\tFOR SYSTEMS OF TYPE Ax = b USING THE LU DECOMPOSITION METHOD (WITH PARTIAL PIVOTING) \
					\n\n\tREGARDS NIKOLAOS BEGETIS UNDERGRADUATE STUDENT OF DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS, UNIVERSITY OF ATHENS \
					\n\n\t2011-2012\n");
					return 0;

			default:break;
		}
	if(back2menu!=1)
		LU(A, X, n);
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
		\n\t4. File input: you are about to give a text file with your matrices in it. The file name must have the name:'ask1_LU_1_a.txt' \
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

	printf("\nGive vector X data below (e.g 1,2,3,1,2 for the first adjustment 1.a.1) :\n");
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
		\nSwitch the specific matrix to solve a linear system as given from exercise ask1_LU.1.a: \
		\n\t1. Matrix of dimensions 5X5 (adjustment 1.a.1) \
		\n\t2. Matrix of dimensions 8X8 (adjustment 1.a.2) \
		\n\t3. Hilbert Matrix of dimensions 10X10 (adjustment 1.a.3) \
		\n\t4. Matrix of dimensions NXN, where N given by you with values 100,500,1000 and system solution: x=(1,1,...,1,1)^T (adjustment 1.a.4) \
		\n\n\t5. Select if you want to return to MAIN MENU.\n");
		printf("INPUT : ");
		scanf("%d", &matrix_no);
	}while((matrix_no<1)||(matrix_no>5));
	return matrix_no;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** matrix_5X5(int *n, double **X){
//returns the a specific matrix (adjustment 1.a.1)

    double **A;

	*n=5;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=2;	A[0][1]=1;	A[0][2]=-3;	A[0][3]=4;	A[0][4]=2;	A[0][5]=3;
    A[1][0]=-3;	A[1][1]=2;	A[1][2]=5;	A[1][3]=-3;	A[1][4]=1;	A[1][5]=15;
    A[2][0]=8;	A[2][1]=1;	A[2][2]=-3;	A[2][3]=2;	A[2][4]=4;	A[2][5]=11;
    A[3][0]=-4;	A[3][1]=2;	A[3][2]=3;	A[3][3]=-1;	A[3][4]=5;	A[3][5]=18;
    A[4][0]=6;	A[4][1]=2;	A[4][2]=1;	A[4][3]=-5;	A[4][4]=9;	A[4][5]=26;

    *X = (double*)malloc(*n*sizeof(double));
    (*X)[0]=1;	(*X)[1]=2;	(*X)[2]=3;	(*X)[3]=1;	(*X)[4]=2;

    return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** matrix_8X8(int *n, double **X){
//returns the a specific matrix (adjustment 1.a.2)

    double **A;

	*n=8;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=10;	A[0][1]=-2;	A[0][2]=-1;	A[0][3]=2;	A[0][4]=3;	A[0][5]=1;	A[0][6]=-4;	A[0][7]=7;	A[0][8]=-6;
    A[1][0]=5;	A[1][1]=11;	A[1][2]=3;	A[1][3]=10;	A[1][4]=-3;	A[1][5]=3;	A[1][6]=3;	A[1][7]=-4;	A[1][8]=-22;
    A[2][0]=7;	A[2][1]=12;	A[2][2]=1;	A[2][3]=5;	A[2][4]=3;	A[2][5]=-12;A[2][6]=2;	A[2][7]=3;	A[2][8]=19;
    A[3][0]=8;	A[3][1]=7;	A[3][2]=-2;	A[3][3]=1;	A[3][4]=3;	A[3][5]=2;	A[3][6]=2;	A[3][7]=4;	A[3][8]=-19;
    A[4][0]=2;	A[4][1]=-15;A[4][2]=-1;	A[4][3]=4;	A[4][4]=-2;	A[4][5]=-1;	A[4][6]=8;	A[4][7]=3;	A[4][8]=26;
    A[5][0]=4;	A[5][1]=2;	A[5][2]=9;	A[5][3]=1;	A[5][4]=12;	A[5][5]=-1;	A[5][6]=4;	A[5][7]=1;	A[5][8]=55;
    A[6][0]=-1;	A[6][1]=4;	A[6][2]=-7;	A[6][3]=-1;	A[6][4]=1;	A[6][5]=1;	A[6][6]=-1;	A[6][7]=-3;	A[6][8]=-25;
    A[7][0]=-1;	A[7][1]=3;	A[7][2]=4;	A[7][3]=1;	A[7][4]=3;	A[7][5]=-4;	A[7][6]=7;	A[7][7]=6;	A[7][8]=17;

    *X = (double*)malloc(*n*sizeof(double));

    (*X)[0]=1;	(*X)[1]=-2;	(*X)[2]=3;	(*X)[3]=-1;	(*X)[4]=2;	(*X)[5]=-3;	(*X)[6]=1;	(*X)[7]=-2;

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** HilbertMatrix_10X10(int *n, double **X){
//returns the a specific matrix (adjustment 1.a.3)

	double **A;
	int i, j;

	*n = 10;
/** if we would like we could also give any other dimension for Hilbert matrix
*	printf("Give Hilbert matrix[NXN] dimension N : ");
*   scanf("%d",n);
*/

	*X = (double*)malloc(*n*sizeof(double));

	A = allocateMatrix(*n,*n+1);			//the one more column corresponds to the b vector

	//values for A Hilbert Matrix
	for(i=1 ; i<=*n ; i++)					//begins with 1 to n+1 to avoid problems of floating exception
		for(j=1 ; j<=*n ; j++)
			A[i-1][j-1]= 1/((double)i+(double)j-(double)1);			//formula as given

	//values for X
	for(i=0 ; i<*n ; i++)
		((i%2)==0)?(*X)[i]=1:(*X)[i]=-2;

	//b computation
	for(i=0 ; i<*n ; i++){
		A[i][*n] = 0;					//initializes into zero all the values of b vector
		for(j=0 ; j<*n ; j++)
			A[i][*n] += A[i][j]*((*X)[j]);
	}
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** matrix_NXN(int *n, double **X){
//returns the a specific matrix (adjustment 1.a.4)

	double **A;
	int i, j;

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

	//randomly selected data for b vector below so that X is (1,1,...,1,1)^T
	for(i=0 ; i<*n ; i++){
			A[i][*n]=0.0;						//initializes into zero all the values of b vector
			for(j=0 ; j<*n ; j++)
				A[i][*n]=A[i][*n]+A[i][j];
	}
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double * randomInput_X(int n){
//data of matrix X are randomly selected and inserted (adjustment 1.a.5)

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

double ** fileInput_AX(int *n, double **X){
//data of matrix A and vector X are inserted from file(adjustment 1.a.6)

	double **A;
	int i,j;
	FILE *file;

	if((file=fopen("ask1_LU_1_a.txt", "r"))==NULL){
		perror("FILE ERROR : Either the file with name 'ask1_LU_1_a.txt' does not exist or it is placed in a wrong directory");
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

void LU(double **A, double *X, int n){
//linear system resolution of Ax=b with LU method(with partial pivoting)

	double **U, **L, **A_inverted, *x, *y;
	double sum, normA, normA_inverted;
	double cputime;
    struct timeval t1, t2;
	int i,j;


	y =(double*)malloc(n*sizeof(double));
	x =(double*)malloc(n*sizeof(double));
	U = allocateMatrix(n,n);
	L = allocateMatrix(n,n);

	gettimeofday(&t1, NULL);
	printf("\n\nExecution of LU method(with partial pivoting) for linear system Ax = b resolution started...\n\n");

	LU_factorizationMethod(A, &L, &U, n);

	//system solution for Ly=b
	y[0] = A[0][n]/L[0][0];
	for(i=1 ; i<n ; i++){
		sum=0;
		for(j=0 ; j<i ; j++)
			sum += y[j]*L[i][j];
		y[i] = (A[i][n]-sum)/L[i][i];
	}

	//system solution for Ux=y
	x[n-1] = y[n-1]/U[n-1][n-1];
	for(i=n-2 ; i>=0 ; i--){
		sum=0;
		for(j=n-1 ; j>i ; j--)
				sum += x[j]*U[i][j];
		x[i]=(y[i]-sum)/U[i][i];
	}


	printf("\nMatrix A with vector b in last column :\n");
	for(i=0 ; i<n ; i++, printf("\n"))
		for (j=0 ; j<n+1 ; j++)
			printf("%7.2lf", A[i][j]);

	printf("\n\nMatrix L :\n");
	for(i=0 ; i<n ; i++, printf("\n"))
		for(j=0 ; j<n ; j++)
			printf("%7.2lf", L[i][j]);

	printf("\n\nMatrix U :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
				printf("%7.2lf", U[i][j]);

	printf("\n\nVector y :\n");
	printf("y =( ");
	for(i=0 ; i<n-1 ; i++)
		printf("%7.2lf, ", y[i]);
	printf("%7.2lf )^T\n", y[n-1]);

    printf("\n\nLINEAR SYSTEM SOLUTION :\n");
	printf("\tx = ( ");
	for(i=0 ; i<n-1 ; i++)
		printf("%7.2lf, ", x[i]);
	printf("%7.2lf )^T\n", x[n-1]);

	printf("\nThe approximate relative fault of system is : %.20lf\n", apprRelativeFault(x, X, n));
	printf("\nThe approximate relative modulo of system is : %.20lf\n", apprRelativeModulo(A, x, X, n));


	normA = maxMatrixNorm(A, n);

	A_inverted = LU_inverted(A, A_inverted, n, 1, 0);
	normA_inverted = maxMatrixNorm(A_inverted, n);
	//printf("normA : %lf\n", normA);
	//printf("normA_inverted : %lf\n", normA_inverted);
	printf("Condition number of A matrix : %lf\n", normA*normA_inverted);


	gettimeofday(&t2, NULL);

    cputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    cputime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	printf("\n\nExecution of LU method(with partial pivoting) for linear system Ax = b resolution ended...\n");
	printf("Execution time of LU system : %.4lf ms\n\n", cputime);

    for(i=0 ; i<n ; i++){
		free(L[i]);
		free(U[i]);
		free(A[i]);
    }
    free(L);
    free(A);
    free(U);
    free(x);
    free(X);
    free(y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** LU_inverted(double **A, double **A_inverted, int n, int is_inverted, int random){
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

	if((random==0)&&(is_inverted==0)){

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
				printf("%7.2lf", A[i][j]);

		printf("\n\nMatrix A^-1 :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
				printf("%7.2lf", A_inverted_local[i][j]);

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

		printf("\n\nDue to the fact that in random matrices we don't know the Χ inverted vector faults are not computed, \
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

