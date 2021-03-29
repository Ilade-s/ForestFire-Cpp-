// Simulation de feu de forêt
// Fait à partir de mon programme en Python

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

void print(vector<vector<int>> Grid, int cols, int rows)
{
    // Affichage grille
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << Grid[i][j] << " ";
        }
        cout << "\n";
    }
}
vector<vector<int>> GenGrid(int rows, int cols, float TreeRate) // Génération de la grille
{
    // Initialisation variables
    vector<int> GridLine;
    vector<vector<int>> Grid;

    // Création grille en ligne
    for (int i = 0; i < rows*cols*(1-TreeRate); ++i) GridLine.push_back(0); // Cases vides
    for (int i = 0; i < rows*cols*TreeRate; ++i) GridLine.push_back(1); // Cases de forêt
    GridLine[0] = 2; // Case en feu initiale

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

void PropFire(vector<vector<int>> Grid) // exécute une passe de propagation de feu
{



}

int TreesRemaining(vector<vector<int>> Grid, int cols, int rows) // fonction pour compter les arbres restants
{
    int Ntrees = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (Grid[i][j] == 1)
            {
                Ntrees++;
            }
            
        }
    }
    return Ntrees;
}

int main()
{
    cout << "Bienvenue dans ma simulation de feu de foret !\n";

    // initialisation variables
    int rows = 50;
    int cols = 50;
    float TreeRate = 0.90;
    vector<vector<int>> Grid = GenGrid(rows, cols, TreeRate); // création grille
    int Ntrees = TreesRemaining(Grid, cols, rows); // nombre d'arbres

    print(Grid, cols, rows); // affichage grille

    cout << "\n" << Ntrees << "\n";

    return 0;
}