#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <set>

enum class ClasseBioquimica {          
    POLAR = 0,      //'P'
    NAO_POLAR = 1,  //'N'
    ACIDO = 2,      //'A'
    BASE = 3,       //'B'
    TERMINAL = 4    // chain[0] e chain[n+1]
};

//Matriz de Afinidades (5x5)
const unsigned int Afinidades[5][5] = {
    //    P, N, A, B, T
    /*P*/{1, 3, 1, 3, 1}, 
    /*N*/{5, 1, 0, 1, 1},
    /*A*/{0, 1, 0, 4, 1}, 
    /*B*/{1, 3, 2, 3, 1}, 
    /*T*/{1, 1, 1, 1, 0}
};

// Converte o Char do input ('P') para o Enum
ClasseBioquimica CharParaEnum(char c) {
    switch (c) {
        case 'P': return ClasseBioquimica::POLAR;
        case 'N': return ClasseBioquimica::NAO_POLAR;
        case 'A': return ClasseBioquimica::ACIDO;
        case 'B': return ClasseBioquimica::BASE;
        default : return ClasseBioquimica::TERMINAL;
    }
}

class Aminoacido {
private:
    unsigned long long energiaPotencial;
    ClasseBioquimica classe;

public:
    Aminoacido(){}

    Aminoacido(unsigned long long ep, ClasseBioquimica cb): energiaPotencial(ep), classe(cb){}
  
    unsigned long long getEnergia() const{return energiaPotencial;}
    ClasseBioquimica getClasse() const{return classe;}
    
    unsigned long long Afinidade(const Aminoacido *outro) const{
        unsigned long long i = static_cast<unsigned long long>(this->classe);
        unsigned long long j = static_cast<unsigned long long>(outro->getClasse());
        return Afinidades[i][j];
    }
};

struct BinaryNode{
    unsigned long long val;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(unsigned long long value) : val(value), left(NULL), right(NULL) {} 

    BinaryNode(unsigned long long value, BinaryNode *bnleft, BinaryNode *bnright) : val(value), left(bnleft), right(bnright) {} 

    void setLeft(BinaryNode *bn){left = bn;}

    void setRight(BinaryNode *bn){right = bn;}
    
    /*
    Aqui imprime-se para o terminal a sequência diretamente ao percorrer a árvore, para evitar perdas de eficiência
    com concatenação.
    */
    void print(){
        if (left!=NULL){
            left->print();
            printf(" ");
        }
        if (right!=NULL){
            right->print();
            printf(" ");
        }
        printf("%llu",val);
    }
};

unsigned long long getRemovalEnergy(Aminoacido *a1, Aminoacido *a2, Aminoacido *a3){
    return a2->getEnergia()*(a1->getEnergia() * a1->Afinidade(a2) + a3->getEnergia() * a2->Afinidade(a3));
}

void maxEnergy(unsigned long long n,std::vector<Aminoacido*> chain){
    std::vector<std::vector<unsigned long long>> maxEnergy(n,std::vector<unsigned long long>(n,0));
    std::vector<std::vector<BinaryNode*>> removalSequence(n,std::vector<BinaryNode*>(n,NULL));
    for (unsigned long long interval = 2; interval <= n; interval++){
        for (unsigned long long left = 0; left < n - interval; left++){
            unsigned long long right = left + interval;
            for (unsigned long long i = left + 1;i < right;i++){
                unsigned long long sequenceEnergy = getRemovalEnergy(chain[left],chain[i],chain[right]) + maxEnergy[left][i] + maxEnergy[i][right];
                if (sequenceEnergy >= maxEnergy[left][right]){ //O >= aqui é ESSENCIAL para garantir ordem lexicográfica
                    maxEnergy[left][right] = sequenceEnergy;
                    removalSequence[left][right] = new BinaryNode(i,removalSequence[left][i],removalSequence[i][right]);
                }
            }
        }
    }
    printf("%llu\n",maxEnergy[0][n-1]);

    removalSequence[0][n-1]->print();
    printf("\n");
}

int main() {
    unsigned long long n;

    //Ler número de aminoacidos
    if(scanf("%llu",&n) != 1){
        printf("Error reading n\n");
        return -1;
    }

    //Ler energias potenciais
    std::vector<unsigned long long> potenciais(n);
    for (unsigned long long i = 0; i < n; i++){
        if(scanf("%llu",&potenciais[i])!=1){
            printf("Error reading potencial\n");
            return -1; 
        }
    }

    //Ler classes bioquímicas
    std::vector<char> classes(n + 1); 
    if(scanf("%s",classes.data())!=1){
        printf("Error reading classes\n");
        return -1;
    }

    //Criar cadeia de aminoácidos
    std::vector<Aminoacido*> chain(n+2);
    chain[0]=(new Aminoacido(1,CharParaEnum('T')));
    chain[n+1]=(new Aminoacido(1,CharParaEnum('T')));
    
    for (unsigned long long i = 1; i <= n; ++i) {
        ClasseBioquimica tipo = CharParaEnum(classes[i-1]);
        chain[i]=new Aminoacido(potenciais[i-1], tipo);
    }

    maxEnergy(n+2,chain);
    return 0;
}