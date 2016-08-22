/*      Algoritmo Genetico: Criptoaritmetica

    S E N D
    M O R E +
  ---------
  M O N E Y     */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define PMAX	100 // Nro maximo de individuos da populacao
#define NGER	50  // Nro de geracoes
#define PCROSS	60  // Qtde de filhos que serao gerados
#define PMUT	1   // Prob de mutacao
#define NGEN 	10	// Nro de genes no individuo

/*			Formato do gene
	indice|0|1|2|3|4|5|6|7|8|9|
	letra |S|E|N|D|M|O|R|Y|-|-|     */
struct ind {
	int gene[NGEN];
	int fit;
};

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
			val = rand() % NGEN;
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
	int i1 = rand() % PMAX;
	int i2 = rand() % PMAX;
	int i3 = rand() % PMAX;

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

/* Reliza o crossover ciclico entre i1 e i2 e retorna dois novos individuos */
void crossover(ind i1, ind i2, ind filhos[]) {
	int i, pt_cross;
	bool flag = true;

	// Inicia em um ponto de crossover aleatorio
	pt_cross = rand() % NGEN;
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
	// Gera dois pontos diferentes de mutacao aleatorios
	int pt_mut1 = rand() % NGEN;
	int pt_mut2 = rand() % NGEN;
	while (pt_mut1 == pt_mut2)
		pt_mut2 = rand() % NGEN;
	// Troca os valores dos genes do individuo nos pts sorteados
	std::swap(i->gene[pt_mut1], i->gene[pt_mut2]);
	// Recalcula o fitness do individuo
	i->fit = fitness(*i);
}

/* Analisa e tira estatisticas da populacao */
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
	/* Mostra os resultados
	printf("Media fitness: \t\t%.2f\n", fit_pop / (PMAX * 1.0));
	printf("Melhor fitness: \t%d\n", pop[melhor_ind].fit);
	printf("Nro de ind < 100: \t%d\n", n_100);
	printf("Media ind < 100: \t%.2f\n", (n_100 != 0) ? (fit_100 / (n_100 * 1.0)) : 0);
	printf("Nro de ind com M = 0: \t%d\n", n_0);
	printf("Nro de ind com M = 1: \t%d\n", n_1);
	//*/
}

int main(int argc, char *argv[]) {
	ind pop[PMAX], filhos[PCROSS], ger[PMAX+PCROSS], ind1, ind2, result[2];
	int i;
	double medias_inicial[50][6], medias_final[50][6];

	srand(time(NULL));
	for (int c = 0; c < 50; c++) {
		// Gera 100 individuos aleatorios para a populacao inicial
		for (i = 0; i < PMAX; i++) {
			pop[i] = gera_individuo();
		}
		//printf("\tPopulacao inicial\n\n");
		analisa_populacao(pop, medias_inicial[c]);

		// Seleciona PCROSS individuos aleatorios para o crossover
		for (i = 0; i < PCROSS; i += 2) {
			ind1        = torneio(pop);
			ind2        = torneio(pop);
			crossover(ind1, ind2, result);
			filhos[i]   = result[0];
			filhos[i+1] = result[1];
		}

		// Seleciona um filho aleatorio e o mutaciona
		i = rand() % PCROSS;
		mutaciona(&filhos[i]);

		// Insere os filhos na populacao
		for (i = 0; i < PMAX; i++)
			ger[i] = pop[i];
		for (i = PMAX; i < PMAX+PCROSS; i++)
			ger[i] = filhos[i-PMAX];

		// Ordena os individuos e pega os PMAX melhores
		std::sort(ger, ger+PMAX+PCROSS, mais_apto);
		for (i = 0; i < PMAX; i++) {
			pop[i] = ger[i];
		}
		//printf("\n\tPopulacao gerada\n\n");
		analisa_populacao(pop, medias_final[c]);
	}

	double fit_pop_in, n_0_in, n_1_in, n_100_in, fit_100_in, melhor_ind_in;
	double fit_pop_fin, n_0_fin, n_1_fin, n_100_fin, fit_100_fin, melhor_ind_fin;

	fit_pop_in = n_0_in = n_1_in = n_100_in = fit_100_in = melhor_ind_in = 0;
	fit_pop_fin = n_0_fin = n_1_fin = n_100_fin = fit_100_fin = melhor_ind_fin = 0;
	for (int c = 0; c < 50; c++) {
		// Medias populacao inicial
		fit_pop_in    += medias_inicial[c][0];
		melhor_ind_in += medias_inicial[c][1];
		n_100_in 	  += medias_inicial[c][2];
		fit_100_in    += medias_inicial[c][3];
		n_0_in 		  += medias_inicial[c][4];
		n_1_in 		  += medias_inicial[c][5];
		// Medias populacao final
		fit_pop_fin    += medias_final[c][0];
		melhor_ind_fin += medias_final[c][1];
		n_100_fin      += medias_final[c][2];
		fit_100_fin    += medias_final[c][3];
		n_0_fin        += medias_final[c][4];
		n_1_fin        += medias_final[c][5];
	}
	printf("\tMedias populacao inicial\n\n");
	printf("Media fitness: \t\t%.2lf\n",   fit_pop_in / 50.0);
	printf("Melhor fitness: \t%.2lf\n", melhor_ind_in / 50.0);
	printf("Nro de ind < 100: \t%.2lf\n", 	 n_100_in / 50.0);
	printf("Media ind < 100: \t%.2lf\n", 	   n_0_in / 50.0);
	printf("Nro de ind com M = 0: \t%.2lf\n",  n_0_in / 50.0);
	printf("Nro de ind com M = 1: \t%.2lf\n",  n_1_in / 50.0);

	printf("\n\tMedias populacao gerada\n\n");
	printf("Media fitness: \t\t%.2lf\n",   fit_pop_fin / 50.0);
	printf("Melhor fitness: \t%.2lf\n", melhor_ind_fin / 50.0);
	printf("Nro de ind < 100: \t%.2lf\n",    n_100_fin / 50.0);
	printf("Media ind < 100: \t%.2lf\n", 	   n_0_fin / 50.0);
	printf("Nro de ind com M = 0: \t%.2lf\n",  n_0_fin / 50.0);
	printf("Nro de ind com M = 1: \t%.2lf\n",  n_1_fin / 50.0);

	return 0;
}
