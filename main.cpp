#include "SparseMatrix.h"
#include <iostream>

int main() {

	SparseMatrix<int, 4, 5> matrix;
	SparseMatrix<int, 6, 4> matrixOther;
	SparseMatrix<int, 4, 4> result;
	matrix.pushElementAtPosition(0, 1, 5);
	matrix.pushElementAtPosition(1, 3, 7);
	matrix.pushElementAtPosition(2, 3, 9);
	matrixOther.pushElementAtPosition(0, 1, 3);
	matrixOther.pushElementAtPosition(1, 1, 2);
	matrixOther.pushElementAtPosition(2, 3, 5);
	std::cout << matrix;
	std::cout << matrixOther;
	result = matrix * matrixOther;
	std::cout << result;

	return 0;
}