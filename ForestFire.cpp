// Simulation de feu de forêt
// Fait à partir de mon programme en Python

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

vector<vector<int>> GenGrid() // Génération de la grille
{
    vector<int> voidPart {1, 2, 3};

    shuffle(begin(voidPart), end(voidPart), default_random_engine());

    // affichage liste
        cout << "liste initiale : ";
        for (vector<int>::iterator it = voidPart.begin(); it != voidPart.end(); it++)
            cout << *it << ' ';

    cout << "\n";

    vector<vector<int>> Grid;

    return Grid;
}

int main()
{
    cout << "Bienvenue dans ma simulation de feu de foret !\n";

    // initialisation variables
    vector<vector<int>> Grid = GenGrid();

    return 0;
}