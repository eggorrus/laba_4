#include <iostream>

using namespace std;

void matrix_to_disp(int** A, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols - 1; j++)
			cout << A[i][j] << " ";
		cout << A[i][cols - 1]<< endl;
	}
}

void delete_matrix(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int** declaration_of_matrix(int rows, int cols) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
	return matrix;
}

int** input_matrix(int** matrix, int rows, int cols) {
	int num;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> num;
			matrix[i][j] = num;
		}
	}
	return matrix;
}

void equal_matrix(int** matrix1, int** matrix2, int rows, int cols) {
	for (int i = 0; i < rows; i++) 
		for (int j = 0; j < cols; j++) 
			matrix1[i][j] = matrix2[i][j];
}

void multiple_matrix(int** a, int** b, int rows, int cols) {
	int** result = declaration_of_matrix(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result[i][j] = 0;
			for (int k = 0; k < rows; k++) {
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	equal_matrix(a, result, rows, cols);
	delete_matrix(result, rows);
}

int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "rus");
	bool interface = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
		interface = true;
	int N, M;
	if (interface)
		cout << "Введите размерность матрицы" << endl;
	cin >> N >> M;
	int** A = declaration_of_matrix(N, M);
	if (interface) cout << "Введите матрицу по строкам" << endl;
	int num;
	A = input_matrix(A, N, M);
	int command;
	if (interface) cout << "Введите команду (0 - окончание работы программы, 1 - вывод матрицы А, 2 - произведение матриц, 3 - вовзедение А в степень" << endl;
	cin >> command;
	while (command != 0) {
		if (command == 1) {
			matrix_to_disp(A, N, M);
		}
		else if (command == 2) {
			int K;
			if (interface) cout << "Введите значение К (количество столбцов в вводимой матрице)" << endl;
			cin >> K;
			int** A2 = declaration_of_matrix(M, K);
			if (interface) cout << "Введите новую матрицу" << endl;
			A2 = input_matrix(A2, M, K);
			multiple_matrix(A, A2, N, K);
			delete_matrix(A2, M);
			M = K;
		}
		else if (command == 3) {
			if (N != M) {
				if (interface) cout << "Матрица не квадратная!" << endl;
				else cout << "NO" << endl;
				goto point;
			}
			else {
				if (interface) cout << "Введите степень" << endl;
				int x;
				cin >> x;
				int** a0 = declaration_of_matrix(N, M);
				equal_matrix(a0, A, N, M);
				for (int i = 1; i < x; i++) {
					multiple_matrix(A, a0, N, M);
				}
				delete_matrix(a0, N);
			}
		}
		point:;
		if (interface) cout << "Введите команду (0 - окончание работы программы, 1 - вывод матрицы А, 2 - произведение матриц, 3 - вовзедение А в степень" << endl;
		cin >> command;
	}

	delete_matrix(A, N);
}