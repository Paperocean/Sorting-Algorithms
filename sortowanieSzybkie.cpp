#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
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

void quicksort(RatingData tab[], int a, int b) {
	if (a < b) {
		int pivotIndex = (a + b) / 2;
        RatingData pivot = tab[pivotIndex];
		int l = a, r = b;

		while (l <= r && l >= a && r <= b) {
			while (tab[l].rating < pivot.rating && l < b) l++; // Wyznaczasz sobie tu liczbe wieksza od pvt
			while (tab[r].rating > pivot.rating && r > a) r--; // Wyznaczasz liczbe mniejsza od pvt

			if (l <= r) { // poprawnosc pivota
				RatingData temp = tab[r]; // swap
				tab[r] = tab[l];
				tab[l] = temp;
				l++; // pomniejszasz zakres o ta liczbe
				r--;
			}
		}
		quicksort(tab, a, r);
		quicksort(tab, l, b);
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
    quicksort(ratings, 0, numRatings - 1);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Czas sortowania: " << elapsed_ms.count() << " mikrosekundy" << endl;

    //cout << "Sorted Ratings:\n";
    //for (int i = 0; i < numRatings; i++) {
    //    cout << "Rating: " << ratings[i].rating << ", Title: " << ratings[i].title << endl;
    //}

    delete[] ratings;

}