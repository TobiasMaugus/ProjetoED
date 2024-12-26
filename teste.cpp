#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
using namespace std;

#define NumMaxRegistros 4;

struct Registro{
    int id;
    string name;
    string team;
    string games;
    int year;
    string season;
};

struct Node{
    string filePath;
    int qtdRegistros;
    Node* proximo=nullptr;
};

class SequenceSet{
    private:
    //header
    int numSequences;
    Node* inicio;
    Node* ultimo;

    public:
    SequenceSet(){
        numSequences=0;
        inicio = NULL;
        ultimo = NULL;
    };

    void InsereOrdenado(Registro R){};
    void RemoveRegistro(int IdRemovido){};
    void buscarRegistro(int IdBuscado){};
};

//funcoes auxiliares que eu ainda irei arrumar estão comentadas(to reaproveitando de ialg)
void telaOpcoes(){
    system("clear||cls");
    cout<<"-------------------------------------------------------"<<endl;
	cout<<"|1 - ADICIONAR REGISTROS DE ARQUIVO CSV/TXT           |"<<endl;
	cout<<"|2 - ADICIONAR REGISTRO PELO TERMINAL                 |"<<endl;
	cout<<"|3 - BUSCAR REGISTRO                                  |"<<endl;
	cout<<"|4 - REMOVER REGISTRO                                 |"<<endl;
	cout<<"-------------------------------------------------------"<<endl;
	cout<<"|9 - SAIR DO PROGRAMA                                 |"<<endl;
	cout<<"-------------------------------------------------------"<<endl;
	cout<<"Digite o numero da acao que deseja realizar: ";
}

void printRegistro(Registro R){
    cout<<"- ID: "<<R.id<<" Name: "<<R.name<<" Team: "<<R.team<<" Games: "<<
    R.games<<" Year: "<<R.year<<" Season: "<<R.season<<endl;
}

// TipoJogador* importarBIN(const string& nomeArq, int& tam, int&posicoesPreenchidas) {
// 	struct structAUX {
// 		int id;
// 		char nome[40];
// 		int idade;
// 		int nivel;
// 		char classe[40];
// 	};
// 	posicoesPreenchidas=0;
// 	int tamanhoinicial=40;
// 	ifstream arquivo(nomeArq, ios::binary);

// 	if(arquivo) {
// 		arquivo.seekg(0, ios::end);
// 		streampos arquivoTAM = arquivo.tellg();
// 		arquivo.seekg(0, ios::beg);

// 		tam = arquivoTAM / sizeof(structAUX);

// 		//aloca a memoria do vetor auxiliar e calcula o tamanho do arquivo previamente
// 		structAUX* vetAUX = new structAUX[tam];
// 		arquivo.read(reinterpret_cast<char*>(vetAUX), sizeof(structAUX) * tam);
// 		bool controle=true;
// 		TipoJogador* vet = new TipoJogador[tam];


// 		while(posicoesPreenchidas <= tam and controle==true) {
// 			if(posicoesPreenchidas>=tamanhoinicial) {
// 				//redimensionando
// 				vet=redimensionaVetor(vet, tamanhoinicial, 10);
// 				tamanhoinicial = tamanhoinicial+10;
// 			}
// 			if(string(vetAUX[posicoesPreenchidas].nome)=="ZZZ POSICAO VAZIA ZZZ") {
// 				controle=false;
// 			}
// 			//adiciona as posicoes do vetor Auxiliar no vetor Principal
// 			vet=adicionaRegistro(vet, posicoesPreenchidas, vetAUX[posicoesPreenchidas].id,
// 			                     string(vetAUX[posicoesPreenchidas].nome),
// 			                     vetAUX[posicoesPreenchidas].idade,
// 			                     vetAUX[posicoesPreenchidas].nivel,
// 			                     string(vetAUX[posicoesPreenchidas].classe));
// 			posicoesPreenchidas++;
// 		}
// 		//inativa posicoes que nao serao preenchidas
// 		for(int k=posicoesPreenchidas; k<tamanhoinicial; k++) {
// 			vet=InativarPosicao(vet, k);
// 		}
// 		delete[] vetAUX;

// 		arquivo.close();
// 		tam=tamanhoinicial;
// 		return vet;
// 	} else {
// 		return nullptr;
// 		tam=0;
// 		posicoesPreenchidas=0;
// 	}
// }



// void exportarBinario(TipoJogador* vet, const string& nomeArquivo, int tam) {
// 	struct structAUX {
// 		int id;
// 		char nome[40];
// 		int idade;
// 		int nivel;
// 		char classe[40];
// 	};
// 	structAUX* vetAUX = new structAUX[tam];

// // Copia de dados entre os vetores
// 	for (int i = 0; i < tam; i++) {
// 		vetAUX[i].id = vet[i].id;
// 		strncpy(vetAUX[i].nome, vet[i].nome.c_str(), sizeof(vetAUX[i].nome) - 1);
// 		vetAUX[i].idade = vet[i].idade;
// 		vetAUX[i].nivel = vet[i].nivel;
// 		strncpy(vetAUX[i].classe, vet[i].classe.c_str(), sizeof(vetAUX[i].classe) - 1);
// 	}

// 	ofstream arquivo(nomeArquivo, ios::binary);
// 	if (arquivo) {
// 		//escrita no arquivo .dat
// 		arquivo.write((const char*)(vetAUX), sizeof(structAUX) * tam);
// 		arquivo.close();
// 		cout << "arquivo "<<nomeArquivo<<" lido com sucesso."<<endl;
// 	} else {
// 		cout<<"Erro ao ler o arquivo!!"<<endl;
// 	}

// 	delete[] vetAUX;
// }



//IMPORTARCSV
// arquivo2.open(nomeArquivo);


// 				if (arquivo2) {
// 					string linha2;
// 					std::getline(arquivo2, linha2);  // Descartar a primeira linha
// 					arquivo2.tellg();

// 					posicoesPreenchidas = 0;
// 					tam = 40;
// 					delete [] Jogadores;
// 					Jogadores = nullptr;
// 					Jogadores = new Jogador[tam];


// 					while(getline(arquivo2, linha2)) {
// 						if (linha2.empty()) {
// 							continue;
// 						}
// 						stringstream ss2(linha2);
// 						getline(ss2,idAUX,';');
// 						getline(ss2,nomeAUX,';');
// 						getline(ss2,idadeAUX,';');
// 						getline(ss2,nivelAUX,';');
// 						getline(ss2,classeAUX);

// 						nomeAUX.erase(0,1);
// 						nomeAUX.pop_back();
// 						classeAUX.erase(0,1);
// 						classeAUX.pop_back();

// 						if(posicoesPreenchidas>=tam) {
// 							Jogadores=redimensionaVetor(Jogadores, tam, incremento);
// 							tam = tam+incremento;
// 						}
// 						Jogadores=adicionaRegistro(Jogadores, posicoesPreenchidas, stoi(idAUX), nomeAUX, stoi(idadeAUX), stoi(nivelAUX), classeAUX);

// 						posicoesPreenchidas++;
// 					}
// 					cout<<"Arquivo "<< nomeArquivo <<" lido com sucesso!!"<<endl;
// 					arquivo2.close();
// 				} else {
// 					cout<<"Arquivo "<<nomeArquivo<<" nao pode ser aberto ";
// 				}



int main(){
    int opcao;
    string nomeArquivoCSV;

    do{
		telaOpcoes();
		cin>>opcao;
        switch (opcao){
            case 1:
            break;

            case 2:
            break;

            case 3:
            break;

            case 4:
            break;

            default:
                cout<<"OPCAO INVALIDA!";
        }
        cout<<"\nTecle ENTER para continuar...";
		cin.ignore().get();
    }while(opcao!=9);
    
    return 0;
}
