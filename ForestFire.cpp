// Simulation de feu de forêt
// Fait à partir de mon programme en Python

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <windows.h>

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

bool Proba(int ProbaFire = 80)
{
    int n = rand() % 100 + 1;

    if (n < ProbaFire)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<vector<int>> GenGrid(int rows, int cols, int TreeRate) // Génération de la grille
{
    // Initialisation variables
    vector<int> GridLine;
    vector<vector<int>> Grid;

    // Création grille en ligne
    for (int i = 0; i < rows*cols*TreeRate/100-1; ++i) GridLine.push_back(1); // Cases vides
    for (int i = 0; i < rows*cols*(100-TreeRate)/100; ++i) GridLine.push_back(0); // Cases de forêt
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

auto PropFire(vector<vector<int>> Grid, int cols, int rows) // exécute une passe de propagation de feu
{
    // boucle sur la totalité de la grille
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((Grid[i][j] == 2) || (Grid[i][j] == 3)) // si arbre en feu
            {
                // exceptions sur les lignes extrêmes
                if (i == 0){
                    if ((Grid[i+1][j] == 1) && (Proba())){
                        Grid[i+1][j] = 5;
                    }
                }
                else if (i == rows-1){
                    if ((Grid[i-1][j] == 1) && (Proba())){
                        Grid[i-1][j] = 5;
                    }
                }
                // ligne non extrême
                else
                {
                    if ((Grid[i+1][j] == 1) && (Proba())){
                        Grid[i+1][j] = 5;
                    }
                    if ((Grid[i-1][j] == 1) && (Proba())){
                        Grid[i-1][j] = 5;
                    }
                }
                // exceptions sur les colonnes extrêmes
                if (j == 0){
                    if ((Grid[i][j+1] == 1) && (Proba())){
                        Grid[i][j+1] = 5;
                    }
                }
                else if (j == cols-1){
                    if ((Grid[i][j-1] == 1) && (Proba())){
                        Grid[i][j-1] = 5;
                    }
                }
                // colonne non extrême
                else
                {
                    if ((Grid[i][j+1] == 1) && (Proba())){
                        Grid[i][j+1] = 5;
                    }
                    if ((Grid[i][j-1] == 1) && (Proba())){
                        Grid[i][j-1] = 5;
                    }
                }
                // passe arbre
                switch (Grid[i][j])
                {
                case 2:
                    Grid[i][j] = 3;
                    break;
                
                case 3:
                    Grid[i][j] = 4;
                    break;
                }
            }
        }
            
    }
    // boucle sur la totalité de la grille pour passage nouveaux feux en feux normaux
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (Grid[i][j] == 5){
                Grid[i][j] = 2;
            }
        }
    }
    return Grid;
}

int TypeSearch(vector<vector<int>> Grid, int cols, int rows, int type = 1) // fonction pour compter les arbres restants
{
    int Ntrees = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (Grid[i][j] == type)
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
    int rows = 50; // nombre de lignes
    int cols = 50; // nombre de colonnes
    int ProbaFire = 80; // probabilité de prise de feu
    int TreeRate = 80; // part d'arbres initiale dans les cases

    // inputs pour génération de la grille (optionnels)
    cout << "Infos pour generation de la grille :" << "\n" << "\tNombre de lignes : ";
    cin >> rows;
    cout << "\n" << "\tNombre de colonnes : ";
    cin >> cols;
    cout << "\n" << "\tPart d'arbres (en %) : ";
    cin >> TreeRate;
    cout << "\n" << "\tProbabilite de feu (en %) : ";
    cin >> ProbaFire;

    vector<vector<int>> Grid = GenGrid(rows, cols, TreeRate); // grille de simulation
    int Ntrees = rows*cols*TreeRate; // nombre d'arbres
    int NInitialTrees = rows*cols*TreeRate; // nombre d'arbres initiaux
    int Nfeux = TypeSearch(Grid, cols, rows, 2); // nombre d'arbres en feu
    float RemainingTreeShare = 100.0;
    int TimePause = 1000; // temps de pause entre chaque passe
    string aff = "O";
    // input pour demande d'affichage
    cout << "\n" << "\tSouhaitez-vous un affichage de la grille ? ('O' ou 'N') ";
    cin >> aff;
    
    if (aff == "O") 
    {
        // input temps de pause
        cout << "\n" << "\tCombien de temps de pause entre chaque passe (en dixiemes de secondes) ? ";
        cin >> TimePause;
        TimePause *= 100;
        // affichage grille
        print(Grid, cols, rows); 
    }

    cout << "\n" << "Arbres initiaux : " << NInitialTrees;
    cout << "\n" << "Arbres en feu initiaux : " << Ntrees << "\n";
    
    while (Nfeux != 0) // boucle propagation du feu
    {
       Grid = PropFire(Grid, cols, rows); // passe de propagation
       // mise à jour des variables
       Ntrees = TypeSearch(Grid, cols, rows);
       Nfeux = TypeSearch(Grid, cols, rows, 2) + TypeSearch(Grid, cols, rows, 3);
       RemainingTreeShare = Ntrees / NInitialTrees * 100;
       // affichage résultat de la passe (si demandé)
       if (aff == "O")
       {
            print(Grid, cols, rows);
            cout << "\n" << "Arbres restants : " << Ntrees << "\n";
            cout << "Proportion d'arbres restants (en %) : " << RemainingTreeShare << "\n\n"; 
       }
       Sleep(TimePause); // pause
    }
    // fin du programme
    if (aff == "N"){
        cout << "\n" << "Arbres restants : " << Ntrees << "\n";
        cout << "Proportion d'arbres restants (en %) : " << RemainingTreeShare << "\n\n"; 
    }
    cout << "Simulation terminee" << "\n";
    return 0;
}