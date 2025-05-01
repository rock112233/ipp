#include <iostream>
using namespace std;

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void multiplyMatrix(int** M1, int** M2, int** result, int n, int m) {
	#pragma omp parallel for 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the size of the First matrix: ";
    cin >> n;

    // Dynamically allocate memory for matrix M1
    int** M1 = new int*[n];
    for (int i = 0; i < n; i++) {
        M1[i] = new int[n];
    }

    cout << "Enter the elements of the First matrix: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> M1[i][j];
        }
    }

    int m;
    cout << "Enter the size of the Second matrix: ";
    cin >> m;

    // Dynamically allocate memory for matrix M2
    int** M2 = new int*[m];
    for (int i = 0; i < m; i++) {
        M2[i] = new int[m];
    }

    cout << "Enter the elements of the Second matrix: ";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> M2[i][j];
        }
    }

    if (n != m) {
        cout << "Matrix multiplication is not possible as the dimensions do not match!" << endl;
        return 1;
    }

    // Dynamically allocate memory for the result matrix
    int** result = new int*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[m];
    }

    multiplyMatrix(M1, M2, result, n, m);

    cout << "The product of the two matrices is: " << endl;
    printMatrix(result, n, m);

    // Clean up memory for the result matrix only
    for (int i = 0; i < n; i++) {
        delete[] result[i];
    }
    delete[] result;

    return 0;
}
