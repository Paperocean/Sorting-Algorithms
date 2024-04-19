#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;

/*
Quicksort
Wybiera sobie pivot, a nastepnie:
z lewej strony szuka wartosci wiekszej niz pivot
z prawej strony szuka wartosci mniejszej niz pivot
az do momentu kiedy beda posortowane czyli lewa strona nie przekroczy prawej
jezeli znajdzie dane wartosci zamienia je ze soba
*/

struct RatingData {
    int id;
    string title;
    double rating;
};

void quicksort(RatingData*& tab, int a, int b) {
	if (a < b) {
		int middle = static_cast<int>((a + b) / 2);
        int pivotIndex = rand() % (b - a + 1) + a;
        RatingData pivot = tab[pivotIndex];
		int l = a, r = b ;

		if (pivot.rating != tab[middle].rating) {
			swap(tab[pivotIndex], tab[middle]);
		}

		while (l <= r ) {
			while (tab[l].rating < pivot.rating) l++; // Wyznaczasz sobie tu liczbe wieksza od pvt
			while (tab[r].rating > pivot.rating) r--; // Wyznaczasz liczbe mniejsza od pvt

			if (l <= r) { // poprawnosc pivota
				swap(tab[l], tab[r]);
				l++; // pomniejszasz zakres o ta liczbe
				r--;
			}
		}

		quicksort(tab, a, r);
		quicksort(tab, l, b);
	}
}

void swap(RatingData*& tabA, RatingData*& tabB) {
    RatingData* temp = tabA;
    tabA = tabB;
    tabB = temp;
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
			quicksort(ratings, 0, value - 1);
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
				cout << "Ilosc: " << sortingSize[i] << " Czas: " << fixed << setprecision(4) << avr/3 << " sekund" << endl;
			}
		}
	}
	delete[] ratings;
}
