#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
using namespace std;

struct RatingData {
	int id;
	string title;
	double rating;
};

void merge(RatingData tab[], int l, int m, int r, RatingData*& temp) {
	int a = l, b = m + 1, i = 0;
	while (a <= m && b <= r) {
		if (tab[a].rating < tab[b].rating)
			temp[i++] = tab[a++];
		else
			temp[i++] = tab[b++];
	} // Porownanie dwoch stron tablicy

	// Gdy b skonczylo sie przed a
	while (a <= m) {
		temp[i++] = tab[a++];
	}

	// Gdy a skonczylo sie przed b
	while (b <= r) {
		temp[i++] = tab[b++];
	}

	// Przepisanie wartosci do oryginalnej tablicy
	for (size_t i = 0; i < r - l + 1; i++) {
		tab[l + i] = temp[i];
	} // tak btw l to przesuniecie
	// miejsce w ktorym nalezy dodac wartosc
	// skoro tablica jest jednoargumentowa
}

void mergeSort(RatingData tab[], int l, int r) {
	if (l < r) {
		RatingData* temp = new RatingData[r - l + 1]; // Tymczasowa tablica
		int m = static_cast<int>(floor((l + r) / 2));
		mergeSort(tab, l, m); // Zmniejszenie lewej strony tablicy
		mergeSort(tab, m + 1, r); // Zmniejszenie prawej strony tablicy
		merge(tab, l, m, r, temp); // Scalenie i porownanie powyzszych czesci
		delete[] temp; // Sprzatanie
	}
}

int main() {
	ifstream file("C:\\Users\\nicwr\\Downloads\\projekt2_dane.csv");

	if (!file.is_open()) {
		cout << "Error: Could not open file." << endl;
		return 1;
	}

	const int MAX_RATINGS = 1010294;
	const int MAX_RATINGS_DATA = 1010294;
	RatingData* ratings = new RatingData[MAX_RATINGS];
	string line;
	int numRatings = 0;

	getline(file, line);

	while (getline(file, line) && numRatings < MAX_RATINGS) {
		stringstream ss(line);
		RatingData data;
		string id_str, rating_str;

		getline(ss, id_str, ',');
		data.id = stoi(id_str);
		getline(ss, data.title, ',');

		// Sprawdzenie czy rating nie jest pusty
		if (ss >> data.rating && data.rating <= 10) {
			ratings[numRatings++] = data;
		}
	}

	file.close();

	auto start = chrono::steady_clock::now();
	mergeSort(ratings, 0, numRatings - 1);
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Czas sortowania: " << elapsed_ms.count() << " mikrosekundy" << endl;

	//cout << "Sorted Ratings:\n";
	//for (int i = 0; i < numRatings; i++) {
	//	cout << "Rating: " << ratings[i].rating << ", Title: " << ratings[i].title << endl;
	//}

	delete[] ratings;
}