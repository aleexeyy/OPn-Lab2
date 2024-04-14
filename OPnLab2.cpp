#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class SparseMatrix {
private:
    int rows;
    int cols;
    double** elements;

public:
    SparseMatrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        elements = new double*[rows];
        for (int i = 0; i < rows; i++) {
            elements[i] = new double[cols];
            fill(elements[i], elements[i] + cols, 0.0);
        }
    }
    ~SparseMatrix() {
        for (int i = 0; i < rows; i++) {
            delete[] elements[i];
        }
        delete[] elements;
    }

    SparseMatrix(const SparseMatrix& other) : rows(other.rows), cols(other.cols) {
        elements = new double*[rows];
        for (int i = 0; i < rows; i++) {
            elements[i] = new double[cols];
            copy(other.elements[i], other.elements[i] + cols, elements[i]);
        }
    }
    double Determinant() {
        if (cols != rows) {
            return 0.0;
        }
        if (cols == 2) {
            return (elements[0][0]*elements[1][1]-elements[0][1]*elements[1][0]);
        }
        if (cols == 3) {
            return (elements[0][0]*elements[1][1]*elements[2][2]+elements[0][1]*elements[1][2]*elements[2][0]+elements[0][2]*elements[1][0]*elements[2][1]) - (elements[0][2]*elements[1][1]*elements[2][0]+elements[0][1]*elements[1][0]*elements[2][2]+elements[0][0]*elements[1][2]*elements[2][1]);
        }
        double det = 0.0;

        for (int i = 0; i < cols; i++) {
            SparseMatrix submatrix(cols - 1, cols - 1);
            for (int j = 1; j < cols; j++) {
                int col = 0;
                for (int k = 0; k < cols; k++) {
                    if (k != i) {
                        submatrix.elements[j-1][col++] = elements[j][k];
                    }
                }
            }

            det += elements[0][i]*pow(-1, i)*submatrix.Determinant();
        }
        return det;
    }
    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this != &other) {
            for (int i = 0; i < rows; i++) {
                delete[] elements[i];
            }
            delete[] elements;

            rows = other.rows;
            cols = other.cols;

            elements = new double*[rows];
            for (int i = 0; i < rows; i++) {
                elements[i] = new double[cols];
                copy(other.elements[i], other.elements[i] + cols, elements[i]);
            }
        }
        return *this;
    }

    SparseMatrix operator+(const SparseMatrix& other) const {
        SparseMatrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.elements[i][j] = elements[i][j] + other.elements[i][j];
            }
        }
        return result;
    }

    SparseMatrix operator*(double scalar) const {
        SparseMatrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.elements[i][j] = elements[i][j] * scalar;
            }
        }
        return result;
    }

    SparseMatrix operator*(const SparseMatrix& other) const {
        SparseMatrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.elements[i][j] += elements[i][k] * other.elements[k][j];
                }
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const SparseMatrix& mat);
    friend istream& operator>>(istream& is, SparseMatrix& mat);
};

ostream& operator<<(ostream& os, const SparseMatrix& mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            os << mat.elements[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, SparseMatrix& mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            is >> mat.elements[i][j];
        }
    }
    return is;
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns: ";
    cin >> rows >> cols;

    SparseMatrix mat1(rows, cols);
    cout << "Enter matrix 1:" << endl;
    cin >> mat1;

    SparseMatrix mat2(rows, cols);
    cout << "Enter matrix 2:" << endl;
    cin >> mat2;

    SparseMatrix sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl << sum << endl;

    double scalar;
    cout << "Enter the scalar factor:" << endl;
    cin >> scalar;
    SparseMatrix scalarProduct = mat1 * scalar;
    cout << "Scalar product of matrix 1 and " << scalar << ":" << endl << scalarProduct << endl;

    SparseMatrix product = mat1 * mat2;
    cout << "Product of matrices:" << endl << product << endl;

    double det1 = mat1.Determinant();
    double det2 = mat2.Determinant();
    cout << "Determinant of matrix1 is " << det1 << endl;
    cout << "Determinant of matrix2 is " << det2 << endl;

    return 0;
}
