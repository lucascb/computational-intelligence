/*      Algoritmo Genetico: Criptoaritmetica

    S E N D
    M O R E +
  ---------
  M O N E Y     */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Parametros do algoritmo
#define NGEN 	10  // Nro de genes no individuo
#define PMAX	100 // Nro maximo de individuos da populacao
#define NGER	50  // Nro de geracoes
#define PCROSS	80  // Qtde de filhos que serao gerados
#define PMUT	5   // Prob de mutacao
#define ELITE   20	// Porcentagem de elitismo

/*			Formato do gene
	indice|0|1|2|3|4|5|6|7|8|9|
	letra |S|E|N|D|M|O|R|Y|-|-|     */
struct ind {
	int gene[NGEN];
	int fit;
};

// Funcoes auxiliares
int randint(int n);
int randrange(int min, int max);

// Funcoes do algoritmo
int fitness(ind i);
bool convergiu(ind pop[]);
bool mais_apto(ind a, ind b);
ind gera_individuo(void);

ind torneio(ind pop[]);
void monta_roleta(ind pop[]);
ind roleta(ind pop[]);

void crossover_ciclico(ind i1, ind i2, ind filhos[]);
void crossover_pmx(ind i1, ind i2, ind filhos[]);
void mutaciona(ind* i);

// Funcoes para teste
void analisa_populacao(ind pop[]);
void analisa_populacao(ind pop[], double result[]);
