// Matrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::vector<int>> mult_matrices(const std::vector<std::vector<int>>& A,
	const std::vector<std::vector<int>>& B);

bool test_mult();


int main()
{
	if (!test_mult()) {
		std::cout << "error\n";
	}
	else {
		std::cout << "correct\n";
	}

}

bool test_mult()
{

	std::vector<std::vector<int>> A = { {1,2}, {3,4 }};
	std::vector<std::vector<int>> B = { {5,6}, {7,8 }};
	std::vector<std::vector<int>> expected = { {19, 22}, {43, 50} };
	const int N = expected.size();

	auto C = mult_matrices(A, B);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (C[i][j] != expected[i][j]) {
				std::cout << "C[" << i << "][" << j << "] = " << C[i][j] << " ";
				return false;
			}
			std::cout << "\n";
		}
	}
	return true;
}

std::vector<std::vector<int>> mult_matrices(const std::vector<std::vector<int>>& A,
	const std::vector<std::vector<int>>& B)
{
	size_t N = A.size();
	std::vector<std::vector<int>> C(N, std::vector<int>(N));

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			C[i][j] = 0;
			for (size_t k = 0; k < N; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return C;
}



