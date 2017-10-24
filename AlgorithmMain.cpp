#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

void INSERTION_SORT(int A[],int A_length);
int * MERGE_SORT(int B[], int p, int r);
void MERGE(int B[], int p, int q, int r);
int * QUICKSORT(int C[], int p, int r);
int PARTITION(int C[], int p, int r);
void print(int array[], int numElements, string functionName);

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
	//print(A, A_length, "INSERTION_SORT");
}

int * MERGE_SORT(int B[], int p, int r) {
	int q=1;
	if (p < r) {
		q = (p + r) / 2;
		q = floor(q);
		MERGE_SORT(B, p, q);
		MERGE_SORT(B, q + 1, r);
		MERGE(B, p, q, r);
	}
	return B;
}

void MERGE(int B[], int p, int q, int r) {	
	const int n1 = q - p + 1;
	const int n2 = r - q;
	int *L = new int[n1 - 1];
	int *R = new int[n2 - 1];

	for (int i = 0; i <= n1; i++) {
		L[i] = B[p + i - 1];
	}
	for (int j = 0; j <= n2; j++) {
		R[j] = B[q + j];
	}

	L[n1 + 1] = numeric_limits<int>::max();
	R[n2 + 1] = numeric_limits<int>::max();
	
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

int * QUICKSORT(int C[], int p, int r) {
	if (p < r) {
		int q = PARTITION(C, p, r);
		QUICKSORT(C, p, q - 1);
		QUICKSORT(C, q + 1, r);
	}
	return C;
}

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

void print(int array[], int numElements, string functionName) {
	cout << "inside " << functionName << ": ";
	for (int k = 0; k <= numElements; k++) {
		cout << array[k] << " ";
	}
	cout << endl;
}

int main() {
	cout.setf(ios::fixed);
	cout.precision(1);
	//INSERTION_SORT T(n)=theta(n^2)
	//MERGE_SORT T(n)=theta(nlgn)
	//QUICKSORT worst case RT=theta(n^2) or expected RT=theta(nlgn)
	//partition RT=theta(n)
	//merge RT=theta(n)


	/*int A[] = { 10,9,8,7,6,5,4,3,2,1 };
	int B[] = { 10,9,8,7,6,5,4,3,2,1 };
	int C[] = { 10,9,8,7,6,5,4,3,2,1 };

	int A_length = sizeof(A) / sizeof(*A);

	INSERTION_SORT(A, A_length-1);
	int *bArray = MERGE_SORT(B, 0, A_length - 1);
	int *cArray = QUICKSORT(C, 0, A_length - 1);

	print(bArray, A_length - 1, "MERGE_SORT");
	print(cArray, A_length - 1, "QUICKSORT");*/

	const int m = 10;
	const int nf = 100;
	const int ns = 50;
	int A[m][nf];
	int B[nf];
	double talg1[m][nf];
	double tavgalg1 = 0;
	double tavgAlgArray[nf];

	for (int i = 0; i <= m-1; i++) {
		for (int j = 0; j <= nf-1; j++) {
			A[i][j] = rand();
		}
	}

	for (int n = ns; n <= nf-1; n = n + 5) {
		for (int i = 0; i <= m-1; i++) {
			for (int k = 0; k <= n-1; k++) {
				B[k] = A[i][k];
			}
			auto t1 = chrono::steady_clock::now();
			INSERTION_SORT(B, n-1);
			auto t2 = chrono::steady_clock::now();
			double elapsed_time = double(chrono::duration_cast<chrono::microseconds>(t2 - t1).count());
			talg1[i][n] = elapsed_time;
		}
		for (int i = 0; i <= m-1; i++) {
			tavgalg1 = tavgalg1 + talg1[i][n];
		}
		tavgalg1 = tavgalg1 / m;
		tavgAlgArray[n] = tavgalg1;
		cout << endl << "Avergage Time in Milliseconds to run INSERTION_SORT: " << tavgalg1 << " for: " << n << endl;
	}
	
	/*for (int n = 5; n <= 9; n = n + 5) {
		for (int i = 0; i <= 9; i = i + 1) {
			for (int k = 0; k <= 9; k++) {
				B[k] = A[i][k];
			}
			auto t1 = chrono::steady_clock::now();
			INSERTION_SORT(B, 9);
			auto t2 = chrono::steady_clock::now();
			double elapsed_time = double(chrono::duration_cast<chrono::microseconds>(t2 - t1).count());
			talg1[i] = elapsed_time;
		}
		for (int i = 0; i <= 9; i++) {
			tavgalg1 = tavgalg1 + talg1[i];
		}
		tavgalg1 = tavgalg1 / 10;
		cout << endl << "Avergage Time in Microseconds to run INSERTION_SORT: " << tavgalg1 << endl;
	}*/

	return 0;
}