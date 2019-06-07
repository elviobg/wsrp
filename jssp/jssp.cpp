#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1048576
#define WIDTH 7
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

// https://google.github.io/styleguide/cppguide.html

#define INFINITO 9999999;
using namespace std;

typedef vector<vector<int>> Matriz;

class Programacao {

public:
	Matriz inicio;
	Matriz termino;
	Matriz tarefa;
	void getProgramacao(Matriz op_maquina, Matriz op_tempo, int qtd_maquinas, int qtd_tarefas);

};
void imprimirInstancia(Matriz& op_maquina, Matriz op_tempo) {
	int op = 1;
	for (int i = 0; i < op_tempo.size(); i++) {
		for (int j = 0; j < op_tempo[0].size(); j++) {
			cout << "operacao: " << op << " maquina: " << op_maquina[i][j] << " tempo de processamento: " << op_tempo[i][j] << " tarefa: " << i + 1 << '\n';
			op++;
		}
	}
}
void imprimirProgramacao(Matriz programacao, int tipo) {
	int qtd_maquinas = programacao.size();
	int qtd_tarefas = programacao[0].size();
	if (tipo == 1) {
		cout << "***********Instante de Inicio " << '\n';
	}if (tipo == 2) {
		cout << "***********Instante de Termino " << '\n';
	}


	int makespan = 0;
	for (int i = 0; i < qtd_maquinas; i++) {
		cout << "Maquina " << i + 1 << ": ";
		for (int j = 0; j < qtd_tarefas; j++) {
			cout << programacao[i][j] << ' ';
		}
		if (programacao[i][qtd_tarefas - 1] > makespan) {
			makespan = programacao[i][qtd_tarefas - 1];
		}
		cout << '\n';
	}
	if (tipo == 2) {
		cout << "\nMakespan: " << makespan << "\n";
	}

}
void imprimirDiagrama(Matriz programacaoInstanteInicio, Matriz programacaoInstanteTermino, Matriz tarefa) {

	int comprimento = 0;
	int k;

#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO Info;
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &Info);
	WORD atributos = Info.wAttributes;
#endif

	for (int i = 0; i < programacaoInstanteInicio.size(); i++) {

		comprimento = 0;
		for (int j = 0; j < programacaoInstanteTermino[0].size(); j++) {

			while (comprimento < programacaoInstanteInicio[i][j]){
				cout << " ";
				comprimento++;

			}while(comprimento < programacaoInstanteTermino[i][j]) {

				for (k = 0; k <= tarefa.size(); k++) {

					if (k == tarefa[i][j]) {
						#ifdef _WIN32
						SetConsoleTextAttribute(hConsole, k + 1);
						#endif
						cout << k+1;

					}
				}
				comprimento++;


			}
		}
		#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, atributos);
		#endif
		cout << " " << comprimento << "\n";

	}
	#ifdef _WIN32
	SetConsoleTextAttribute(hConsole, atributos);
	#endif
}

void Programacao::getProgramacao(Matriz op_maquina, Matriz op_tempo, int qtd_maquinas, int qtd_tarefas) {//1 = jato, 2=Monomotor, 3=planador
vector<int> tempo_tarefa(qtd_tarefas, 0);
vector<int> tempo_maquina(qtd_maquinas, 0);
Matriz programacao_termino(qtd_maquinas, vector<int>(qtd_tarefas, 0));
Matriz programacao_inicio(qtd_maquinas, vector<int>(qtd_tarefas, 0));
Matriz programacao_tarefa(qtd_maquinas, vector<int>(qtd_tarefas, 0));
int operacao;
int mx = 0, my = 0;//variáveis para guardar a posicao do operacao valor
int valorM; //variável para guardar o tempo da maquina
int valorT; //variável para guardar o tempo da tarefa
int valorI = INFINITO; //variável para guardar o tempo atual (máquina ou de tarefa)

for (int i = 0; i < qtd_tarefas; i++) {//percorre a matriz resultante

	for (int j = 0; j < qtd_maquinas; j++) {
		for (int x = 0; x < qtd_tarefas; x++) { //percorre as matrizes de entrada (maquina e tempo de processamento)

			for (int y = 0; y < qtd_maquinas; y++) {

				if (op_maquina[x][y] == j + 1) {//condicao para pegar a op de uma respectiva maquina j+1

					valorM = tempo_maquina[j] + op_tempo[x][y];//tempo de maquina resultante para operacao xy
					valorT = tempo_tarefa[x] + op_tempo[x][y];//tempo de tarefa resultante para operacao xy

					if(valorT <= valorI){//condicao para pegar a operacao que vai resultar em um menor tempo de tarefa
						if (valorM > valorT) {
							valorI = valorM;
							operacao = op_tempo[x][y];  //guarda o tempo
							mx = x;//guarda a posicao
							my = y;//guarda a posicao
						}
						else {

							valorI = valorT;
							operacao = op_tempo[x][y]; //guarda o tempo
							mx = x;//guarda a posicao
							my = y;//guarda a posicao
						}
					}

				}

				if (x == qtd_tarefas - 1 && y == qtd_maquinas - 1) {// condicao para permitir que todas posicoes sejam verificadas
					//as condições a seguir verificam os tempos atuais de maquinas e tarefas da qual a operacao pertence
					//e posiciona a operação no instante de tempo adequado
					if (tempo_maquina[j] > tempo_tarefa[mx]) {
						programacao_inicio[j][i] = tempo_maquina[j];
						programacao_termino[j][i] = tempo_maquina[j] + operacao;
						programacao_tarefa[j][i] = mx;
					}
					else {
						programacao_inicio[j][i] = tempo_tarefa[mx];
						programacao_termino[j][i] = tempo_tarefa[mx] + operacao;
						programacao_tarefa[j][i] = mx;
					}
					tempo_maquina[j] = programacao_termino[j][i];//atualiza o tempo de maquina
					tempo_tarefa[mx] = programacao_termino[j][i];//atualiza o tempo de tarefa
					op_tempo[mx][my] = INFINITO ;// atribui um valor "infinito" para que a operacao não se repita
					valorI = INFINITO;// atribui um valor "infinito" para testar operarações na prox maquina
				}

			}
		}
	}
}
this->inicio = programacao_inicio;
this->termino = programacao_termino;
this->tarefa = programacao_tarefa;

}
int main()
{
	Matriz instanteInicio;
	Matriz instanteTermino;
	Matriz tarefas;
	int opcao;
	std::ifstream file("tailard/matriz08x07.txt");
	if (!file)
	{
		std::cout << "Erro no arquivo!" << std::endl;
	}

	size_t qtd_tarefas, qtd_maquinas;
	file >> qtd_tarefas; //pega a qtd de tarefas
	file >> qtd_maquinas; //pega a qtd de maquinas

	std::string trashLine;
	getline(file, trashLine); //pula uma linha
	getline(file, trashLine); //pula uma linha

	Matriz op_tempo(qtd_tarefas, vector<int>(qtd_maquinas, 0));
	Matriz op_maquina(qtd_tarefas, vector<int>(qtd_maquinas, 0));

	for (size_t i = 0; i < qtd_tarefas; ++i){
		for (size_t j = 0; j < qtd_maquinas; ++j){
			int valor;
			file >> valor;
			op_tempo[i][j] = valor;
		}
	}

	getline(file, trashLine); //pular linha
	getline(file, trashLine); //pular linha

	for (size_t i = 0; i < qtd_tarefas; ++i){
		for (size_t j = 0; j < qtd_maquinas; ++j){
			int valor;
			file >> valor;
			op_maquina[i][j] = valor;
		}
	}

	file.close();

	Programacao *p1 = new Programacao();
	p1->getProgramacao(op_maquina, op_tempo, qtd_maquinas, qtd_tarefas);

	cout << "\nMENU PARA FINS DIDATICOS:  " << "\n" << "1: IMPRIMIR INSTANCIA\n" << "2: IMPRIMIR SOLUCAO (INSTANTE DE INICIO)\n"
		<< "3: MAKESPAN (INSTANTE DE TERMINO)\n" << "4: IMPRIMIR DIAGRAMA\n" << "5: TODAS OPCOES" << "\n" ;
	cin >> opcao;


	switch (opcao)
	{

	case 1:
		imprimirInstancia(op_maquina, op_tempo);
		main();
		break;
	case 2:
		imprimirProgramacao(p1->inicio, 1);
		main();
		break;
	case 3:
		imprimirProgramacao(p1->termino, 2);
		main();
		break;
	case 4:
		imprimirDiagrama(p1->inicio, p1->termino, p1->tarefa);
		main();
		break;
	default:
	  imprimirInstancia(op_maquina, op_tempo);
		imprimirProgramacao(p1->inicio, 1);
		imprimirProgramacao(p1->termino, 2);
		imprimirDiagrama(p1->inicio, p1->termino, p1->tarefa);
		main();
		break;
	}

	cin.get(); // wait
	return 0;
}
