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

bool square_matrix(int rows, int cols) {
	if (rows == cols) return true;
	else return false;
}

void user_output(double num_of_out) {
	if (num_of_out == 0) {
		cout << "Введите размерность матрицы"<<endl;
	}
	else if (num_of_out == 0.1) {
		cout << "Введите вашу матрицу построчно" << endl;
	}
	else if (num_of_out == 0.3) {
		cout << "Введите номер команды" << endl;
	}
	else if (num_of_out == 2.1) {
		cout << "Введите количество столбцов новой матрицы" << endl;
	}
	else if (num_of_out == 2.2) {
		cout << "Введите новую матрицу по строкам" << endl;
	}
	else if (num_of_out == 3.1) {
		cout << "Введите положительное число - степень" << endl;
	}
	else if (num_of_out == 3.2) {
		cout << "Ошибка! Ваша матрица не квадратная!" << endl;
	}
}

int** power_matrix(int** matrix, int power, int rows, int cols) {
	int** a0 = declaration_of_matrix(rows, cols);
	equal_matrix(a0, matrix, rows, cols);
	for (int i = 1; i < power; i++) {
		multiple_matrix(matrix, a0, rows, cols);
	}
	delete_matrix(a0, rows);
	return matrix;
}

int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "rus");
	bool interface = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
		interface = true;
	int N, M;
	if(interface) user_output(0);
	cin >> N >> M;
	int** A = declaration_of_matrix(N, M);
	if(interface) user_output(0.1);
	A = input_matrix(A, N, M);
	int command;
	if (interface) user_output(0.3);
	cin >> command;
	while (command != 0) {
		if (command == 1) {
			matrix_to_disp(A, N, M);
		}
		else if (command == 2) {
			int K;
			if (interface) user_output(2.1);
			cin >> K;
			int** A2 = declaration_of_matrix(M, K);
			if (interface) user_output(2.2);
			A2 = input_matrix(A2, M, K);
			multiple_matrix(A, A2, N, K);
			delete_matrix(A2, M);
			M = K;
		}
		else if (command == 3) {
			if (square_matrix(N, M)) {
				if (interface) user_output(3.1);
				int x;
				cin >> x;
				power_matrix(A, x, N, M);
			}
			else {
				if (interface) user_output(3.2);
				else cout<<"NO"<<endl;
				goto point;
			}
		}
		point:;
		if (interface) user_output(0.3);
		cin >> command;
	}
	delete_matrix(A, N);
}
