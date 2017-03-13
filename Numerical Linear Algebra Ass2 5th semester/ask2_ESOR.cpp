/***************************************************************************************************************************
* University/Faculty	: National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor	: Numerical Linear Algebra - Tzaferis Filippos
* File name				: ask2_ESOR.cpp
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
double ** pentaMatrix_5X5(int*, double**);
double ** pentaMatrix_10X10(int*, double**);
double ** pentaMatrix_NXN(int*, double**);

double ** randomInput_A(int*);
double * randomInput_X(int);

double ** fileInput_Axb(int*, double**);

int ESOR_menu();
void ESOR(double**, double*, int);

double ** allocateMatrix(int, int);
double sign();
void ESOR_iterativeMethod(double **, double **, int, double, double, int, int *);



//srand(time(NULL));

int main(int argc, char* argv[]){
//main of ask2_ESOR.cpp

	int back2menu, n;
	double **A, *X;

	printf("\nLINEAR SYSTEM RESOLUTION OF Ax = b SYSTEMS USING ESOR ITERATIVE METHOD\n");

	while(1){

		back2menu = 0;

		switch(menu()){
			case 1:	A = userInput_A(&n);
					X = userInput_X(n);
					break;

			case 2: switch(list_specificMatrices()){
						case 1:	A = pentaMatrix_5X5(&n, &X);
								break;
						case 2:	A = pentaMatrix_10X10(&n, &X);
								break;
						case 3:	A = pentaMatrix_NXN(&n, &X);
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
					\n\tFOR SYSTEMS OF TYPE Ax = b USING THE ESOR ITERATIVE METHOD. \
					\n\n\tREGARDS NIKOLAOS BEGETIS UNDERGRADUATE STUDENT OF DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS, UNIVERSITY OF ATHENS \
					\n\n\t2011-2012\n");
					return 0;

			default:break;
		}
	if(back2menu!=1)
		ESOR(A, X, n);
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
		\n\t1. User Input: you are about to insert the A pentadiagonial matrix and the b vector directly from keyboard \
		\n\t2. Use specific pentadiagonial matrices: you are about to switch from a list of given matrices \
		\n\t3. Use ramdom pentadiagonial matrices: you are about to select only the size of the pentadiagonial matrix you want and the matrix will be generated randomly \
		\n\t4. File input: you are about to give a text file with your pentadiagonial matrices in it. The file name must have the name:'ask2_ESOR.txt' \
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

    printf("Give pentadiagonial matrix[NXN] dimension N : ");
    scanf("%d",n);

    A = allocateMatrix(*n, *n+1);		//the one more column represents the b vector. this allowance has effect in the whole written program

    printf("\nInsert A pentadiagonial matrix data below:\n");
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

	printf("\nGive vector X data below (e.g (1,1,1,1,1)^T for a 5X5 pentadiagonial matrix) :\n");
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
		\nSwitch the specific matrix to solve a linear system as given from exercise ask2_ESOR: \
		\n\t1. Pentadiagonial matrix of dimensions 5X5 (adjustment 1.i) \
		\n\t2. Pentadiagonial matrix of dimensions 10X10 (adjustment 1.ii) \
		\n\t3. Pentadiagonial matrix of dimensions NXN, where N, a, b, c and d given by you with values 100,1000,10000(for N) and 0.1-1.9(for each of a,b,c,d), and system solution: x=(1,1,...,1,1)^T (adjustment 2) \
		\n\n\t4. Select if you want to return to MAIN MENU.\n");
		printf("INPUT : ");
		scanf("%d", &matrix_no);
	}while((matrix_no<1)||(matrix_no>4));
	return matrix_no;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** pentaMatrix_5X5(int *n, double **X){
//returns a specific matrix (adjustment 1.i)

    double **A;

	*n=5;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=4;		A[0][1]=-0.3;	A[0][2]=-0.4;	A[0][3]=0;		A[0][4]=0;		A[0][5]=3.3;
    A[1][0]=-0.2;	A[1][1]=4;		A[1][2]=-0.3;	A[1][3]=-0.4;	A[1][4]=0;		A[1][5]=3.1;
    A[2][0]=-0.1;	A[2][1]=-0.2;	A[2][2]=4;		A[2][3]=-0.3;	A[2][4]=-0.4;	A[2][5]=3;
    A[3][0]=0;		A[3][1]=-0.1;	A[3][2]=-0.2;	A[3][3]=4;		A[3][4]=-0.3;	A[3][5]=3.4;
    A[4][0]=0;		A[4][1]=0;		A[4][2]=-0.1;	A[4][3]=-0.2;	A[4][4]=4;		A[4][5]=3.7;
	//on the above matrix the indexes in the abs(i-j)=0 places are 4, those with (abs(i-j)=1 and i>j) are l=-b=-0.2, those with (abs(i-j)=1 and i<j) are r=-c=-0.3, those with (abs(i-j)=2 and i>j) are k=-a=-0.1 and finally those with (abs(i-j)=2 and i<j) are s=-d=-0.4
	//so as it is asked in the assignement a=0.1, b=0.2, c=0.3 and d=0.4
	//also on the above vector b[i] cause of x=(1,1,...,1)^T = a[i]+b[i]+diag[i]+c[i]+d[i] = -(k[i]+l[i]+d[i]+r[i]+s[i])

    *X = (double*)malloc(*n*sizeof(double));
    (*X)[0]=1;	(*X)[1]=1;	(*X)[2]=1;	(*X)[3]=1;	(*X)[4]=1;

    return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** pentaMatrix_10X10(int *n, double **X){
//returns a specific matrix (adjustment 1.ii)

    double **A;

	*n=10;

    A = allocateMatrix(*n, *n+1);			//the one more column corresponds to the b vector

    A[0][0]=4;		A[0][1]=-0.2;	A[0][2]=-0.1;	A[0][3]=0;		A[0][4]=0;		A[0][5]=0;		A[0][6]=0;		A[0][7]=0;		A[0][8]=0;		A[0][9]=0;		A[0][10]=3.7;
    A[1][0]=-0.3;	A[1][1]=4;		A[1][2]=-0.2;	A[1][3]=-0.1;	A[1][4]=0;		A[1][5]=0;		A[1][6]=0;		A[1][7]=0;		A[1][8]=0;		A[1][9]=0;		A[1][10]=3.4;
    A[2][0]=-0.4;	A[2][1]=-0.3;	A[2][2]=4;		A[2][3]=-0.2;	A[2][4]=-0.1;	A[2][5]=0;		A[2][6]=0;		A[2][7]=0;		A[2][8]=0;		A[2][9]=0;		A[2][10]=3;
    A[3][0]=0;		A[3][1]=-0.4;	A[3][2]=-0.3;	A[3][3]=4;		A[3][4]=-0.2;	A[3][5]=-0.1;	A[3][6]=0;		A[3][7]=0;		A[3][8]=0;		A[3][9]=0;		A[3][10]=3;
    A[4][0]=0;		A[4][1]=0;		A[4][2]=-0.4;	A[4][3]=-0.3;	A[4][4]=4;		A[4][5]=-0.2;	A[4][6]=-0.1;	A[4][7]=0;		A[4][8]=0;		A[4][9]=0;		A[4][10]=3;
    A[5][0]=0;		A[5][1]=0;		A[5][2]=0;		A[5][3]=-0.4;	A[5][4]=-0.3;	A[5][5]=4;		A[5][6]=-0.2;	A[5][7]=-0.1;	A[5][8]=0;		A[5][9]=0;		A[5][10]=3;
    A[6][0]=0;		A[6][1]=0;		A[6][2]=0;		A[6][3]=0;		A[6][4]=-0.4;	A[6][5]=-0.3;	A[6][6]=4;		A[6][7]=-0.2;	A[6][8]=-0.1;	A[6][9]=0;		A[6][10]=3;
    A[7][0]=0;		A[7][1]=0;		A[7][2]=0;		A[7][3]=0;		A[7][4]=0;		A[7][5]=-0.4;	A[7][6]=-0.3;	A[7][7]=4;		A[7][8]=-0.2;	A[7][9]=-0.1;	A[7][10]=3;
    A[8][0]=0;		A[8][1]=0;		A[8][2]=0;		A[8][3]=0;		A[8][4]=0;		A[8][5]=0;		A[8][6]=-0.4;	A[8][7]=-0.3;	A[8][8]=4;		A[8][9]=-0.2;	A[8][10]=3.1;
    A[9][0]=0;		A[9][1]=0;		A[9][2]=0;		A[9][3]=0;		A[9][4]=0;		A[9][5]=0;		A[9][6]=0;		A[9][7]=-0.4;	A[9][8]=-0.3;	A[9][9]=4;		A[9][10]=3.3;
	//on the above matrix the indexes in the abs(i-j)=0 places are 4, those with (abs(i-j)=1 and i>j) are l=-b=-0.3, those with (abs(i-j)=1 and i<j) are r=-c=-0.2, those with (abs(i-j)=2 and i>j) are k=-a=-0.4 and finally those with (abs(i-j)=2 and i<j) are s=-d=-0.1
	//so as it is asked in the assignement a=0.4, b=0.3, c=0.2 and d=0.1
	//also on the above vector b[i] cause of x=(1,1,...,1)^T = a[i]+b[i]+diag[i]+c[i]+d[i] = -(k[i]+l[i]+d[i]+r[i]+s[i])

    *X = (double*)malloc(*n*sizeof(double));

    (*X)[0]=1;	(*X)[1]=1;	(*X)[2]=1;	(*X)[3]=1;	(*X)[4]=1;	(*X)[5]=1;	(*X)[6]=1;	(*X)[7]=1; (*X)[8]=1; (*X)[9]=1;

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** pentaMatrix_NXN(int *n, double **X){
//returns a specific matrix (adjustment 2)

	double **A, a, b, c, d;					//where  -a=k, -b=l, -c=r, -d=s
	int i, j;

	printf("Give pentadiagonial matrix[NXN] dimension N(e.g. 100,1000,10000) : ");
	scanf("%d",n);
	printf("Now give the matrix parameters a, b, c, d respectively in this order with a, b, c, d in 0.1(0.1)1.9 (e.g. a=1.2, b=0.9, c=0.6, d=0.3) :\n");
	printf("a = ");
	scanf("%lf", &a);
	printf("b = ");
	scanf("%lf", &b);
	printf("c = ");
	scanf("%lf", &c);
	printf("d = ");
	scanf("%lf", &d);

	*X = (double*)malloc(*n*sizeof(double));

	A = allocateMatrix(*n,*n+1);			//the one more column corresponds to the b vector

	//values for matrix A
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++)
			switch(abs(i-j)){
				case 0:	A[i][j]=4;
						break;

				case 1: (i>j)?A[i][j]=-b : A[i][j]=-c;
						break;

				case 2: (i>j)?A[i][j]=-a : A[i][j]=-d;
						break;

				default:A[i][j]=0.0;
						break;
			}

	//values for X
	for(i=0 ; i<*n ; i++)
		(*X)[i]=1;

	//b computation
	for(i=0 ; i<*n ; i++){
		A[i][*n] = 0;					//initializes into zero all the values of b vector
		for(j=0 ; j<*n ; j++)
			A[i][*n] += A[i][j]*(*X)[j];
			//the above vector b cause of x=(1,1,...,1)^T means b[i] = a[i]+b[i]+diag[i]+c[i]+d[i] = -(k[i]+l[i]+d[i]+r[i]+s[i])
	}

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ** randomInput_A(int *n){
//data of matrix A are randomly selected and inserted (adjustment 3)

	srand(time(NULL));


	double **A,k,l,r,s,values,diag_value,mult;	//where  k=-a, l=-b, r=-c, s=-d
    int i,j,case_values;

    printf("Give pentadiagonial matrix[NXN] dimension N(e.g. 100,1000,10000)  : ");
    scanf("%d",n);

	//values for parameters of matrix A
	values = 0.1+(0.1*(double)(rand()%19));						//desirable values of parameters a,b,c,d between [0.1,1.9]
	case_values = (int)(values*10);
	diag_value = (sign()*(4.0+(double)((rand()%385)/4)))-1;		//desirable values of diagonial between [-100,-4] or [4,100] all multiplies of 4(-100,...,-4,4,8,12,...,100)

	switch(case_values){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
				mult = 0.1*(1.0+(double)(rand()%4));
				k = sign()*values;
				l = sign()*(k+mult);
				r = sign()*(k+2.0*mult);
				s = sign()*(k+3.0*mult);
				break;

		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
				mult = 0.1*(1.0+(double)(rand()%3));
				k = sign()*values;
				l = sign()*(k+mult);
				r = sign()*(k+2.0*mult);
				s = sign()*(k+3.0*mult);
				break;

		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
				mult = 0.1*(1.0+(double)(rand()%3));
				s = sign()*values;
				r = sign()*(s-mult);
				l = sign()*(s-2.0*mult);
				k = sign()*(s-3.0*mult);
				break;

		case 16:
		case 17:
		case 18:
		case 19:
				mult = 0.1*(1.0+(double)(rand()%4));
				s = sign()*values;
				r = sign()*(s-mult);
				l = sign()*(s-2.0*mult);
				k = sign()*(s-3.0*mult);
				break;

		default:break;
	}

	printf("\n\n\nPentadiagonial matrix parameters selected as follows: \
			\nk=%2.1lf, l=%2.1lf, d=%2.1lf, r=%2.1lf, s=%2.1lf\n\n\n",k,l,diag_value,r,s);
	//printf("\n\n\n\n\nk=%lf, l=%lf, d=%lf, r=%lf, s=%lf, values=%lf, case_values=%d, mult=%lf\n\n\n\n\n",k,l,diag_value,r,s,values,case_values,mult);

	A = allocateMatrix(*n, *n+1);							//the one more column corresponds to the b vector

	//values for matrix A
	for(i=0 ; i<*n ; i++)
		for(j=0 ; j<*n ; j++)
			switch(abs(i-j)){
				case 0:	A[i][j]=diag_value;
						break;

				case 1: (i>j)?A[i][j]=l : A[i][j]=r;
						break;

				case 2: (i>j)?A[i][j]=k : A[i][j]=s;
						break;

				default:A[i][j]=0.0;
						break;
			}

	//randomly selected data for b vector below so that X is (1,1,...,1,1)^T
	for(i=0 ; i<*n ; i++){
			A[i][*n]=0.0;									//initializes into zero all the values of b vector
			for(j=0 ; j<*n ; j++)
				A[i][*n] += A[i][j];
				//the above vector b cause of x=(1,1,...,1)^T means b[i] = a[i]+b[i]+diag[i]+c[i]+d[i] = -(k[i]+l[i]+d[i]+r[i]+s[i])
	}

	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double * randomInput_X(int n){
//data of matrix X are randomly selected and inserted (adjustment 3)

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
//data of matrix A and vectors x and b are inserted from file(optional adjustment)
//on the above inserted matrix the indexes in the abs(i-j)=0 places are 4, those with (abs(i-j)=1 and i>j) are l=-b=-0.3, those with (abs(i-j)=1 and i<j) are r=-c=-0.2, those with (abs(i-j)=2 and i>j) are k=-a=-0.4 and finally those with (abs(i-j)=2 and i<j) are s=-d=-0.1

	double **A;
	int i,j;
	FILE *file;

	if((file=fopen("ask2_ESOR.txt", "r"))==NULL){
		perror("FILE ERROR : Either the file with name 'ask2_ESOR.txt' does not exist or it is placed in a wrong directory");
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

void ESOR(double **A, double *x, int n){
//linear system resolution of Ax=b with ESOR iterative method

//	double *x;
	double t, w, cputime, itcputime, best_cputime;
    struct timeval t1, t2, t3, t4;
	int i, j, itmax,min_itcount=0,itcount=0;


//	x = (double*)malloc(n*sizeof(double));

	printf("Give the maximum number of iterations that you want to be applied so that a system solution will be computed \
			\n Suggestion : If you type a big number(e.g. 500) probably you will find a solution, but you will lack in time \
			\n(e.g. if you chose a 5X5 matrix and you are about to choose t=0.1 & w=0.4 type 200, if t=0.1 & w=0.1 type 10) : ");
	scanf("%d", &itmax);

	switch(ESOR_menu()){
		case 1:	printf("Now give the t and w parameters respectively in this order with t, w in 0.1(0.1)1.9 (e.g. t=0.1, w=0.4) :\n");
				printf("t = ");
				scanf("%lf", &t);
				printf("w = ");
				scanf("%lf", &w);

				gettimeofday(&t1, NULL);
				printf("\n\nExecution of ESOR method for linear system Ax = b resolution started...\n\n");

				ESOR_iterativeMethod(A, &x, n, t, w, itmax, &itcount);

				gettimeofday(&t2, NULL);
				printf("\n\nExecution of ESOR iterative method for linear systems Ax = b resolution ended...\n");

				cputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
				cputime += (t2.tv_usec - t1.tv_usec) / 1000.0;

				(itcount < itmax) ? printf("\nAPPROXIMATE LINEAR SOLUTION FOR THE PENTADIAGONIAL MATRIX FOUND WITH PARAMETERS t=%2.1lf AND w=%2.1lf AFTER %d ITERATIONS\n", t, w, itcount) :
									printf("\nAPPROXIMATE LINEAR SOLUTION FOR THE PENTADIAGONIAL MATRIX WAS NOT FOUND AMONG %d ITERATIONS WITH PARAMETERS t=%2.1lf AND w=%2.1lf. LAST APPROXIMATE SOLUTION WILL BE PRINTED.\n", itmax, t, w);

				printf("\nMatrix A with vector b in last column :\n");
				for(i=0 ; i<n ; i++, printf("\n"))
					for (j=0 ; j<n+1 ; j++)
						printf("%7.1lf", A[i][j]);

				printf("\n\nLINEAR SYSTEM SOLUTION :\n");
				printf("\tx = ( ");
				for(i=0 ; i<n-1 ; i++)
					printf("%7.3lf, ", x[i]);
				printf("%7.3lf )^T\n\n", x[n-1]);

				printf("\nExecution time of ESOR system : %.4lf ms\n\n", cputime);

				break;

		case 2:	double t_optimal, w_optimal;

		printf("The parameters t and w are iteratively selected in range [0.1, 1.9] in oder to find the optimal values of t and w\n");
				printf("\n\nExecution of ESOR method for linear system Ax = b resolution with all the values of t and w in range started...\n\n");

				for(t=0.1 ; t<2.0 ; t+=0.1)
					for(w=0.1 ; w<2.0 ; w+=0.1){
						itcputime = 0.0;
						gettimeofday(&t1, NULL);
						ESOR_iterativeMethod(A, &x, n, t, w, itmax, &itcount);
						gettimeofday(&t2, NULL);

						itcputime = (t2.tv_sec - t1.tv_sec) * 1000.0;
						itcputime += (t2.tv_usec - t1.tv_usec) / 1000.0;
						cputime += itcputime;

						if((itcount < min_itcount) || (t==0.1 && w==0.1)){				//printing each time only when a better solution is found
							min_itcount = itcount;
							t_optimal = t;
							w_optimal = w;

							printf("BETTER PARAMETERS FOUND! \
							\nThe best parameters until this iterations are t_optimal = %2.1lf and w_optimal = %2.1lf\n", t_optimal, w_optimal);
						}
						itcount = 0;
					}

				printf("\nExecution of ESOR iterative method for linear systems Ax = b resolution with all the values of t and w in range ended...\n");

				(min_itcount < itmax) ? printf("\nAPPROXIMATE LINEAR SOLUTION FOR THE PENTADIAGONIAL MATRIX FOUND WITH OPTIMAL PARAMETERS t_optimal=%2.1lf AND w_optimal=%2.1lf AFTER %d ITERATIONS\n", t_optimal, w_optimal, min_itcount) :
										printf("\nAPPROXIMATE LINEAR SOLUTION FOR THE PENTADIAGONIAL MATRIX WAS NOT FOUND AMONG %d ITERATIONS WITH BEST PARAMETERS t_optimal=%2.1lf AND w_optimal=%2.1lf. LAST APPROXIMATE SOLUTION WILL BE PRINTED.\n", itmax, t_optimal, w_optimal);

				gettimeofday(&t3, NULL);
				ESOR_iterativeMethod(A, &x, n, t_optimal, w_optimal, itmax, &min_itcount);
				gettimeofday(&t4, NULL);

				best_cputime = (t4.tv_sec - t3.tv_sec) * 1000.0;
				best_cputime += (t4.tv_usec - t3.tv_usec) / 1000.0;


				printf("\nMatrix A with vector b in last column :\n");
				for(i=0 ; i<n ; i++, printf("\n"))
					for (j=0 ; j<n+1 ; j++)
						printf("%7.1lf", A[i][j]);

				printf("\n\nLINEAR SYSTEM SOLUTION :\n");
				printf("\tx = ( ");
				for(i=0 ; i<n-1 ; i++)
					printf("%7.3lf, ", x[i]);
				printf("%7.3lf )^T\n\n", x[n-1]);

				printf("The optimal t parameter is : %2.1lf\n", t_optimal);
				printf("The optimal w parameter is : %2.1lf\n", w_optimal);
				printf("The number of iterations executed with the optimal parameters t and w is : %d\n", min_itcount);
				printf("\nExecution of ESOR method for linear system Ax = b resolution with all the values of t and w in range took : %.4lf ms\n\n", cputime);
				printf("\nExecution time of ESOR system with the minimum number of iterations took : %.4lf ms\n\n", best_cputime);
				break;

		case 3:	printf ("\n\n\tHOPE THAT YOU ENJOYED USING MY PROGRAM FOR FINDING LINEAR SYSTEM SOLUTIONS \
					\n\tFOR SYSTEMS OF TYPE Ax = b USING THE ESOR ITERATIVE METHOD. \
					\n\n\tREGARDS NIKOLAOS BEGETIS UNDERGRADUATE STUDENT OF DEPARTMENT OF INFORMATICS AND TELECOMMUNICATIONS, UNIVERSITY OF ATHENS \
					\n\n\t2011-2012\n");
				exit(0);			//not return 0..
	}

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

int ESOR_menu(){
//main menu

	int menuSelection;
	do{
		printf ("IMPLEMENTATION MENU \
		\nSwitch how you want to use the ESOR iterative method: \
		\n\t1. Experimental verification of correctness of ESOR algorithm for resolution of the linear system Ax=b with x given x=(1,1,...,1)^T \
		\n\t2. Experimental study of convergence of the ESOR iterative method with t, w given in [0.1, 1.9] with step 0.1 \
		\n\t3. Select if you want to quit.\n");
		printf("INPUT: ");
		scanf("%d", &menuSelection);
	}while((menuSelection<1)||(menuSelection>3));
	return menuSelection;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ESOR_iterativeMethod(double **A, double **x1, int n, double t, double w, int itmax, int *itcount){
//algorithm of ESOR for factorizing matrix A in L and U using partial pivoting

	long double e = 0.0000005;
	double *x0, *k, *l, *d, *r, *s, approximation;
	int i, j;


	//xo, k, l, d, r, s matrix allocations
	x0 = (double*)malloc(n*sizeof(double));
	k = (double*)malloc(n*sizeof(double));
	l = (double*)malloc(n*sizeof(double));
	d = (double*)malloc(n*sizeof(double));
	r = (double*)malloc(n*sizeof(double));
	s = (double*)malloc(n*sizeof(double));

	//initialization of x0, k, l, r, s
	for(i=0 ; i<n ; i++){
			x0[i] = 0;
			k[i] = 0;
			l[i] = 0;
			d[i] = 0;
			r[i] = 0;
			s[i] = 0;
	}

	//x0, k, l, d, r, s assignements
	for(i=0 ; i<n ; i++){
		x0[i] = A[i][n];
		for(j=0 ; j<n ; j++)
			switch(abs(i-j)){
				case 0:	d[i] = A[i][j];
						break;

				case 1: (i>j)?l[i]=A[i][j] : r[i]=A[i][j];
						break;

				case 2: (i>j)?k[i]=A[i][j] : s[i]=A[i][j];
						break;

				default:break;
			}
	}

	while((*itcount) < itmax){
		approximation = 0.0;

		//step B4.1 - compute values of x1
		for(i=0 ; i<n ; i++)
			(*x1)[i] = (1.0-t)*x0[i] - w*((k[i]/d[i])*(*x1)[i-2]+(l[i]/d[i])*(*x1)[i-1]) -
					(t-w)*((k[i]/d[i])*x0[i-2]+(l[i]/d[i])*x0[i-1]) -
					t*((r[i]/d[i])*x0[i+1]+(s[i]/d[i])*x0[i+2]-(A[i][n]/d[i]));

		//step B4.2 - increment of iterations' count
		(*itcount)++;

		for(i=0 ; i<n ; i++)
			if(fabs((*x1)[i]-x0[i])>approximation)
				approximation=fabs((*x1)[i]-x0[i]);

		if(approximation < e)
		//step B4.3 - check if approximation is less than desired accuracy and if yes stop method
			break;
		else
		//step B4.4 - assign x1 to x0 to aprroximate better in next iteration
			for(i=0 ; i<n ; i++)
				x0[i] = (*x1)[i];
	}
	free(x0);
    free(k);
    free(l);
    free(d);
    free(r);
    free(s);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

