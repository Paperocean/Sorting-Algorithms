#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;

struct RatingData {
	int id;
	string title;
	double rating;
};

void merge(RatingData*& tab, int l, int m, int r, RatingData*& temp) {
	size_t tempSize = r - l + 1;
	if (tempSize > 1) {
		int a = l, b = m + 1, i = 0;
		while (i < tempSize) {
			if (a <= m && (b > r || tab[a].rating < tab[b].rating))
				temp[i++] = tab[a++];
			else
				temp[i++] = tab[b++];
		} // Porownanie dwoch stron tablicy

		// Przepisanie wartosci do oryginalnej tablicy
		for (size_t j = 0; j < tempSize; j++) {
			tab[l + j] = temp[j];
		} // l to przesuniecie
		// miejsce w ktorym nalezy dodac wartosc
		// skoro tablica jest jednoargumentowa
	}
}

void mergeSort(RatingData*& tab, int l, int r) {
	if ( l < r ) {
		RatingData* temp = new RatingData[r - l + 1]; // Tymczasowa tablica
		int m = static_cast<int>(floor((l + r) / 2));
		mergeSort(tab, l, m); // Zmniejszenie lewej strony tablicy
		mergeSort(tab, m + 1, r); // Zmniejszenie prawej strony tablicy
		merge(tab, l, m, r, temp); // Scalenie i porownanie powyzszych czesci
		delete[] temp;
	}
}

void readFile(RatingData*& ratings, int& max) {
	ifstream file("C:\\Users\\nicwr\\Downloads\\projekt2_dane.csv");
	if (!file.is_open()) {
		cout << "Error: Could not open file." << endl;
		return;
	}

	const int INCREASE_VALUE = 1000000;
	int MAX_RATINGS = INCREASE_VALUE;
	ratings = new RatingData[INCREASE_VALUE];
	string line;
	max = 0;

	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		RatingData data;
		string id_str, rating_str;

		getline(ss, id_str, ',');
		data.id = stoi(id_str);
		getline(ss, data.title, ',');

		if (ss >> data.rating && data.rating <= 10) {
			if (max >= MAX_RATINGS) {
				// Dynamiczne powiększanie tablicy ratings / wykorzystanie dwukrotnej alokacji pamieci
				MAX_RATINGS *= 2;
				RatingData* temp = new RatingData[MAX_RATINGS];
				for (int i = 0; i < max; ++i) {
					temp[i] = ratings[i];
				}
				delete[] ratings;
				ratings = temp;
			}
			ratings[max++] = data;
		}
	}
	file.close();
}

int main() {
	RatingData* ratings;
	int max;
	readFile(ratings, max);
	const int sortingSize[5]{ 10000, 100000, 500000, 1000000, max };
	float avr;
	for (size_t i = 0; i < 5; i++) {
		avr = 0.0;
		for (size_t j = 0; j < 3; j++) {
			int value = sortingSize[i];
			if (value > max) {
				value = max;
			}
			auto start = chrono::steady_clock::now();
			mergeSort(ratings, 0, value-1);
			auto end = chrono::steady_clock::now();
			auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - start);
			avr += static_cast<double>(elapsed_ms.count()) / 1000000;
			if (i == 0 && j == 0) {
				cout << "Sorted Ratings:\n";
				for (size_t k = 0; k < sortingSize[i]; k++) {
					cout << "Rating: " << ratings[k].rating << ", Title: " << ratings[k].title << endl;
				}
				cout << endl;
			}
			if (j == 2) {
				cout << "Ilosc: " << sortingSize[i] << " Czas: " << fixed << setprecision(4) << avr / 3 << " sekund" << endl;
			}
		}
	}
	delete[] ratings;
}
