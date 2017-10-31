#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

//*****************************************************************************
//P R O G R A M  H E A D E R
//  Name:  Muhammad Saim
//	Z#:  23306519
//	Instructor:  Dr. Cardei
//	Class:  Design and Analysis of Algorithms
//	Term:  Fall 2017
//	Algorithm Project
//	Due Date:   October 30,2017
//	Due Time:  11:59PM
//	Points:  90
//	
//  Description: This program sorts arrays of different number of elements. Each 
//	    variation in elements in the array are tested 10 times and the average of
//		the ten is recorded to the screen. This is done to test the run times of 
//      INSERTION_SORT, MERGE_SORT, and QUICKSORT to see how they compare against 
//      each other and the theoretical values.
//******************************************************************************

void INSERTION_SORT(int A[],int A_length);
void MERGE_SORT(int B[], int p, int r);
void MERGE(int B[], int p, int q, int r);
void QUICKSORT(int C[], int p, int r);
int PARTITION(int C[], int p, int r);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: INSERTION_SORT
//Precondition: The unsorted array and size of the array has been passed to the function
//Postcondition: The array has been sorted.
//Description: Insertion sort is a sorting algorithm that transfers the elements one at a time to the right position.
//    It builds the final list one at a time, with the movement of the higher-ranked element.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void INSERTION_SORT(int A[], int A_length) {
	int i, key, j;

	for (j = 1; j<=A_length; j++) {
		key = A[j];
		i = j - 1;

		while (i>-1 && A[i]>key) {
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: MERGE_SORT
//Precondition: The unsorted array, intial position and final position of the array has been passed to the function
//Postcondition: The array has been sorted using divide and conquer
//Description: Merge Sort is a Divide and Conquer algorithm. It divides an input array into two halves and 
//    recursively calls itself for the two halves. The array is recursively divided in two halves until the size 
//    becomes 1. Then the merge function starts merging the arrays back until the array is merged completely
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MERGE_SORT(int B[], int p, int r) {
	int q=1;
	if (p < r) {
		q = (p + r) / 2;
		q = floor(q);
		MERGE_SORT(B, p, q);
		MERGE_SORT(B, q + 1, r);
		MERGE(B, p, q, r);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: MERGE
//Precondition: The array, intial, final, and divided positions are passed to the function.
//Postcondition: The array has been merged together.
//Description: The merge function is used for merging two halves together.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MERGE(int B[], int p, int q, int r) {	
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];

	for (int i = 0; i <= n1; i++) {
		L[i] = B[p + i - 1];
	}
	for (int j = 0; j <= n2; j++) {
		R[j] = B[q + j];
	}

	L[n1 + 1] = 99999;
	R[n2 + 1] = 99999;
	
	int i = 1;
	int j = 1;

	for (int k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			B[k] = L[i];
			i = i + 1;
		}
		else {
			B[k] = R[j];
			j = j + 1;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: QUICKSORT
//Precondition: The unsorted array, intial, and final positions has been passed to the function
//Postcondition: The array has been sorted.
//Description:  QuickSort is a Divide and Conquer algorithm. The algorithm selects an element as pivot and partitions the 
//    array around the pivot.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void QUICKSORT(int C[], int p, int r) {
	if (p < r) {
		int q = PARTITION(C, p, r);
		QUICKSORT(C, p, q - 1);
		QUICKSORT(C, q + 1, r);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: PARTITION
//Precondition: The array, intial, and final positions has been passed to the function
//Postcondition: The array has been 
//Description:  Partition selects the last element as the pivot and orders the array by having all the elements 
//    smaller than the pivot to the left and all the elements larger than the pivot on the right.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PARTITION(int C[], int p, int r) {
	int pivot = C[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (C[j] <= pivot) {
			i = i + 1;
			int temp = C[i];
			C[i] = C[j];
			C[j] = temp;
		}
	}
	int temp2 = C[i + 1];
	C[i + 1] = C[r];
	C[r] = temp2;
	return (i+1);
}

int main() {
	//used to format the output
	cout.setf(ios::fixed);
	cout.precision(1);

	//number of times array is sorted
	const int m = 10;
	//total number of elements in array
	const int nf = 100000;
	//start amount for the number of elements in array
	const int ns = 5000;
	//incrementing the array size
	const int sigma = 5000;

	//dynamic arrays used for the program
	int **A = new int*[m];
	for (int i = 0; i <= m-1; i++) {
		A[i] = new int[nf];
	}

	int *B = new int[nf];
	int *C = new int[nf];
	int *D = new int[nf];
	
	double **talg1 = new double*[m];
	for (int j = 0; j <= m-1; j++) {
		talg1[j] = new double[nf];
	}
	double **talg2 = new double*[m];
	for (int k = 0; k <= m - 1; k++) {
		talg2[k] = new double[nf];
	}
	double **talg3 = new double*[m];
	for (int j = 0; j <= m - 1; j++) {
		talg3[j] = new double[nf];
	}

	//used for the average run times
	double tavgalg = 0;
	double tavgAlgArray[nf];
	
	//fills array A with random values 
	for (int i = 0; i <= m-1; i++) {
		for (int j = 0; j <= nf-1; j++) {
			A[i][j] = rand();
		}
	}

	//runs INSERTION_SORT
	//starts at 5000 element arrays and increments by 5000
	for (int n = ns; n <= nf; n = n + sigma) {
		
		//runs each variation 10 times
		for (int i = 0; i <= m-1; i++) {
		
			//stores the value of the specific A array in B
			for (int k = 0; k <= n-1; k++) {
				B[k] = A[i][k];
			}
			
			//records start time
			auto t1 = chrono::steady_clock::now();
			
			INSERTION_SORT(B, n - 1);
			
			//records end time
			auto t2 = chrono::steady_clock::now();
			
			//computes the difference
			double elapsed_time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
			
			//stores time in array
			talg1[i][n] = elapsed_time;
		}
		
		//adds all the times up
		for (int i = 0; i <= m-1; i++) {
			tavgalg = tavgalg + talg1[i][n];
		}
		
		//divides by 10 to get average
		tavgalg = tavgalg / m;
		tavgAlgArray[n-1] = tavgalg;
		cout << endl << "Avergage Time in Milliseconds to run INSERTION_SORT: " << tavgalg << " for: " << n << endl;
	}
	
	//same for MERGE_SORT
	for (int n = ns; n <= nf; n = n + sigma) {
		for (int i = 0; i <= m - 1; i++) {
			for (int k = 0; k <= n - 1; k++) {
				C[k] = A[i][k];
			}
			auto t1 = chrono::steady_clock::now();
			MERGE_SORT(C, 0, n - 1);
			auto t2 = chrono::steady_clock::now();
			double elapsed_time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
			talg2[i][n] = elapsed_time;
		}
		for (int i = 0; i <= m - 1; i++) {
			tavgalg = tavgalg + talg2[i][n];
		}
		tavgalg = tavgalg / m;
		tavgAlgArray[n-1] = tavgalg;
		cout << endl << "Avergage Time in Milliseconds to run MERGE_SORT: " << tavgalg << " for: " << n << endl;	
	}

	//same for QUICKSORT
	for (int n = ns; n <= nf; n = n + sigma) {
		for (int i = 0; i <= m - 1; i++) {
			for (int k = 0; k <= n - 1; k++) {
				D[k] = A[i][k];
			}
			auto t1 = chrono::steady_clock::now();
			QUICKSORT(D, 0, n - 1);
			auto t2 = chrono::steady_clock::now();
			double elapsed_time = double(chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());
			talg3[i][n] = elapsed_time;
		}
		for (int i = 0; i <= m - 1; i++) {
			tavgalg = tavgalg + talg3[i][n];
		}
		tavgalg = tavgalg / m;
		tavgAlgArray[n-1] = tavgalg;
		cout << endl << "Avergage Time in Milliseconds to run QUICKSORT: " << tavgalg << " for: " << n << endl;
	}

	return 0;
}