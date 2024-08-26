#include <iostream>
#include <locale.h>
#include <unistd.h>
#include <array> 

using namespace  std;

class Protagonist {
  public:
    string name;   
    int level;
    int health;
    int maxHealth;
    int damage;
    bool blocking;
    bool running;

    void setProtagonist(string newName) {
         name = newName;
         level = 1;
         health = 100;
         maxHealth = 100;
         damage = 10;
         blocking = false;
         running = false;
     }
         
    void takeDamage(int damage){
        health -= damage;
    }
    
    void levelUp(){
        level += 1;
        maxHealth += 50;
        health += 50;
    }
    void heal(){
        health += level * 10;
        if(health > maxHealth){
            health = maxHealth;
        }
    }
    
};


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

    void takeDamege(int damage){
        health -= damage;
    }
    
};

void setPieces(Piece pieces[], string name, int level, int health, int damage, int variant1, int variant2){
    int length;
    if(name == "Peão"){
        length = 8;
    } else {
        length = 2;
    }
    for(int i = 0; i < length; i++){
        pieces[i].setPiece(name, i + level, ((i + 1) * health) + variant1, ((i + 1) * damage) + variant2);
    }
}

void enemyCombat(Protagonist &prot, Piece &piec){
    
    cout << "O inimigo esta te atacando!";
    sleep(1);
    if(prot.blocking == true){
        cout << "O ataque foi bloqueado";
        prot.blocking = false;
    } else {
        cout << "\nVoce recebeu " << piec.damage << " de dano";
        prot.takeDamage(piec.damage);
    }
    
    sleep(2);
    cout << "\x1B[2J\x1B[H";
}

void combat(Protagonist &me, Piece &enemy){
    int playerAtack;
    if(me.health > 0 && enemy.health > 0){
        
        bool repeat;
        do {
            repeat = false;
            cout << "\n\n";
            cout << "1. Atacar\n";
            cout << "2. Defender\n";
            cout << "3. Correr!\n";
            cout << "\n";
            cin >> playerAtack;

            int i  = rand() % 100 + 1;
                switch (playerAtack){
                case 1:
                    cout << "Atacando!";
                    sleep(1);
                    cout << "\nVoce deu " << me.damage << " de dano no inimigo!";
                    enemy.takeDamege(me.damage);     
                    break;
                case 2:
                    cout << "Defendendo";
                    sleep(1);
                    if(i >= 50){
                        me.blocking = true;
                    }
                        cout << "\nvoce tambem se cura em " << 10 * me.level;
                        me.heal();
                        sleep(1);
                    break;
                case 3:
                    cout << "Fugindo!!!";
                    me.running = true;
                    cout << "\n seu inimigo consegue lhe acertar um ultimo golpe antes de fugir, voce recebe " << enemy.damage / 2 << " de dano";
                    me.takeDamage(enemy.damage / 2);
                    break;
                default:
                cout << "Comando invalido!";
                repeat = true;
                break;
            }
            sleep(2);
            cout << "\x1B[2J\x1B[H";

        }
        while(repeat);
        
    }
    
}

void combatStats(Protagonist &protag, Piece &piec){
        cout << "Entrando em combate...";
        sleep(1);
        cout << "\x1B[2J\x1B[H";
        cout << "Você esta contra: " << piec.name;
        sleep(1);
        cout << "\x1B[2J\x1B[H";
    while(protag.health > 0 && piec.health > 0 && protag.running == false){
        cout << "Nome: " << protag.name << "        |       Nome da peca: " << piec.name << "\nNivel: " << protag.level << "          |       Nivel da peca: " << piec.level 
        << "\nVida: " << protag.health << "         |       Vida da peca: " << piec.health;

        combat(protag, piec);
        if(piec.health > 0 && protag.running == false){
            enemyCombat(protag, piec);
        }
        
    }
    if(protag.health > 0 && protag.running == true){
        cout << "com sorte voce escapou com vida";
    } else if(protag.health > 0 && protag.running == false){
        cout << "Parabens voce venceu!";
    } else {
        cout << "Voce foi de dormes :(";
    }
    
}

int main(){

    setlocale(LC_ALL, "Portuguese_Brazil");
    
    //Contando historia e criando personagem
    Protagonist protagonist;
    string name;
    cout << "Uma batalha foi travada, Brancas VS Pretas, foi uma guerra devastadora que terminou em 77 movimentos, todas as pecas pretas foram mortas exceto por voce, o rei preto\n Agora em um mundo governado pelo cruel Rei das Pecas Brancas, onde a liberdade foi suprimida e a justica e apenas uma lembranca.\nDeterminado a minar o poder do Imperio e restaurar a liberdade ao continente de Xadrez.\nSua missao e clara: desafiar a tirania e um dia, enfrentar o proprio Rei Branco.\nO destino do Xadrez depende de suas acoes." << endl;
    //sleep(3);
    cout << "Qual o seu nome ?" << endl;
    cin >> name;
    protagonist.setProtagonist(name);
    //sleep(1);
    cout << "\x1B[2J\x1B[H";
    cout << "Nome: " << protagonist.name << endl << "Nivel: " << protagonist.level << endl << "Vida: " << protagonist.health << endl;
    //sleep(2);
    cout << "\x1B[2J\x1B[H";
    
    
    //Construir inimigos
    Piece paw1, paw2, paw3, paw4, paw5, paw6, paw7, paw8, bishop1, bishop2, knight1, knight2, rook1, rook2, queen, king;

    Piece paws[8] = {paw1, paw2, paw3, paw4, paw5, paw6, paw7, paw8};
    Piece bishops[2] = {bishop1, bishop2};
    Piece knights[2] = {knight1, knight2};
    Piece rooks[2] = {rook1, rook2};
    
    setPieces(paws, "Peao", 1, 10, 5, 1, 1);
    setPieces(bishops, "Bispo", 3, 100, 30, 50, 0);
    setPieces(knights, "Cavalo", 3, 50, 30, 50, 30);
    setPieces(rooks, "Torre", 5, 80, 40, 100, 40);

    queen.setPiece("Rainha", 99, 500, 200);

    king.setPiece("Rei", 99, 1, 1);

    combatStats(protagonist, paws[0]);


}
