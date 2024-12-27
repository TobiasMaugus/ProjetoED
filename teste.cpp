#include<iostream>//utilizar cout e cin
#include<fstream>//ler arquivos
#include<sstream>//fazer leitura de strings com espaco de forma mais eficaz
#include<stdlib.h>//limpar o terminal utilizando system
#include<cstring>//realizar conversoes BINARIO-STRING

const int NUM_MAX_REGISTROS = 4;

using namespace std;

struct Registro{
    int id;
    string name;
    string team;
    string games;
    int year;
    string season;
};

struct Node{
    string filePath="";
    int qtdRegistros=0;
    Node* proximo=nullptr;
    int menorIdDoProximoNode=0;
};

 struct structAUX {
	int id;
	char name[50];
	char team[50];
	char games[50];
    int year;
	char season[50];
};

Registro* importarBIN(const string& nomeArq) {
 	ifstream arquivo(nomeArq, ios::binary);

    if(arquivo) {
		arquivo.seekg(0, ios::beg);

        structAUX* vetAUX = new structAUX[NUM_MAX_REGISTROS];
        Registro* Registros = new Registro[NUM_MAX_REGISTROS];
        arquivo.read(reinterpret_cast<char*>(vetAUX), sizeof(structAUX) * NUM_MAX_REGISTROS);
        

        for(int i=0; i<NUM_MAX_REGISTROS; i++){
            Registros[i].id=vetAUX[i].id;
            Registros[i].name=vetAUX[i].name;
            Registros[i].team=vetAUX[i].team;
            Registros[i].games=vetAUX[i].games;
            Registros[i].year=vetAUX[i].year;
            Registros[i].season=vetAUX[i].season;
        }


        delete[] vetAUX;
        arquivo.close();
        return Registros;
    }else{
        cout<<endl<<"Erro ao ler arquivo"<<endl;
        return nullptr;
    }
}

void exportarBinario(Registro* Registros, const string& nomeArquivo) {
   structAUX* vetAUX = new structAUX[NUM_MAX_REGISTROS];

// Copia de dados entre os vetores
	for (int i = 0; i < NUM_MAX_REGISTROS; i++) {
		vetAUX[i].id = Registros[i].id;
		strncpy(vetAUX[i].name, Registros[i].name.c_str(), sizeof(vetAUX[i].name) - 1);
		strncpy(vetAUX[i].team, Registros[i].team.c_str(), sizeof(vetAUX[i].team) - 1);
        strncpy(vetAUX[i].games, Registros[i].games.c_str(), sizeof(vetAUX[i].games) - 1);
        vetAUX[i].year = Registros[i].year;
		strncpy(vetAUX[i].season, Registros[i].season.c_str(), sizeof(vetAUX[i].season) - 1);
	}

    ofstream arquivo(nomeArquivo, ios::binary);
    if (arquivo) {
		//escrita no arquivo .dat
		arquivo.write((const char*)(vetAUX), sizeof(structAUX) * NUM_MAX_REGISTROS);
		arquivo.close();
		cout << "arquivo "<<nomeArquivo<<" lido com sucesso. "<<endl;
	} else {
		cout<<"Erro ao ler o arquivo!! "<<endl;
	}
    delete [] vetAUX;
}


bool verificaSeEhRegistroVazio(Registro R){
    if(R.id==-1){
        return true;
    }
    return false;
}

Registro RegistroVazio(){
    Registro R;
    R.id = -1;
    R.name = "-";
    R.team = "-";
    R.games = "-";
    R.year = -1;
    R.season = "-";

    return R;
}

int BinarySearch(Registro* R, int left, int right, int procurado){
    if(left>right){
        return -1;
    }
    int mid = left+((right-left)/2);

    if(R[mid].id==procurado){
        return mid;
    }

    if(R[mid].id>procurado){
        return BinarySearch(R, left, mid-1, procurado);
    }else{
        return BinarySearch(R, mid+1, right, procurado);
    }
}

Registro* EsvaziaVetor(){
    Registro* R = new Registro[NUM_MAX_REGISTROS];
    for(int i=0; i<NUM_MAX_REGISTROS; i++){
        R[i] = RegistroVazio();
    }
    return R;
}

Registro* insereOrdenadoNoVetor(Registro* R, Registro novo, int qtdRegistrosNoNode){
    int i = qtdRegistrosNoNode-1; //ultima posicao ocupada
    while (i >= 0 && R[i].id > novo.id) {
        R[i + 1] = R[i];
        i--;
    }

    R[i + 1] = novo;

    return R;
}

Registro* reorganizaVetorNaRemocao(Registro* R, int posicaoRemovida){
    for(int i=posicaoRemovida; i<NUM_MAX_REGISTROS-1; i++){
        R[i]=R[i+1];
    }
    R[NUM_MAX_REGISTROS-1]=RegistroVazio();
    return R;
}

string gerarNomeArquivoNode(int n){
    return "arquivoBIN_Node_"+to_string(n);
}



class SequenceSet{
    private:
    //header
    int numSequences;
    Node* inicio;
    Node* ultimo;
    int numProximoNodeCriado;

    public:
    SequenceSet(){
        numSequences=0;
        inicio = nullptr;
        ultimo = nullptr;
        numProximoNodeCriado=0;
    };

   ~SequenceSet() {
    Node* atual = inicio;
    while (atual != nullptr) {
        Node* prox = atual->proximo;

        if (remove(atual->filePath.c_str()) == 0) {
            cout << "Arquivo " << atual->filePath << " deletado com sucesso"<<endl;
        } else {
            cerr << "Erro ao deletar o arquivo " << atual->filePath << endl;
        }

        delete atual;
        atual = prox;
    }
    inicio = nullptr;
    ultimo = nullptr;
}


    void insereOrdenado(Registro R){};//implementar
    bool removeRegistro(int IdRemovido){return true;};//implementar
    Registro buscarRegistro(int IdBuscado){
        Node* atual = inicio;

        while (atual != nullptr) {
            if (atual->proximo == nullptr || IdBuscado < atual->menorIdDoProximoNode) {
                Registro* Registros = importarBIN(atual->filePath);
                int posicao = BinarySearch(Registros, 0, atual->qtdRegistros - 1, IdBuscado);

                if (posicao != -1) {
                    cout << "Registro encontrado no arquivo: " << atual->filePath << endl;
                    cout << "Posição do registro no vetor: " << posicao << endl;
                    Registro R = Registros[posicao];
                    delete [] Registros;
                    return R;
                }

                delete [] Registros;
                return RegistroVazio();
            }
            atual = atual->proximo;
        }
        return RegistroVazio();
    };
};

void importarCSV (string nomeArquivo, SequenceSet S){
    ifstream arquivo(nomeArquivo);
    
    if(arquivo){
        string linha;
        Registro R;
        string idAUX, yearAUX;

        while(getline(arquivo, linha)) {
			if (linha.empty()) {
				continue;
			}

            stringstream StrStream(linha);
			getline(StrStream,idAUX,',');
			getline(StrStream,R.name,',');
			getline(StrStream,R.team,',');
			getline(StrStream,R.games,',');
			getline(StrStream,yearAUX, ',');
            getline(StrStream,R.season, ',');

            R.id=stoi(idAUX);
            R.year=stoi(yearAUX);

            S.insereOrdenado(R);
        }
        cout<<"Arquivo "<< nomeArquivo <<" lido com sucesso!! "<<endl;
		arquivo.close();
    }else{
        cout<<"Arquivo "<<nomeArquivo<<" nao pode ser aberto "<<endl;
    }
}

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


int main(){
    int opcao, idAux;
    string fileName;
    SequenceSet SqcSet;
    Registro RegAux;

    do{
		telaOpcoes();
		cin>>opcao;
        switch (opcao){
            case 1:
                cout<<"Digite o nome do arquivo que sera lido: ";
				cin>>fileName;
                importarCSV(fileName, SqcSet);
            break;

            case 2:
                cout<<"Digite o id do registro que sera adicionado: ";
                cin>>RegAux.id;
                cout<<endl<<"Digite o nome do registro que sera adicionado: ";
                cin>>RegAux.name;
                cout<<endl<<"Digite o time do registro que sera adicionado: ";
                cin>>RegAux.team;
                cout<<endl<<"Digite os jogos do registro que sera adicionado: ";
                cin>>RegAux.games;
                cout<<endl<<"Digite o ano do registro que sera adicionado: ";
                cin>>RegAux.year;
                cout<<endl<<"Digite a estacao do registro que sera adicionado: ";
                cin>>RegAux.season;
                
                SqcSet.insereOrdenado(RegAux);
                cout<<endl<<"Registro adicionado com sucesso! ";
            break;

            case 3:
               cout<<"Digite o id do registro a ser buscado: ";
                cin>>idAux;
                RegAux=SqcSet.buscarRegistro(idAux);
                if(verificaSeEhRegistroVazio(RegAux)){
                    cout<<endl<<"Registro buscado nao existe!!"<<endl;
                }else{
                    printRegistro(RegAux);
                }
            break;

            case 4:
                cout<<"Digite o id do registro a ser removido: ";
                cin>>idAux;
                if(SqcSet.removeRegistro(idAux)){
                    cout<<endl<<"Registro removido com sucesso!!"<<endl;
                }else{
                    cout<<endl<<"Registro buscado nao existe!!"<<endl;
                }
            break;

            default:
                cout<<"OPCAO INVALIDA!";
        }
        cout<<"\nTecle ENTER para continuar...";
		cin.ignore().get();
    }while(opcao!=9);
    
    return 0;
}
