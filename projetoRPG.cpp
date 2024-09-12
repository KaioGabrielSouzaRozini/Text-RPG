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
    int action;
    bool pawHelp;

    void setProtagonist(string newName) {
         name = newName;
         level = 1;
         health = 100;
         maxHealth = 100;
         damage = 10;
         blocking = false;
         running = false;
         xp = 0;
         action = 3;
         pawHelp = false;
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
            maxHealth += 50;
            health += 50;
            if(xp == 150){
                xp = 50;
            } else {
                xp = 0;
            }
            
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
        sleep(2);
        cout << "\x1B[2J\x1B[H";
    }
    protag.running = false;
    
}

void moving(Protagonist &protagonist, Piece &piece) {
    int choice;
    cout << "Nome: " << protagonist.name  << "\nNivel: " << protagonist.level
        << "\nVida: " << protagonist.health <<  "\nDano: " << protagonist.damage 
        << "\nAcoes: " << protagonist.action << endl;
    
        cout << "\n1. Andar por ai\n";
        cout << "2. Descansar\n";
        cout << "3. treinar\n\n";
        
        cin >> choice;
        int i  = rand() % 100 + 1;
        
        switch(choice){
            case 1:
                cout << "Andando..." << endl;
                sleep(2);
                if(i >= 35){
                    cout << "Voce encontrou um inimigo!\n";
                    sleep(1);
                    combatStats(protagonist, piece);
                    protagonist.action = 3;
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
            if(protagonist.action <= 0) {
                cout << "Voce precisa ir dar uma caminhada...";
                sleep(3);
                cout << "\x1B[2J\x1B[H";
            } else {
                cout << "Descansando...\n";
                protagonist.heal();
                protagonist.action -= 1;
                sleep(1);
                cout << "Voce se curou em " << protagonist.level * 20 << " pontos de vida\n";
                sleep(2);
                cout << "\x1B[2J\x1B[H";
            }
                break;
            case 3:
            if(protagonist.action <= 0) {
                cout << "Voce precisa ir dar uma caminhada...";
                sleep(3);
                cout << "\x1B[2J\x1B[H";
            } else {
                cout << "treinando...\n";
                protagonist.damage += protagonist.level * 2;
                protagonist.action -= 1;
                sleep(1);
                cout << "Voce treinou muito e conseguiu melhorar suas habilidades de combate!\n";
                sleep(1);
                cout << "seu dano aumenta em " << protagonist.level * 2; 
                sleep(2);
                cout << "\x1B[2J\x1B[H";
            }
                break;
            default:
                cout << "Comando invalido!";
                sleep(2);
                cout << "\x1B[2J\x1B[H";
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

      string title  ="   _____ _                     ______                 _            \n"
                     "  / ____| |                   |  ____|               (_)           \n"
                     " | |    | |__   ___  ___ ___  | |__   _ __ ___  _ __  _ _ __ ___   \n"
                     " | |    | '_  |/ _ |/ __/ __| |  __| | '_ ` _ || '_ || | '__/ _ |  \n"
                     " | |____| | | |  __/|__ |__ | | |____| | | | | | |_) | | | |  __/  \n"
                     "  L ____|_| |_||___||___/___/ |______|_| |_| |_| .__/|_|_|  |___|  \n"
                     "                                             | |                   \n"
                     "                                             |_|                   \n";

    cout << "Bem vindo ao meu RPG de Texto!";
    sleep(3);
    cout << "\x1B[2J\x1B[H";

    cout << title << endl;   
    sleep(5);
    cout << "\x1B[2J\x1B[H";                                     
    
    //Contando historia e criando personagem
    Protagonist protagonist;
    string name;
    cout << "Uma batalha foi travada, Brancas VS Pretas, foi uma guerra devastadora que terminou em 77 movimentos, todas as pecas pretas foram mortas exceto por voce, o rei preto\nAgora em um mundo governado pelo cruel Rei das Pecas Brancas, onde a liberdade foi suprimida e a justica e apenas uma lembranca.\nDeterminado a minar o poder do Imperio e restaurar a liberdade ao continente de Xadrez.\nSua missao e clara: desafiar a tirania e um dia, enfrentar o proprio Rei Branco.\nO destino do Xadrez depende de suas acoes." << endl;
    sleep(3);
    cout << "Qual o seu nome ?" << endl;
    cin >> name;
    protagonist.setProtagonist(name);
    sleep(1);
    cout << "\x1B[2J\x1B[H";
    cout << "Nome: " << protagonist.name << endl << "Nivel: " << protagonist.level << endl << "Vida: " << protagonist.health << endl;
    sleep(2);
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

    queen.setPiece("Rainha", 99, 700, 180);

    king.setPiece("Rei", 99, 1, 1);

    Piece allPieces[14] = {paw1, paw2, paw3, paw4, paw5, paw6, paw7, paw8, bishop1, bishop2, knight1, knight2, rook1, rook2};
    
    int help;
    cout << "antes de comecar sua jornada, voce percebe um pequeno peao preto caido nos escombros, ele ainda nao morreu\n";
    sleep(1);
    cout << "peao: meu rei por favor acabe com meu sofrimento...\n";
    sleep(1);
    cout << "1. ajudar o peao\n"
            "2. executar o peao";
    cin >> help;
    if(help == 1){
        cout << "voce o ajuda, cuida de seus ferimentos e o carrega por uma longa distancia até um lugar seguro,\n"
                "ele lhe agradece muito pela ajuda e jura o recompensar,\n";
                sleep(3);
        cout << "infelizmente durante o caminho voce se cansa, acaba caindo e se machuca diversas vezes, voce perde 40 de vida";
        protagonist.takeDamage(40);
        protagonist.pawHelp = true;
    } else if(help == 2){
        cout << "voce corta a cabeça do peao, com o sangue em suas mãos voce jura vingalo em sua jornada...";
    } else {
        cout << "voce o deixa ali e segue em frente...";
    }
    
    sleep(5);
    cout << "\x1B[2J\x1B[H";
    //sistema de historia e combate
    bool final;
    do{
        final = true;
        int j;
        do{
            j  = rand() % 14;
        } while(allPieces[j].health <= 0);
        
        if(protagonist.health <= 0){
            final = false;
        }
        moving(protagonist, allPieces[j]);
        if(protagonist.health <= 0){
            final = false;
        }
        if(allPieces[0].health <= 0 && allPieces[1].health <= 0 && allPieces[2].health <= 0 && allPieces[3].health <= 0 
        && allPieces[4].health <= 0 && allPieces[5].health <= 0 && allPieces[6].health <= 0 && allPieces[7].health <= 0 
        && allPieces[8].health <= 0 && allPieces[9].health <= 0 && allPieces[10].health <= 0 && allPieces[11].health <= 0
        && allPieces[12].health <= 0 && allPieces[13].health <= 0){
            final = false;
        }
    } while(final);

    
    if(protagonist.health <= 0) {
        cout << "Voce lutou bravamente, mas o inimigo era muito forte, voce deixou esta terra buscando o seu sonho...";
    } else {
        cout << "Parabens! voce conseguiu derrotar todas as pecas brancas!\n";
        sleep(3);
        cout << "Agora so resta subir o castelo onde o rei esta\n";
        sleep(3);
        cout << "voce sobe toda a escadaria e la esta ele, O Rei Branco\n";
        sleep(3);
        cout << "Mas espere, algo esta errado, voce sente um calafrio subindo pela sua espinha, seus batimentos aceleram, voce sente como se estivesse prestes a morrer e entao...\n";
        sleep(3);
        cout << "Das sombras surje...\n";
        sleep(3);
        cout << "A Rainha Branca!";
        sleep(5);
        cout << "\x1B[2J\x1B[H";

        sleep(2);
        
        if(protagonist.pawHelp){
            cout << "Mestre!\n"
                    "Eu voltei para lhe ajudar!\n"
                    "com um furioso golpe em um ponto vital da rainha Branca o pequeno a acerta causando 200 de dano!\n\n";
            sleep(2);
            cout << "Logo em seguida a rainha se vira e o acerta em cheio, o pequeno peao cai...\n";
            cout << "voce tenta o ajudar mas ele esta quase morto, ele entrega a sua espada e como suas palavras finais ele diz\n";
            sleep(2);
            cout << "VIDA LONGA AO REI!\n";
            
            sleep(3);
            
            cout << "A espada era super afiada e voce ganha 30 de ataque!";
            sleep(4);
            queen.health -= 200;
            protagonist.damage += 30;
        }
        
        combatStats(protagonist, queen);

        //Finais
        if(queen.health > 0){
            cout << "A rainha era muito forte, voce se retira, isolado e sem dignidade, voce jura voltar um dia e terminar oque comecou";
        } else {
            cout << "\x1B[2J\x1B[H";

            dialog(protagonist, king, "Eu: (Entrando na sala do trono, espadas em maos) Finalmente, estamos cara a cara, depois de todo o sangue que derramei para chegar ate aqui.");
            dialog(protagonist, king, "Rei Branco: (Com um olhar calmo, mas cansado) Voce veio para vingar o que perdi, nao e? Seu trono, sua gloria... sua honra. Mas me diga, valeu a pena o caminho de destruicao ate aqui?");
            dialog(protagonist, king, "Eu: Cada passo, cada batalha. Eu vim terminar o que voce comecou quando tomou meu reino e massacrou meu povo.");
            dialog(protagonist, king, "Rei Branco: (Se levantando do trono, sem empunhar armas) E agora voce esta diante de sua vinganca. Mas antes de empunhar sua espada contra mim, considere o que realmente deseja. Morte? Justica? Ou apenas o fim deste ciclo de odio?");
            dialog(protagonist, king, "Eu: Nao posso confiar em um ditador como voce");
            dialog(protagonist, king, "Rei Branco: Talvez. Mas pense no que vem depois. Mate-me, e voce se tornara o monstro que jurei derrotar. Poupe-me, e talvez possamos encontrar um caminho melhor... ou faca algo inesperado e una forcas contra um inimigo maior que ambos.");

            int choose;
            cout << "1. Xeque-mate: Matar o rei branco\n"
                    "2. En passant: Exilar o rei branco\n"
                    "3. Draw: Perdoar o rei branco\n";

            cin >> choose;

            if(choose == 1){
                cout << "Eu: Nao ha caminho melhor para nos. Hoje, voce paga por tudo.\n\n";
                sleep(5);
                cout << "Rei Branco: (Sorriso amargo) Entao este e o fim... Que minha morte pese sobre sua consciencia para sempre.\n\n";
                sleep(5);
                cout << "Eu: (Atinge o rei branco com sua espada) Adeus, velho inimigo. Finalmente, meu reino esta vingado.\n\n";
                sleep(5);
                cout << "(O sangue do rei branco mancha o cho. O silêncio ecoa no salão do trono. O novo rei assume, mas em seu coração, a paz nunca vira. O ciclo de odio continua, agora com ele no comando.)";
                
            } else if (choose == 2){
                cout << "Eu: Nao. Nao matarei você. O ciclo de vinganca termina aqui. Eu o exilo deste reino para nunca mais retornar.\n\n";
                sleep(5);
                cout << "Rei Branco: (Olhos arregalados, incredulo) Voce... me poupa? Por que?\n\n";
                sleep(5);
                cout << "Eu: Porque nao quero ser como você. Vou governar com justica, algo que você jamais fez.\n\n";
                sleep(5);
                cout << "Rei Branco: (Abaixando a cabeca) Talvez... talvez haja redenção para mim apos tudo isso. Obrigado... por esta segunda chance.\n\n";
                sleep(5);
                cout << "(O rei branco e exilado, e o novo governante e celebrado por sua sabedoria e misericordia. Uma nova era de paz começa, guiada pela escolha inesperada do perdao.)";
            } else {
                cout << "Eu: Talvez tenha razao. A morte nao e o caminho. Vamos por nossas diferencas de lado. Nossos reinos precisam de paz.\n\n";
                sleep(5);
                cout << "Rei Branco: (Surpreso) Você sugere... uma alianca? Apos tudo o que fiz?\n\n";
                sleep(5);
                cout << "Eu: Sim. Mas saiba que a confianca deve ser construida. Lute ao meu lado e prove seu valor.\n\n";
                sleep(5);
                cout << "Rei Branco: (Com um aceno firme) Entao que assim seja. Por nossos povos, lutaremos juntos.\n\n";
                sleep(5);
                cout << "Unidos por uma causa comum, os dois antigos inimigos formam uma alianca inesperada. Juntos estabelecem um novo capitulo de cooperacao entre seus reinos.";
            }
        }

    }

    sleep(20);
    cout << "\x1B[2J\x1B[H";

    cout << "Muito obrigado por jogar!\n\n";
    cout << title;
}
