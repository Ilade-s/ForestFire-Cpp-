// Simulation de feu de forêt
// Fait à partir de mon programme en Python

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

vector<int> GenGrid() // Génération de la grille
{
    vector<int> voidPart {1, 2, 3};

    shuffle(begin(voidPart), end(voidPart), default_random_engine());

    vector<vector<int>> Grid;

    return voidPart;
}

int main()
{
    cout << "Bienvenue dans ma simulation de feu de foret !\n";

    // initialisation variables
    vector<int> Grid = GenGrid();

    // affichage liste
        cout << "liste initiale : ";
        for (vector<int>::iterator it = Grid.begin(); it != Grid.end(); it++)
            cout << *it << ' ';

    cout << "\n";

    return 0;
}