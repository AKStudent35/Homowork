#include <iostream>
#include <random>

//trochę informacji
/*
zastanawiałem się nad tym jak zrobić ten algorytm i zauważyłem kilka zależności.
1) nowe pole pobiera daną z pola wyżej, niżej,z lewe lub z prawej.
2) pola te tworzą swego rodzaju piramidki
-przykładowa tablica, gdzie p to prawo,l to lewo, d to dół, g to góra
p	p	p	p	p	p	p	d
g	p	p	p	p	p	d	d
g	g	p	p	p	d	d	d
g	g	g	l	l	l	d	d
g	g	l	l	l	l	l	d
g	l	l	l	l	l	l	l

co daje nam						
			l	l	l		
		l	l	l	l	l	
	l	l	l	l	l	l	l

4) pola przesuwają się po okręgu

po sprawdzeniu dwóch algorytmów uznałem, że prostrzym rozwiązaniem jest aktualizacja tablicy po okręgu

program losuje wartości od 0 do 9 oczywiście można tą wartość zmienić - jest wpisana na sztywno do kodu

powinienem był ten kod rozbić na większą ilość plików/funkcji, lecz rozumiem to zadanie jako sprawdzenie czy potrafię napisać algorytm przemieszczający dane po tablicy
*/

//sets random values for an array
void setValues(int N, int M, int **&table) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			table[i][j] = rand() % 10;
		}
	}
}

//prints table to the console
void printTable(int N,int M,int **&table) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cout << table[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}

//memory allocation
void allocateMemory(int N, int M, int **&table) {
	table = new int* [N];
	for (int i = 0; i < N; i++) {
		table[i] = new int[M];
	}
}

//swaping tables
void swapTable(int**&table1, int** table2,int N,int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			table1[i][j] = table2[i][j];
		}
	}
}

//single rotation
void iterate(int N,int M,int**&asd,int**&table) {

	enum Direction { up, down, left, right };
	Direction direction = right;

	int iterationCounter=0;
	int n=0;
	int m=0;

	
	while (1) {

		if (direction == right) {
			if (m != M - 1 - iterationCounter) {
				asd[n][m] = table[n][m + 1];
				m++;
			}

			else {
				asd[n][m] = table[n + 1][m];
				direction = down;
				if (n != N - 1) {
					n++;
				}
			}
		}

		if (direction == down) {
			if (n != N - 1 - iterationCounter) {
				asd[n][m] = table[n + 1][m];
				n++;
			}
			else {

				asd[n][m] = table[n][m - 1];
				direction = left;
				if (m != 0) {
					m--;
				}
			}
		}

		if (direction == left) {
			if (m != iterationCounter) {
				asd[n][m] = table[n][m - 1];
				m--;
			}
			else {
				asd[n][m] = table[n - 1][m];
				direction = up;
				if (n != 0) {
					n--;
				}
			}
		}

		if (direction == up) {
			if (n != iterationCounter) {
				asd[n][m] = table[n - 1][m];
				n--;
			}
			else {
				direction = right;

				iterationCounter++;
				n = iterationCounter;
				m = iterationCounter;
				if (n >= N / 2 || m >= M / 2) { break; }
			}
		}
	}

}

// main function :)
int main()
{
	//dimensions
    int N, M;

	int** table;

	int** asd;

	int R;

	std::cout << "put number of columns" << std::endl;
	std::cin >> M;
	
	std::cout << "put number of rows" << std::endl;
	std::cin >> N;

	std::cout << "put number of iterations" << std::endl;
	std::cin >> R;

	//some exceptions
	if (R < 0) {
		std::cout << "imposible number of iterations";
		return 0;
	}
	if (M == 1 || N == 1) {
		std::cout << "it is no longer 2 dimensional matrix";
		return 0;
	}


	//memory allocation
	allocateMemory(N, M, table);
	allocateMemory(N, M, asd);

	//set random values and print them to the console
	setValues(N, M, table);
	printTable(N, M,table);

	//iterations
	swapTable(asd, table, N, M);

	//rotating matrix
	for (int k = 0; k < R; k++) {
		//single rotation on matrix
		iterate(N, M, asd, table);

		//swaping buffer matrix with main matrix
		swapTable(table, asd, N, M);
		printTable(N, M, table);

	}
	delete []asd;

	return 0;
}
