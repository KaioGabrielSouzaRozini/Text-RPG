#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <time.h>

using namespace  std;

class Protagonist {
  public:
    string name;   
    int level;
    int health;

    void setProtagonist(string name) {
         name = name;
         level = 1;
         health = 100;
         }
};

class Monster {
  public:
    string name;   
    int level;
    int health;
};

int main(){

    setlocale(LC_ALL, "portuguese");
    Protagonist protagonist;
    string name;
    cout << "Em um mundo governado pelo cruel Império de Valgard, onde a liberdade foi suprimida e a justiça é apenas uma lembrança, pequenos grupos de resistência começam a se formar." << endl;
    cout << "Você é um desses rebeldes, determinado a minar o poder do Império e restaurar a liberdade ao continente de Eryndor. Sua missão é clara: desafiar a tirania e um dia, enfrentar o próprio Imperador." << endl;
    cout << " O destino de Eryndor depende de suas ações.";

    cout << "Qual o seu nome ?";
    cin >> name;
    protagonist.setProtagonist(name);

}

