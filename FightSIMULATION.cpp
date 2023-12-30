#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Classe base (� abstrata)
class Personagem {
protected:
    std::string nome;
    int vida;

public:
    // construtor 
    Personagem(const std::string& nome, int vida) : nome(nome), vida(vida) {}

    // Tabela virtual usando metodos virtuais puros
    virtual void atacar() const = 0;
    virtual void defender() const = 0;

    void exibirStatus() const {
        std::cout << "\nNome: " << nome << " - Vida: " << vida << std::endl;
    }

    std::string GetName() const {
        return nome;
    }

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) {
            vida = 0;
        }
    }
};

// Classe intermediaria derivada da classe Personagem para mostrar hierarquia de classes
class Lutador : public Personagem {
protected:
    int forca;

public:
    Lutador(const std::string& nome, int vida, int forca) : Personagem(nome, vida), forca(forca) {}

	//sobescri��o do metodo virtual da classe base
    void atacar() const override {
        std::cout << nome << " atacando com forca " << forca << " \n" << std::endl;
    }

    void defender() const override {
        std::cout << nome << " defendendo " << std::endl;
    }
};

// Classe derivada da classe lutador
class Mago : public Lutador {
protected:
    int poderMagico;

public:
    Mago(const std::string& nome, int vida, int forca, int poderMagico)
        : Lutador(nome, vida, forca), poderMagico(poderMagico) {}
        
	//sobescri��o do metodo
    void atacar() const override {
        std::cout << nome << " lan�ando feiti�o com poder m�gico de " << poderMagico << "!" << std::endl;
    }

    void defender() const override {
        std::cout << nome << " conjurando escudo m�gico! \n" << std::endl;
    }
};

// Classe derivada da classe lutador
class Guerreiro : public Lutador {
protected:
    int resistenciaArmadura;

public:
    Guerreiro(const std::string& nome, int vida, int forca, int resistenciaArmadura)
        : Lutador(nome, vida, forca), resistenciaArmadura(resistenciaArmadura) {}

    void atacar() const override {
        std::cout << nome << " atacando com for�a de " << forca << " e usando resist�ncia de armadura de "
                  << resistenciaArmadura << "!" << std::endl;
    }

    void defender() const override {
        std::cout << nome << " usando escudo para se proteger! \n" << std::endl;
    }
};

class Inimigo {
private:
    int vida;
    int forcaAtaque;

public:
    Inimigo(int vida, int forcaAtaque) : vida(vida), forcaAtaque(forcaAtaque) {}

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) {
            vida = 0;
        }
    }

    bool estaVivo() const {
        return vida > 0;
    }

    void exibirStatus() const {
        std::cout << "\t Inimigo - Vida: " << vida << std::endl;
    }

    void atacar() const {
        std::cout << "\t Inimigo atacando com for�a " << forcaAtaque << " \n" << std::endl;
    }

    int getForcaAtaque() const {
        return forcaAtaque;
    }
};

int main() {

    // gera��o de n�meros aleat�rios
    std::srand(std::time(0));

    // Criando instancias de personagens
    Mago merlin("Merlin", 100, 20, 30);
    Guerreiro arthur("Arthur", 120, 25, 40);

    Inimigo inimigo(80, 15);

   	//uso do vetor para armazenar ponteiros das classes derivadas de diferentes tipos
   	// isso permite a cria��o do ambiente polim�rfico
    std::vector<Personagem*> personagens;

    // adi��o de personagens como ponteiros ao vetor 
    // eles est�o sendo adicionados como ponteiros para objetos da classe base
    personagens.push_back(&merlin);
    personagens.push_back(&arthur);


    while (inimigo.estaVivo()) {
        inimigo.exibirStatus();

        std::cout << "Escolha o personagem (0 para Merlin, 1 para Arthur): ";
        size_t escolha;
        std::cin >> escolha;

        if (escolha < personagens.size()) {

            personagens[escolha]->exibirStatus();
			
			// Chamada polim�rficas, elas v�o chamar o metodo baseado no persoangem que estiver em escolha
            personagens[escolha]->atacar();
            personagens[escolha]->defender();

			//calculo para recebimento de dano no inimigo
            int danoPersonagem = std::rand() % 20 + 10;
            inimigo.receberDano(danoPersonagem);

            std::cout << "\t Inimigo recebeu " << danoPersonagem << " de dano. \n" << std::endl;

            if (inimigo.estaVivo()) {
            	
                inimigo.atacar();

				//calculo para recebimento de dano no personagem
                int danoInimigo = std::rand() % 15 + 5;
                personagens[escolha]->receberDano(danoInimigo);

                std::cout << "\t " << personagens[escolha]->GetName() << " recebeu " << danoInimigo
                          << " de dano do inimigo. \n" << std::endl;
            }
        } else {
            std::cout << "Escolha inv�lida!" << std::endl;
        }

        std::cout << std::endl;
    }

    std::cout << "Inimigo derrotado!" << std::endl;

    // libera��o de memoria
    for (size_t i = 0; i < personagens.size(); ++i) {
        delete personagens[i];
    }

    return 0;
}

