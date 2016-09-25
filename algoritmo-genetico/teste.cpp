#include "genetico.h"

/* Mostra na tela o individuo */
void print(ind_t i) {
	printf("Gene: |");
	for (int j = 0; j < NGEN; j++) {
		printf(" %d |", i.gene[j]);
	}
	printf("\nFitness: %d\n", i.fit);
}

/* Verifica se o individuo eh valido */
bool valido(ind_t i) {
	for (int j = 0; j < NGEN-1; j++) {
		for (int k = j+1; k < NGEN; k++) {
			if (i.gene[j] == i.gene[k]) {
				return false;
			}
		}
	}
	return true;
}

/* Analisa e mostra na tela as estatisticas da populacao */
void analisa_populacao(ind_t pop[]) {
    int fit_pop, n_0, n_1, n_100, fit_100, melhor_ind;

	fit_pop = n_0 = n_1 = n_100 = fit_100 = melhor_ind = 0;
	for (int i = 0; i < PMAX; i++) {
		// Pega o melhor individuo
		if (mais_apto(pop[i], pop[melhor_ind]))
			melhor_ind = i;
		// Conta quantos individuos possuem valor 0 ou 1 na letra M
		if      (pop[i].gene[4] == 0) n_0++;
		else if (pop[i].gene[4] == 1) n_1++;
		// Verifica quantos individuos possuem fitness abaixo de 100
		if (pop[i].fit <= 100) {
			fit_100 += pop[i].fit;
			n_100++;
		}
		// Pega a media dos fitness da populacao
		fit_pop += pop[i].fit;
	}

    // Mostra os resultados
    printf("Media fitness: \t\t%.2f\n", fit_pop / (PMAX * 1.0));
    printf("Melhor fitness: \t%d\n", pop[melhor_ind].fit);
    printf("Nro de ind < 100: \t%d\n", n_100);
    printf("Media ind < 100: \t%.2f\n", (n_100 != 0) ? (fit_100 / (n_100 * 1.0)) : 0);
    printf("Nro de ind com M = 0: \t%d\n", n_0);
    printf("Nro de ind com M = 1: \t%d\n", n_1);
}

/* Analisa e salva as estatisticas da populacao em result */
void analisa_populacao(ind_t pop[], double result[]) {
	int fit_pop, n_0, n_1, n_100, fit_100, melhor_ind;

	fit_pop = n_0 = n_1 = n_100 = fit_100 = melhor_ind = 0;
	for (int i = 0; i < PMAX; i++) {
		// Pega o melhor individuo
		if (mais_apto(pop[i], pop[melhor_ind]))
			melhor_ind = i;
		// Conta quantos individuos possuem valor 0 ou 1 na letra M
		if      (pop[i].gene[4] == 0) n_0++;
		else if (pop[i].gene[4] == 1) n_1++;
		// Verifica quantos individuos possuem fitness abaixo de 100
		if (pop[i].fit <= 100) {
			fit_100 += pop[i].fit;
			n_100++;
		}
		// Pega a media dos fitness da populacao
		fit_pop += pop[i].fit;
	}
	// Salva os resultados
	result[0] = (fit_pop / (PMAX * 1.0));						// Media fitness
	result[1] = pop[melhor_ind].fit * 1.0;						// Melhor fitness
	result[2] = n_100 * 1.0;									// Nro de ind < 100
	result[3] = ((n_100 != 0) ? (fit_100 / (n_100 * 1.0)) : 0); // Media ind < 100
	result[4] = n_0 * 1.0;										// Nro de ind M = 0
	result[5] = n_1 * 1.0;										// Nro de ind M = 1
}
