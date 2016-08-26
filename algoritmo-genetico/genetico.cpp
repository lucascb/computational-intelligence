#include "genetico.h"

// Vetor utilizado no metodo de selecao por roleta
int prob[PMAX];

/* Sorteia um numero aleatorio entre [0, n) sem modulo bias */
int randint(int n) {
	int x;
	do { x = rand(); } while (x >= RAND_MAX - (RAND_MAX % n));
	return x % n;
}

/* Sorteia um numero aleatorio entre [min, max) */
int randrange(int min, int max) {
	int x;
	do { x = rand(); } while (x >= RAND_MAX - (RAND_MAX % (max - min)));
	return (x % (max - min)) + min;
}

/* Retorna o fitness do individuo */
int fitness(ind i) {
	int send  = (1000*i.gene[0]) + (100*i.gene[1]) + (10*i.gene[2]) + i.gene[3];
	int more  = (1000*i.gene[4]) + (100*i.gene[5]) + (10*i.gene[6]) + i.gene[1];
	int money = (10000*i.gene[4]) + (1000*i.gene[5]) + (100*i.gene[2]) +
                    (10*i.gene[1]) + i.gene[7];
	return abs(money - (send + more));
}

/* Verdade se o individuo 'a' for mais apto que 'b', falso caso contrario */
bool mais_apto(ind a, ind b) {
	return a.fit < b.fit;
}

/* Gera um individuo aleatorio */
ind gera_individuo(void) {
	int val, i, j;
	bool found;
	ind individuo;

	// Gera valores distintos para cada uma das oito letras
	for (i = 0; i < NGEN; i++) {
		// Gera enquanto o valor ja existir em v
		found = true;
		while (found) {
			val = randint(NGEN);
			// Verifica se val ja existe em v[0..i-1]
			found = false;
			for (j = 0; j < i; j++) {
				if (individuo.gene[j] == val) {
					found = true;
					break;
				}
			}
		}
		individuo.gene[i] = val;
	}
	individuo.fit = fitness(individuo);

	return individuo;
}

/* Faz torneio de 3 e retorna o individuo mais apto da populacao */
ind torneio(ind pop[]) {
	int melhor_ind;
	// Seleciona 3 individuos aleatorios da populacao
	int i1 = randint(PMAX);
	int i2 = randint(PMAX);
	int i3 = randint(PMAX);
	// Verifica qual o mais apto
	if (mais_apto(pop[i1], pop[i2])) {
		if (mais_apto(pop[i1], pop[i3]))
			melhor_ind = i1;
		else
			melhor_ind = i3;
	}
	else {
		if (mais_apto(pop[i2], pop[i3]))
			melhor_ind = i2;
		else
			melhor_ind = i3;
	}

	return pop[melhor_ind];
}

/* Monta a probabilidade de cada individuo baseado em sua aptidao */
void monta_roleta(ind pop[]) {
	int acc = 0;

	for (int i = 0; i < PMAX; i++) {
		acc += pop[i].fit;
		prob[i] = acc;
	}
}

/* Faz o metodo da roleta para selecionar o individuo aleatorio mais apto */
ind roleta(ind pop[]) {
	// Sorteia um numero entre 1 e o maior id
	int id_sorteado = randint(prob[PMAX-1]);
	// Procura o individuo que possue o valor sorteado e o retorna
	int i = 0;
	while (prob[i] < id_sorteado) {
		i++;
	}
	return pop[i];
}

/* Reliza o crossover ciclico entre i1 e i2 e retorna dois novos individuos */
void crossover_ciclico(ind i1, ind i2, ind filhos[]) {
	int i, pt_cross;
	bool flag = true;

	// Inicia em um ponto de crossover aleatorio
	pt_cross = randint(NGEN);
	// Repete enquanto existir pts de crossover
	while (flag) {
		// Troca os valores dos genes no pt de crossover
		std::swap(i1.gene[pt_cross], i2.gene[pt_cross]);
		// Procura o proximo pt de crossover (onde ha repeticao do valor)
		flag = false;
		for (i = 0; i < NGEN; i++) {
			if (i != pt_cross && i1.gene[i] == i1.gene[pt_cross]) {
				pt_cross = i;
				flag = true;
				break;
			}
		}
	}
	// Calcula o fitness dos individuos resultantes
	i1.fit = fitness(i1);
	i2.fit = fitness(i2);
	// Salva os individuos resultantes
	filhos[0] = i1;
	filhos[1] = i2;
}

/* Recebe um individuo i e retorna o individuo mutacionado */
void mutaciona(ind* i) {
	int pt_mut1, pt_mut2;

	// Gera dois pontos diferentes de mutacao aleatorios
	pt_mut1 = randint(NGEN);
	do { pt_mut2 = randint(NGEN); } while (pt_mut1 == pt_mut2);
	// Troca os valores dos genes do individuo nos pts sorteados
	std::swap(i->gene[pt_mut1], i->gene[pt_mut2]);
	// Recalcula o fitness do individuo
	i->fit = fitness(*i);
}

/* Analisa e mostra na tela as estatisticas da populacao */
void analisa_populacao(ind pop[]) {
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
void analisa_populacao(ind pop[], double result[]) {
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
