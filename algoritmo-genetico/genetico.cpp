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

/* Retorna o fitness do individuo para o problema SEND+MORE=MONEY
// 			Formato do gene
//	indice|0|1|2|3|4|5|6|7|8|9|
//	letra |S|E|N|D|M|O|R|Y|-|-|
int fitness(ind_t i) {
	int send  = (1000*i.gene[0]) + (100*i.gene[1]) + (10*i.gene[2]) + i.gene[3];
	int more  = (1000*i.gene[4]) + (100*i.gene[5]) + (10*i.gene[6]) + i.gene[1];
	int money = (10000*i.gene[4]) + (1000*i.gene[5]) + (100*i.gene[2]) +
                    (10*i.gene[1]) + i.gene[7];
	return 1000000 - abs(money - (send + more));
}
//*/

/* Retorna o fitness do individuo para o problema EAT+THAT=APPLE
//			Formato do gene
//	indice|0|1|2|3|4|5|6|7|8|9|
//  letra |E|A|T|H|P|L|-|-|-|-|
int fitness(ind_t i) {
	int eat   = (100*i.gene[0]) + (10*i.gene[1]) + i.gene[2];
	int that  = (1000*i.gene[2]) + (100*i.gene[3]) + (10*i.gene[1]) + i.gene[2];
	int apple = (10000*i.gene[1]) + (1000*i.gene[4]) + (100*i.gene[4]) +
                    (10*i.gene[5]) + i.gene[0];
	return 10000000 - abs(apple - (eat + that));
}
//*/

/* Retorna o fitness do individuo para o problema CROSS+ROADS=DANGER
//			Formato do gene
//	indice|0|1|2|3|4|5|6|7|8|9|
//	letra |C|R|O|S|A|D|N|G|E|-|
int fitness(ind_t i) {
	int cross  = (10000*i.gene[0]) + (1000*i.gene[1]) + (100*i.gene[2]) +
		(10*i.gene[3]) + i.gene[3];
	int roads  = (10000*i.gene[1]) + (1000*i.gene[2]) + (100*i.gene[4]) +
		(10*i.gene[5]) + i.gene[3];
	int danger = (100000*i.gene[5]) + (10000*i.gene[4]) + (1000*i.gene[6]) +
		(100*i.gene[7]) + (10*i.gene[8]) + i.gene[1];
	return 10000000 - abs(danger - (cross + roads));
}
//*/

/* Retorna o fitness do individuo para o problema COCA+COLA=OASIS
//			Formato do gene
//	indice|0|1|2|3|4|5|6|7|8|9|
//	letra |C|O|A|L|S|I|-|-|-|-|
int fitness(ind_t i) {
	int coca  = (1000*i.gene[0]) + (100*i.gene[1]) + (10*i.gene[0]) + i.gene[2];
	int cola  = (1000*i.gene[0]) + (100*i.gene[1]) + (10*i.gene[3]) + i.gene[2];
	int oasis = (10000*i.gene[1]) + (1000*i.gene[2]) + (100*i.gene[4]) +
                    (10*i.gene[5]) + i.gene[4];
	return 10000000 - abs(oasis - (coca + cola));
}
//*/

//* Retorna o fitness do individuo para o problema DONALD+GERALD=ROBERT
//			Formato do gene
//	indice|0|1|2|3|4|5|6|7|8|9|
//	letra |D|O|N|A|L|G|E|R|B|T|
int fitness(ind_t i) {
	int donald = (100000*i.gene[0]) + (10000*i.gene[1]) + (1000*i.gene[2]) +
		(100*i.gene[3]) + (10*i.gene[4]) + i.gene[0];
	int gerald = (100000*i.gene[5]) + (10000*i.gene[6]) + (1000*i.gene[7]) +
		(100*i.gene[3]) + (10*i.gene[4]) + i.gene[0];
	int robert = (100000*i.gene[7]) + (10000*i.gene[1]) + (1000*i.gene[8]) +
		(100*i.gene[6]) + (10*i.gene[7]) + i.gene[9];
	return 10000000 - abs(robert - (donald + gerald));
}
//*/

/* Verifica se uma dada populacao convergiu */
bool convergiu(ind_t pop[]) {
	return pop[0].fit == 10000000;
}

/* Verdade se o individuo 'a' for mais apto que 'b', falso caso contrario */
bool mais_apto(ind_t a, ind_t b) {
	return a.fit > b.fit;
}

/* Gera um individuo aleatorio */
ind_t gera_individuo(void) {
	int val, i, j;
	bool found;
	ind_t individuo;

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
ind_t torneio(ind_t pop[]) {
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
void monta_roleta(ind_t pop[]) {
	int acc = 0;

	for (int i = 0; i < PMAX; i++) {
		acc += pop[i].fit;
		prob[i] = acc;
	}
}

/* Faz o metodo da roleta para selecionar o individuo aleatorio mais apto */
ind_t roleta(ind_t pop[]) {
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
void crossover_ciclico(ind_t i1, ind_t i2, ind_t filhos[]) {
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

/* Realiza o crossover PMX entre i1 e i2 e retorna dois novos individuos */
void crossover_pmx(ind_t i1, ind_t i2, ind_t filhos[]) {
	int troca[NGEN], pt_cross1, pt_cross2, i, j, aux;
	// Gera dois pontos de crossover aleatorios
	do {
		pt_cross1 = randint(NGEN);
		do { pt_cross2 = randint(NGEN); } while (pt_cross1 == pt_cross2);
	} while (pt_cross1 == 0 && pt_cross2 == 9);
	if (pt_cross1 > pt_cross2) std::swap(pt_cross1, pt_cross2);
	// Processa as trocas que deverao ser feitas fora do intervalo
	for (i = 0; i < NGEN; i++)
		troca[i] = -1;
	for (i = pt_cross1; i <= pt_cross2; i++) {
		if (i1.gene[i] != i2.gene[i]) {
			troca[i1.gene[i]] = i2.gene[i];
			// Troca os valores dentro do intervalo de crossover
			std::swap(i1.gene[i], i2.gene[i]);
		}
	}
	// Caso o ciclo seja o gene inteiro nao eh necessario ajustar
	if (pt_cross1 != 0 || pt_cross2 != 9) {
		// Corrige os ciclos
		for (i = 0; i < NGEN; i++) {
			if (troca[i] != -1 && troca[troca[i]] != -1) {
				j = i;
				while (troca[troca[j]] != -1) {
					aux = troca[j];
					troca[j] = -1;
					j = aux;
				}
				troca[i] = troca[j];
				troca[j] = -1;
				//troca[troca[j]] = i;
			}
		}
		for (i = 0; i < NGEN; i++) {
			if (troca[i] != -1 && troca[troca[i]] == -1) {
				troca[troca[i]] = i;
			}
		}
	}
	// Corrige os genes fora do intervalo com base no vetor de troca
	for (i = 0; i < NGEN; i++) {
		if (i < pt_cross1 || i > pt_cross2) {
			if (troca[i1.gene[i]] != -1)
				i1.gene[i] = troca[i1.gene[i]];
			if (troca[i2.gene[i]] != -1)
				i2.gene[i] = troca[i2.gene[i]];
		}
	}
	// Calcula o fitness dos individuos resultantes
	i1.fit = fitness(i1);
	i2.fit = fitness(i2);
	// Salva os individuos resultantes
	filhos[0] = i1;
	filhos[1] = i2;
}

//* Recebe um individuo i e retorna o individuo mutacionado
void mutaciona(ind_t* i) {
	int pt_mut1, pt_mut2;

	// Gera dois pontos diferentes de mutacao aleatorios
	pt_mut1 = randint(NGEN);
	do { pt_mut2 = randint(NGEN); } while (pt_mut1 == pt_mut2);
	// Troca os valores dos genes do individuo nos pts sorteados
	std::swap(i->gene[pt_mut1], i->gene[pt_mut2]);
	// Recalcula o fitness do individuo
	i->fit = fitness(*i);
}
//*/
