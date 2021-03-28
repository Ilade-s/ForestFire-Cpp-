// Simulation de feu de forêt
// Fait à partir de mon programme en Python

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

vector<vector<int>> GenGrid(int rows, int cols, float TreeRate) // Génération de la grille
{
    // Initialisation variables
    vector<int> GridLine;
    vector<vector<int>> Grid;

    // Création grille en ligne
    for (int i = 0; i < rows*cols*(1-TreeRate)-1; ++i) GridLine.push_back(0); // Cases vides
    for (int i = 0; i < rows*cols*TreeRate; ++i) GridLine.push_back(1); // Cases de forêt
    GridLine.push_back(2); // Case en feu initiale

    // Mélange de la grille en ligne
    shuffle(begin(GridLine), end(GridLine), default_random_engine());

    // Séparation liste pour création Grille
    for (int i = 0; i < rows; i++)
    {
        vector<int> ir;
        for (int j = 0; j < cols; j++)
        {
            ir.push_back(GridLine[i*j]);
        }
        Grid.push_back(ir);
    }
    
    
    return Grid;
}

int main()
{
    cout << "Bienvenue dans ma simulation de feu de foret !\n";

    // initialisation variables
    int rows = 50;
    int cols = 50;
    float TreeRate = 0.90;
    vector<vector<int>> Grid = GenGrid(rows, cols, TreeRate);

    // Affichage grille
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << Grid[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    return 0;
}