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

void bucketSort(RatingData tab[], size_t tabSize) {
	// Ustalamy Min i Max pod zakres
	double min = 0.0, max = 0.0;
	for (size_t i = 0; i < tabSize; i++) {
		if (i == 0) {
			min = tab[i].rating;
			max = tab[i].rating;
		}
		else {
			if (tab[i].rating > max) max = tab[i].rating;
			else if (tab[i].rating < min) min = tab[i].rating;
		}
	}

	size_t numberOfBuckets = static_cast<size_t>(max - min + 1); // poniewaz chcemy wartosci od min do max włącznie dlatego tez +1
	int* buckets = new int[numberOfBuckets + 1]; // +1 dla indeksu

	for (size_t i = 0; i <= numberOfBuckets; i++) {
		buckets[i] = 0;
	} // zapełniamy zerami

	for (size_t i = 0; i < tabSize; i++) {
		if (tab[i].rating >= 0 && tab[i].rating <= numberOfBuckets) {
			buckets[static_cast<int>(tab[i].rating)]++;
		}
	} // +1 dla liczb ktore wystepuja w tablicy

	size_t k = 0;
	for (size_t i = 0; i <= numberOfBuckets; i++) {
		for (size_t j = buckets[i]; j > 0; j--) {
			tab[k++].rating = static_cast<double>(i);
		}
	} // przypisanie ( nie sortowanie ) do tablicy w zaleznosci 
	// od tego ile razy wystepuje ( wartosc kubełka na danym indeksie )

	delete[] buckets; // sprzątanie
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
	bucketSort(ratings, numRatings);
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Czas sortowania: " << elapsed_ms.count() << " mikrosekundy" << endl;

	/*cout << "Sorted Ratings:\n";
	for (int i = 0; i < numRatings; i++) {
		cout << "Rating: " << ratings[i].rating << ", Title: " << ratings[i].title << endl;
	}*/

	delete[] ratings;
}