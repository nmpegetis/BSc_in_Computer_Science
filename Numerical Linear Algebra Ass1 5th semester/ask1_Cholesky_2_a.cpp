/***************************************************************************************************************************
* University/Faculty	: National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor	: Numerical Linear Algebra - Tzaferis Filippos
* File name				: ask1_Cholesky_2_a.cpp
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
double ** matrix_4X4_Cholesky(int*, double**);
double ** MolerMatrix_5X5(int*, double**);
double ** PascalMatrix_5X5(int*, double**);
double ** PascalMatrix_8X8(int*, double**);
double ** PascalMatrix_NXN(int*, double**);
double ** matrix_NXN(int*, double**);

double ** randomInput_A(int*);
double * randomInput_X(int);

double ** fileInput_AX(int*, double**);

void Cholesky(double**, double*, int);
double ** Cholesky_inverted(double**, double**, int, int, int);

double ** allocateMatrix(int, int);
double factorial(int);
void Cholesky_factorizationMethod(double **, double ***, double ***, int);
double apprRelativeFault(double*, double*, int);
double apprRelativeModulo(double**, double*, double*, int);
double maxNorm(double*, int);
double maxMatrixNorm(double**, int);
double apprRelativeFault_inverted(double**, double**, int);
double apprRelativeModulo_inverted(double**, double**, double**, int);



int main(int argc, char* argv[]){
//main of ask1_Cholesky_1_a.cpp

	int back2menu, n;
	double **A, *X;

	printf("\nLINEAR SYSTEM RESOLUTION OF Ax = b SYSTEMS USING CHOLESKY FACTORIZATION METHOD\n");

	while(1){

		back2menu = 0;

		switch(menu()){
			case 1:	A = userInput_A(&n);
					X = userInput_X(n);
					break;

			case 2: switch(list_specificMatrices()){
						case 1:	A = matrix_4X4_Cholesky(&n, &X);
								break;
						case 2:	A = MolerMatrix_5X5(&n, &X);
								break;
						case 3:	A = PascalMatrix_5X5(&n, &X);
								break;
						case 4:	A = PascalMatrix_8X8(&n, &X);
								break;
						case 5:	A = PascalMatrix_NXN(&n, &X);
								break;
						case 6:	A = matrix_NXN(&n, &X);
								break;
						case 7: back2menu = 1;
								break;
						default:break;
					}
					break;

			case 3: A = randomInput_A(&n);
					X = randomInput_X(n);
					break;

			case 4:	A = fileInput_AX(&n, &X);
					break;

			case 5: printf ("\n\n\tHOPEFULLY I WILL GET SOME TIME IN CRISTMASS TO CHECK SOME FEW ERRORS IN MY CODE \
					\n\n\tANYWAY, HOPE THAT YOU ENJOYED USING MY PROGRAM FOR SOLVING LINEAR SYSTEMS OF TYPE Ax=B \
					\n\tUSING THE CHOLESKY FACTORIZATION \
					\n\n\tREGARDS NIKOLAOS BEGETIS UNDERGRADUATE STUDENT OF DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS, UNIVERSITY OF ATHENS \
					\n\n\t2011-2012\n\n");
					
					return 0;

			default:break;
		}
		if(back2menu!=1){
			Cholesky(A, X, n);
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
		\n\t4. File input: you are about to give a text file with your matrices in it. The file name must have the name:'ask1_Cholesky_2_a.txt' \
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

    A = allocateMatrix(*n, *n+1);		//the one more coCholeskymn represents the b vector. this allowance has effect in the whole written program

    printf("\nInsert Á matrix data below:\n");
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

	printf("\nGive vector × data below:\n");
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
		\nSwitch the specific matrix to solve a linear system as given from exercise ask1_Cholesky.1.a: \
		\n\t1. Matrix of dimensions 4X4 (adjustment 2.a.1) \
		\n\t2. Moler Matrix of dimensions 5X5 (adjustment 2.a.2) \
		\n\t3. Pascal Matrix of dimensions 5X5 (adjustment 2.a.3) \
		\n\t4. Pascal Matrix of dimensions 8X8 (adjustment 2.a.4) \
		\n\t5. Pascal Matrix of dimensions NXN, where N given by you with values 100,500,1000 and system solution: x=(1,1,...,1,1)^T(adjustment 2.a.5) \
		\n\t6. Matrix of dimensions NXN, where N given by you with values 100,500,1000 and system solution: x=(1,1,...,1,1)^T (adjustment 2.a.6) \
		\n\n\t7. Select if you want to return to MAIN MENU.\n");
		printf("INPUT: ");
		scanf("%d", &matrix_no);
	}while((matrix_no<1)||(matrix_no>7));
	return matrix_no;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** matrix_4X4_Cholesky(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.1)

    double **A;

	*n=4;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=5;	A[0][1]=7;	A[0][2]=6;	A[0][3]=5;	A[0][4]=23;
    A[1][0]=7;	A[1][1]=10;	A[1][2]=8;	A[1][3]=7;	A[1][4]=32;
    A[2][0]=6;	A[2][1]=8;	A[2][2]=10;	A[2][3]=9;	A[2][4]=33;
    A[3][0]=5;	A[3][1]=7;	A[3][2]=9;	A[3][3]=10;	A[3][4]=31;

    *X = (double*)malloc(*n*sizeof(double));
    (*X)[0]=1;	(*X)[1]=1;	(*X)[2]=1;	(*X)[3]=1;

    return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** MolerMatrix_5X5(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.2)

    double **A;

	*n=5;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=2;	A[0][1]=-1;	A[0][2]=-1;	A[0][3]=-1;	A[0][4]=-1;	A[0][5]=-2;
    A[1][0]=-1;	A[1][1]=2;	A[1][2]=0;	A[1][3]=0;	A[1][4]=0;	A[1][5]=1;
    A[2][0]=-1;	A[2][1]=0;	A[2][2]=3;	A[2][3]=1;	A[2][4]=1;	A[2][5]=4;
    A[3][0]=-1;	A[3][1]=0;	A[3][2]=1;	A[3][3]=4;	A[3][4]=2;	A[3][5]=6;
    A[4][0]=-1;	A[4][1]=0;	A[4][2]=1;	A[4][3]=2;	A[4][4]=5;	A[4][5]=7;

    *X = (double*)malloc(*n*sizeof(double));

    (*X)[0]=1;	(*X)[1]=1;	(*X)[2]=1;	(*X)[3]=1;	(*X)[4]=1;	(*X)[5]=1;	(*X)[6]=1;	(*X)[7]=1;
	
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** PascalMatrix_5X5(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.3)

    double **A;

	*n=5;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=1;	A[0][1]=1;	A[0][2]=1;	A[0][3]=1;	A[0][4]=1;	A[0][5]=5;
    A[1][0]=1;	A[1][1]=2;	A[1][2]=3;	A[1][3]=4;	A[1][4]=5;	A[1][5]=15;
    A[2][0]=1;	A[2][1]=3;	A[2][2]=6;	A[2][3]=10;	A[2][4]=15;	A[2][5]=35;
    A[3][0]=1;	A[3][1]=4;	A[3][2]=10;	A[3][3]=20;	A[3][4]=35;	A[3][5]=70;
    A[4][0]=1;	A[4][1]=5;	A[4][2]=15;	A[4][3]=35;	A[4][4]=70;	A[4][5]=126;

    *X = (double*)malloc(*n*sizeof(double));

    (*X)[0]=1;	(*X)[1]=1;	(*X)[2]=1;	(*X)[3]=1;	(*X)[4]=1;
	
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** PascalMatrix_8X8(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.4)

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
//returns the a specific matrix (adjustment 2.a.5)

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

double ** matrix_NXN(int *n, double **X){
//returns the a specific matrix (adjustment 2.a.6)

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
//data of matrix A are randomly selected and inserted (adjustment 2.a.7)

	double **A;
    int i,j;
	
	srand(time(NULL));

    printf("Give matrix[NXN] dimension N : ");
    scanf("%d",n);

	A = allocateMatrix(*n, *n+1);				//the one more column corresponds to the b vector

	//randomly selected data for matrix A below.
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++){
			// A is symmetric
			A[i][j]=rand()%100;
			A[j][i]=A[i][j];
			
			//A is positive definite
			if(i==0||j==0)
				(A[i][i]!=0)?A[i][i]*=2*(*n):A[i][i]=2*(*n);
		}
		
	//randomly selected data for b vector below so that X is (1,1,...,1,1)^T
	for(i=0 ; i<*n ; i++){
			A[i][*n]=0.0;						//initializes into zero all the values of b vector
			for(j=0 ; j<*n ; j++)
				A[i][*n]=A[i][*n]+A[i][j];
	}
	printf("\nsometimes the usage of random shows problems... i haven't fixed that yet... \ntry small numbers!!! in most cases it succeeds!!\n");
	
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

	if((file=fopen("ask1_Cholesky_2_a.txt", "r"))==NULL){
		perror("FILE ERROR : Either the file with name 'ask1_Cholesky_1_a.txt' does not exist or it is placed in a wrong directory");
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

void Cholesky(double **A, double *X, int n){
//linear system resoCholeskytion of Ax=b with Cholesky method

	double **I, **I_inv;
	double **A_inverted, *x, *y;
	double sum, normA, normA_inverted;
	double cputime;
    struct timeval t1, t2;
	int i,j;


	y =(double*)malloc(n*sizeof(double));
	x =(double*)malloc(n*sizeof(double));
	I = allocateMatrix(n,n);
	I_inv = allocateMatrix(n,n);

	gettimeofday(&t1, NULL);
	printf("\n\nExecution of Cholesky method for linear system Ax = b resolution started...\n\n");

	Cholesky_factorizationMethod(A, &I, &I_inv, n);			
	
	//system solution for Iy=b
    y[0] = A[0][n]/I[0][0];
	for(i=1 ; i<n ; i++){
		sum=0;
		for(j=0 ; j<i ; j++)
            sum += y[j]*I[i][j];
        y[i] = (A[i][n]-sum)/I[i][i];
    }

	//system solution for (I^-1)x=y
    x[n-1] = y[n-1]/I_inv[n-1][n-1];
	for(i=n-2 ; i>=0 ; i--){
		sum=0;
		for(j=i+1 ; j<n ; j++)
            sum += x[j]*I_inv[i][j];
        x[i] = (y[i]-sum)/I_inv[i][i];
    }
	
	printf("\nMatrix A with vector b in last column :\n");
	for(i=0 ; i<n ; i++, printf("\n"))
		for (j=0 ; j<n+1 ; j++)
			printf("%10.2lf", A[i][j]);

	printf("\n\nMatrix I:\n");
	for(i=0 ; i<n ; i++, printf("\n"))
		for(j=0 ; j<n ; j++)
			printf("%7.2lf", I[i][j]);			

	printf("\n\nMatrix I^-1:\n");
	for(i=0 ; i<n ; i++, printf("\n"))
		for(j=0 ; j<n ; j++)
			printf("%7.2lf", I_inv[i][j]);
						
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

	A_inverted = Cholesky_inverted(A, A_inverted, n, 1, 0);
	normA_inverted = maxMatrixNorm(A_inverted, n);
	//printf("normA : %lf\n", normA);
	//printf("normA_inverted : %lf\n", normA_inverted);
	printf("Condition number of A matrix : %lf\n", normA*normA_inverted);

	gettimeofday(&t2, NULL);

    cputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    cputime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	printf("\n\nExecution of Cholesky method for linear system Ax = b resolution ended...\n");
	printf("Execution time of Cholesky system : %.4lf ms\n\n", cputime);

    for(i=0 ; i<n ; i++){
		free(I[i]);
		free(I_inv[i]);
		free(A[i]);
    }
    free(I);
	free(A);
    free(I_inv);
    free(x);
    free(X);
    free(y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** Cholesky_inverted(double **A, double **A_inverted, int n, int is_inverted, int random){
//computation of A^-1 with Cholesky method(with partial pivoting)

	double **I, **I_inv, *x, **y, *z, *b, **A_inverted_local;
	double sum, normA, normA_inverted;
	double cputime;
    struct timeval t1, t2;
	int i,j,k;


	b = (double*)malloc(n*sizeof(double));
	z = (double*)malloc(n*sizeof(double));
	x = (double*)malloc(n*sizeof(double));
	I = allocateMatrix(n,n);
	I_inv = allocateMatrix(n,n);
	A_inverted_local = allocateMatrix(n,n);

	for(k=0 ; k<n ; k++)
		b[k]=0;


	gettimeofday(&t1, NULL);
	printf("\n\nExecution of Cholesky method to compute A^-1 matrix started...\n\n");
	

	for(k=0 ; k<n ; k++){
		b[k]=1;

		Cholesky_factorizationMethod(A,&I,&I_inv,n);

		//system solution for Iz=b
		z[0] = b[0]/I[0][0];
		for(i=1 ; i<n ; i++){
			sum=0;
			for(j=0 ; j<i ; j++)
				sum += z[j]*I[i][j];
			z[i] = (b[i]-sum)/I[i][i];
		}

		//system solution for (I^-1)x=z
		x[n-1] = z[n-1]/I_inv[n-1][n-1];
		for(i=n-2 ; i>=0 ; i--){
			sum=0;
			for(j=n-1 ; j>i ; j--)
				sum += x[j]*I_inv[i][j];
			x[i]=(z[i]-sum)/I_inv[i][i];
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
				printf("%10.2lf", A[i][j]);

		printf("\n\nMatrix A^-1 :\n");
		for(i=0 ; i<n ; i++, printf("\n"))
			for(j=0 ; j<n ; j++)
				printf("%10.2lf", A_inverted_local[i][j]);

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
				\nof A*B = A*A^-1 so that we can proove that method Cholesky worked well. We can reach to this conclusion if the \
				\nprinted A*B is the unit matrix(I).\n");
	}

	gettimeofday(&t2, NULL);

    cputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    cputime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	printf("\n\nExecution of Cholesky method to compute A^-1 matrix ended...\n");
	printf("Execution time of Cholesky to compute A^-1 : %.4lf ms\n\n", cputime);


	for(i=0 ; i<n ; i++){
		free(I[i]);
		free(I_inv[i]);
	}
	free(I);
	free(I_inv);
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

void Cholesky_factorizationMethod(double **A, double ***I, double ***I_inv, int n){				//error occures in here!!!!!!!!!!!!!!!!
//algorithm of Cholesky for factorizing matrix A

	double sum=0.0;
	int i, j, p;

	//	printf("\n\nMatrix I initialization...");
	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++){
			(*I)[i][j]=0;
			(*I_inv)[i][j]=0;
		}
			
//step 2 - computation of 1st matrix I element 
	(*I)[0][0] = (double)sqrt(A[0][0]);
	//	printf("\n\n(*I)[0][0] = %5.2lf\t", (*I)[0][0]);

//step 3 - computation of first column of I
	for(i=1 ; i<n ; i++)
		(*I)[i][0] = A[i][0]/(*I)[0][0];

//step 4 - computation of the rest matrix	
	for(i=1 ; i<n-1 ; i++){
		for(j=0 ; j<i ; j++)
			sum += (double)pow((*I)[i][j], (double)2.0);
		(*I)[i][i] = (double)sqrt(A[i][i]-sum);
		//printf("++(*I)[%d][%d]= %lf++",i,i,(*I)[i][i]);

		sum=0.0;
		for(p=i+1 ; p<n ; p++){
			for(j=0 ; j<i ; j++)
				sum += (double)((*I)[p][j]*(*I)[i][j]);
			(*I)[p][i] = (double)(A[p][i]-sum)/(double)(*I)[i][i];
			sum=0.0;
			//	printf("--(*I)[%d][%d]= %lf--",p,i,(*I)[p][i]);
		}
		
		//the rest i<j are 0
		for(j=0 ; j<i ; j++)
            (*I)[j][i] = 0.0;
	}

//step 5
	for(j=0 ; j<n-1 ; j++)
		sum += (double)pow((*I)[n-1][j], (double)2.0);
	(*I)[n-1][n-1] = (double)sqrt(A[n-1][n-1]-sum);

	//the below for can be omited but i use it in case that something wrong happened in initialization	
	for(j=0 ; j<n-1 ; j++)
        (*I)[j][n-1] = 0.0;		

	//I^-1	
	for(i=0 ; i<n ; i++)
		for(j=0 ; j<n ; j++)
			(*I_inv)[j][i] = (*I)[i][j];
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
		//(fabs(x[i])>max)?max=fabs(x[i]):NULL;		//i didn't do this with this way because NULL showed problems in case of Moler's matrix
		if(fabs(x[i])>max)
			max=fabs(x[i]);
		
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
