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
	RatingData() : id(0), title(""), rating(0.0) {};
};

void bucketSort(RatingData*& tab, size_t tabSize) {
	double min = 0.0, max = 0.0;
	// Ustalamy Min i Max pod zakres
	for (size_t i = 0; i < tabSize; i++) {
		if (i == 0) {
			min = tab[i].rating; // O(1)
			max = tab[i].rating; // O(1)
		}
		else {
			if (tab[i].rating > max) max = tab[i].rating; // O(1)
			else if (tab[i].rating < min) min = tab[i].rating; // O(1)
		}
	}

	size_t numberOfBuckets = static_cast<size_t>(max - min + 1); // O(1)
	// poniewaz chcemy wartosci od min do max włącznie dlatego tez +1  
	int* buckets = new int[numberOfBuckets + 1](); // O(liczba kubełków)
	// +1 dla indeksu aby kubelek 10 byl na miejscu 10

	for (size_t i = 0; i < tabSize; i++) {
		if (tab[i].rating >= 0 && tab[i].rating <= numberOfBuckets) {
			buckets[static_cast<int>(tab[i].rating)]++; // O(1)
		}
	} // +1 dla liczb ktore wystepuja w tablicy

	size_t k = 0;
	for (size_t i = 0; i <= numberOfBuckets; i++) {
		for (size_t j = buckets[i]; j > 0; j--) {
			tab[k++].rating = static_cast<double>(i); // O(n)
		}
	} // przypisanie ( nie sortowanie ) do tablicy w zaleznosci 
	// od tego ile razy wystepuje ( wartosc kubełka na danym indeksie )

	delete[] buckets; // O(1)
	// sprzątanie
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
	for (size_t i = 0; i < 5; i++) {
		int value = sortingSize[i];
		if (value > max) {
			value = max;
		}
			auto start = chrono::steady_clock::now();
			bucketSort(ratings, value);
			auto end = chrono::steady_clock::now();
			auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - start);
		if (i == 0) {
			cout << "Sorted Ratings:\n";
			for (size_t j = 0; j < sortingSize[i]; j++) {
				cout << "Rating: " << ratings[j].rating << ", Title: " << ratings[j].title << endl;
			}
			cout << endl;
		}
		cout << "Ilosc: " << sortingSize[i] << " Czas: " << fixed << setprecision(4) << static_cast<double>(elapsed_ms.count()) / 1000000 << " sekundy" << endl;
	}
	delete[] ratings;
}
