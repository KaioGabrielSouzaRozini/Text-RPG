#include <iostream>
#include <locale.h>
#include <unistd.h>
#include <array> 
#include <cstdlib> 
#include <time.h> 

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
    int xp;

    void setProtagonist(string newName) {
         name = newName;
         level = 1;
         health = 100;
         maxHealth = 100;
         damage = 10;
         blocking = false;
         running = false;
         xp = 0;
     }
         
    void takeDamage(int damage){
        health -= damage;
    }
    
    void levelUp(string name){

        if(name == "Peao"){
            xp += 50;
            cout << "Voce ganhou 50 de xp!\n";
            sleep(1);
        } else {
            xp += 100;
            cout << "Voce ganhou 100 de xp!\n";
            sleep(1);
        }
        
        if(xp >= 100){
            level += 1;
            maxHealth += 30;
            health += 30;
            xp = 0;
            cout << "Voce subiu de nivel!\n";
        }
        
    }
    void heal(){
        health += level * 20;
        if(health > maxHealth){
            health = maxHealth;
        }
    }
    
};


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

void setPieces(Piece* pieces[], string name, int level, int health, int damage, int variant1, int variant2){
    int length;
    if(name == "Peao"){
        length = 8;
    } else {
        length = 2;
    }
    for(int i = 0; i < length; i++){
        pieces[i]->setPiece(name, i + level, ((i + 1) * health) + variant1, ((i + 1) * damage) + variant2);
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
        cout << "com sorte voce escapou com vida\n";
        sleep(2);
        cout << "\x1B[2J\x1B[H";
    } else if(protag.health > 0 && protag.running == false){
        cout << "Parabens voce venceu!\n";
        sleep(1);
        protag.levelUp(piec.name);
        sleep(2);
        cout << "\x1B[2J\x1B[H";
    } else {
        cout << "Voce foi de dormes :(";
    }
    protag.running = false;
    
}

void moving(Protagonist &protagonist, Piece &piece) {
    int choice;
    cout << "Nome: " << protagonist.name  << "\nNivel: " << protagonist.level
        << "\nVida: " << protagonist.health <<  "\nDano: " << protagonist.damage << endl;
    
        cout << "\n1. Andar por ai\n";
        cout << "2. Descansar\n";
        cout << "3. treinar\n\n";
        
        cin >> choice;
        int i  = rand() % 100 + 1;
        
        switch(choice){
            case 1:
                cout << "Andando..." << endl;
                sleep(2);
                if(i >= 30){
                    cout << "Voce encontrou um inimigo!\n";
                    sleep(1);
                    combatStats(protagonist, piece);
                } else {
                    cout << "Voce encontrou um item!\n";
                    sleep(1);
                    int item = rand() % 7 + 1;
                    protagonist.damage += item;
                    cout << "seu dano aumentou em " << item;
                    sleep(2);
                    cout << "\x1B[2J\x1B[H";
                }
                break;
            case 2:
                cout << "Descansando...\n";
                protagonist.heal();
                sleep(1);
                cout << "Voce se curou em " << protagonist.level * 20 << " pontos de vida\n";
                sleep(2);
                cout << "\x1B[2J\x1B[H";
                break;
            case 3:
                cout << "treinando...\n";
                break;
        }
}

void dialog(Protagonist &protag, Piece &piec, string dial){
    string name;
    cout << "Nome: " << protag.name << "        |       Nome da peca: " << piec.name << "\nNivel: " << protag.level << "          |       Nivel da peca: " << piec.level 
        << "\nVida: " << protag.health << "         |       Vida da peca: " << piec.health;

    cout << "\n\n" << dial << endl;

    sleep(3);
    cout << "precione qualquer tecla e depois enter para continuar";

    cin >> name;
    cout << "\x1B[2J\x1B[H";
}

int main(){

    setlocale(LC_ALL, "Portuguese_Brazil");

    srand(time(0));
    
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
    
    Piece* ppaw1 = &paw1;
    Piece* ppaw2 = &paw2;
    Piece* ppaw3 = &paw3;
    Piece* ppaw4 = &paw4;
    Piece* ppaw5 = &paw5;
    Piece* ppaw6 = &paw6;
    Piece* ppaw7 = &paw7;
    Piece* ppaw8 = &paw8;
    
    Piece* pbishop1 = &bishop1;
    Piece* pbishop2 = &bishop2;
    
    Piece* pknight1 = &knight1;
    Piece* pknight2 = &knight2;
    
    Piece* prook1 = &rook1;
    Piece* prook2 = &rook2;

    Piece* paws[8] = {ppaw1, ppaw2, ppaw3, ppaw4, ppaw5, ppaw6, ppaw7, ppaw8};
    Piece* bishops[2] = {pbishop1, pbishop2};
    Piece* knights[2] = {pknight1, pknight2};
    Piece* rooks[2] = {prook1, prook2};
    
    setPieces(paws, "Peao",  1, 10, 5, 1, 1);
    
    setPieces(bishops, "Bispo", 3, 100, 30, 50, 0);
    setPieces(knights, "Cavalo", 3, 50, 30, 50, 30);
    setPieces(rooks, "Torre", 5, 80, 40, 100, 40);

    queen.setPiece("Rainha", 99, 500, 200);

    king.setPiece("Rei", 99, 1, 1);

    Piece allPieces[14] = {paw1, paw2, paw3, paw4, paw5, paw6, paw7, paw8, bishop1, bishop2, knight1, knight2, rook1, rook2};
    
    /*
    bool final;
    do{
        final = true;
        int j;
        do{
            j  = rand() % 14;
        } while(allPieces[j].health <= 0);
        
        moving(protagonist, allPieces[j]);

        if(allPieces[0].health <= 0 && allPieces[1].health <= 0 && allPieces[2].health <= 0 && allPieces[3].health <= 0 
        && allPieces[4].health <= 0 && allPieces[5].health <= 0 && allPieces[6].health <= 0 && allPieces[7].health <= 0 
        && allPieces[8].health <= 0 && allPieces[9].health <= 0 && allPieces[10].health <= 0 && allPieces[11].health <= 0
        && allPieces[12].health <= 0 && allPieces[13].health <= 0){
            final = false;
        }
    } while(final);

    */

    cout << "Parabens! voce conseguiu derrotar todas as pecas brancas!\n";
    cout << "Agora só resta subir o castelo onde o rei esta\n";
    cout << "voce sobre toda a escadaria e la esta ele, O Rei Branco\n";

    cout << "\x1B[2J\x1B[H";

    dialog(protagonist, king, "Eu: (Entrando na sala do trono, espadas em maos) Finalmente, estamos cara a cara, depois de todo o sangue que derramei para chegar ate aqui.");
    dialog(protagonist, king, "Rei Branco: (Com um olhar calmo, mas cansado) Voce veio para vingar o que perdi, nao e? Seu trono, sua gloria... sua honra. Mas me diga, valeu a pena o caminho de destruicao ate aqui?");
    dialog(protagonist, king, "Eu: Cada passo, cada batalha. Eu vim terminar o que voce começou quando tomou meu reino e massacrou meu povo.");
    dialog(protagonist, king, "Rei Branco: (Se levantando do trono, sem empunhar armas) E agora voce esta diante de sua vinganca. Mas antes de empunhar sua espada contra mim, considere o que realmente deseja. Morte? Justica? Ou apenas o fim deste ciclo de odio?");
    dialog(protagonist, king, "Rei Derrotado: Suas palavras sao vazias. Você não merece misericordia.");
    dialog(protagonist, king, "Rei Inimigo: Talvez. Mas pense no que vem depois. Mate-me, e você se tornara o monstro que jurei derrotar. Poupe-me, e talvez possamos encontrar um caminho melhor... ou faca algo inesperado e una forcas contra um inimigo maior que ambos.");

}
