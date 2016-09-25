/*      Algoritmo Genetico: Criptoaritmetica
 *
 *    S E N D
 *    M O R E +
 *  ---------
 *  M O N E Y
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Parametros do algoritmo
#define NGEN 	10  // Nro de genes no individuo
#define PMAX	100 // Nro maximo de individuos da populacao
#define NGER	50  // Nro de geracoes
#define PCROSS	80  // Qtde de filhos que serao gerados
#define PMUT	10   // Prob de mutacao
#define ELITE   20	// Porcentagem de elitismo

/*			Formato do gene
 *	indice|0|1|2|3|4|5|6|7|8|9|
 *	letra |S|E|N|D|M|O|R|Y|-|-|
 */
struct ind_t {
	int gene[NGEN];
	int fit;
};

/* 						genetico.cpp					*/
// Funcoes auxiliares
int randint(int n);
int randrange(int min, int max);

// Funcoes do algoritmo
int fitness(ind_t i);
bool convergiu(ind_t pop[]);
bool mais_apto(ind_t a, ind_t b);
ind_t gera_individuo(void);

ind_t torneio(ind_t pop[]);
void monta_roleta(ind_t pop[]);
ind_t roleta(ind_t pop[]);

void crossover_ciclico(ind_t i1, ind_t i2, ind_t filhos[]);
void crossover_pmx(ind_t i1, ind_t i2, ind_t filhos[]);
void mutaciona(ind_t* i);

/*						teste.cpp					 */
void print(ind_t i);
bool valido(ind_t i);
void analisa_populacao(ind_t pop[]);
void analisa_populacao(ind_t pop[], double result[]);
