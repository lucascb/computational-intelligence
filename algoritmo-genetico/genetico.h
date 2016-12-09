/*      Algoritmo Genetico: Criptoaritmetica
 *
 *    S E N D       E A T     C R O S S     C O C A     D O N A L D
 *    M O R E +   T H A T +   R O A D S +   C O L A +   G E R A L D +
 *  ---------    --------    ----------    --------    ------------
 *  M O N E Y   A P P L E   D A N G E R   O A S I S     R O B E R T
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Parametros do algoritmo
#define NGEN 	10  // Nro de genes no individuo
#define PMAX	200 // Nro maximo de individuos da populacao
#define NGER	100 // Nro de geracoes
#define PCROSS	80  // Porcentagem de filhos que serao gerados
#define PMUT	40  // Prob de mutacao
#define ELITE   20	// Porcentagem de elitismo

// Individuo
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

bool igual(ind_t a, ind_t b);
bool existe(ind_t i, ind_t pop[]);
void povoar(ind_t pop[]);
