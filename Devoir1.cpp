#include<iostream>
#include<fstream> // pour les fichier 
#include<cmath>  //maths
#include<string>
#include<vector>
#include "Devoir1.hpp"
using namespace std;
//fonction qui ajoute des mots au vectuer puis les efface
vector<string> effacerLesMots(string s){
    vector<string> words;
    string word ;
    int k = 0;
    while ( k < s.size())
    {
    
        while (k < s.size() && s[k] == ' ' )
        {
            k++;
        }
        while (k < s.size() && s[k] != ' ')
        {
            word.push_back(s[k]);    
            k++;
        }
        if(word.empty()==false){
            words.push_back(word);
        }
        word.clear();
        

    }
    return words ; 
}
// Verification de l'existence du fichier.
vector<string> lireFile(string lien){
   vector<string> fichierLignes;
    string ligne ; 
ifstream myFile(lien.c_str());
if(myFile){
 while(getline(myFile, ligne))
 fichierLignes.push_back(ligne);
}
else{
    cout<<"Erreur : Impossible d'ouvrir le fichier ! " <<endl;
}
return fichierLignes ; 
}
//Le langage C++ est sensible a la casse il faut donc changer toutes les lettres en lettres miniscule.
string lowerCase(string s){

    for (int i=0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}
//parcourir le fichier et le mettre dans un vecteur en changeant les majuscules par miniscule
vector<string> motsFichier(vector<string> lines){

    vector <string> words;
    for( auto line = lines.begin() ; line != lines.end(); line ++ ){
            for ( auto word :effacerLesMots(*line) ) {
                words.push_back(lowerCase(word));
            }
        }

    return words;

}
//compter le nombre d'iterations du mot et le mettre dans un vecteur(mot et son iteration)
vector<pair<string, int > > iterationsNumber(vector <string> wordsfile){
    bool addToList = false;
    vector<pair<string, int > > dataFile;

    for(auto word: wordsfile){
        if(dataFile.empty()==true){
          dataFile.emplace_back(word,1);
        }else{
            for(int i = 0 ; i<=dataFile.size();i++ ){

                if(word == dataFile[i].first){
                    dataFile[i].second++;
                    addToList = true;
                    break;
                }

            }
            if (addToList==false){
            dataFile.emplace_back(word,1);
            }
            addToList=false;
        }
    }
    return dataFile;
}

int main (){
      // lire les fichier depius l'utilisateur :
    string fichier1 , fichier2;
    
    cout << "donner le nom de fichier 1 :  " << endl ; 
    cin >> fichier1;  
    cout << "donner le nom de fichier 2 :  " << endl ; 
    cin >> fichier2;  
    vector<string> fichierLignes1 = lireFile(fichier1);
    vector<string> wordsfile1 = motsFichier(fichierLignes1);
    vector<string> fichierLignes2 = lireFile(fichier2);
    vector<string> wordsfile2 = motsFichier(fichierLignes2);
   
    vector<pair<string, int > > motfichier1 = iterationsNumber(wordsfile1);

    vector<pair<string, int > > motfichier2 = iterationsNumber(wordsfile2);


    double x = 0.0 ; 
    double da, db;
    for(auto data1 : motfichier1){
        for(auto data2 : motfichier2){
            if (data1.first == data2.first){
                
                x += data1.second * data2.second;

            }
        }
    }
    for(auto data1:motfichier1){
         da += data1.second * data1.second;
    }
    for(auto data2:motfichier2){
         db += data2.second * data2.second;
    }

    cout << "  silimarity  :  " << round((x / (sqrt(da) * sqrt(db)))*100)<< "%" << endl ;


    return 0 ; 
}


