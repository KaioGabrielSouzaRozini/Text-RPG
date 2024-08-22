#include <iostream>
#include <locale.h>
#include <unistd.h>


using namespace  std;

class Protagonist {
  public:
    string name;   
    int level;
    int health;
    int maxHealth;
    int damage;

    void setProtagonist(string newName) {
         name = newName;
         level = 1;
         health = 100;
         maxHealth = 100;
         damage = 10;
         }
         
    void takeDamege(int damage){
        health -= damage;
    }
    
    void levelUp(){
        level += 1;
        maxHealth += 50;
        health += 50;
    }
    
    
};
void combat(){
    
}

void moving() {
    int choice;
    cout << "1. Ir ao combate\n";
    cout << "2. Descansar\n";
    cout << "3. treinar\n\n";
    
    cin >> choice;
    
    switch(choice){
        case 1:
            cout << "Andando...";
            sleep(2);
            
            break;
        case 2:
            cout << "Tuesday";
            break;
        case 3:
            cout << "Wednesday";
            break;
    }
}

class Piece {
  public:
    string name;   
    int level;
    int health;
    int damage;
    void setPiece(string newName, int newLevel, int newHealth, int newDamage) {
         name = newName;
         level = newLevel;
         health = newHealth;
         damage = newDamage;
         }
};





    
    



int main(){

    setlocale(LC_ALL, "Portuguese");
    
    //Contando historia e criando personagem
    Protagonist protagonist;
    string name;
    cout << "Uma batalha foi travada, Brancas VS Pretas, foi uma guerra devastadora que terminou em 77 movimentos, todas as peças pretas foram mortas exeto por você, o rei preto\n Agora em um mundo governado pelo cruel Rei das Peças Brancas, onde a liberdade foi suprimida e a justiça é apenas uma lembrança.\nDeterminado a minar o poder do Império e restaurar a liberdade ao continente de Xadrez.\nSua missão é clara: desafiar a tirania e um dia, enfrentar o próprio Rei Branco.\nO destino do Xadrez depende de suas ações." << endl;
    sleep(3);
    cout << "Qual o seu nome ?" << endl;
    cin >> name;
    protagonist.setProtagonist(name);
    sleep(1);
    cout << "\x1B[2J\x1B[H";
    cout << "Nome: " << protagonist.name << endl << "Nivel: " << protagonist.level << endl << "Vida: " << protagonist.health << endl;
    sleep(2);
    cout << "\x1B[2J\x1B[H";
    
    
    //Comecando jornada
    Piece paw1, paw2, paw3, paw4, paw5, paw6, paw7, paw8;
    Piece paws[8] = {paw1, paw2, paw3, paw4, paw5, paw6, paw7, paw8};
    
    paws[0].setPiece("paw", 1, 1 * 10, 1 * 5);
    for(int i = 0; i < 8; i++){
        paws[i].setPiece("paw", i + 1, (i + 1) * 10, (i + 1) * 5);
        cout << i << endl;
    }
    
    cout << paw3.name;
}
