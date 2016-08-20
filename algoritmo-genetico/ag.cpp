/*      Algoritmo Genetico: Criptoaritmetica

    S E N D
    M O R E +
  ---------
  M O N E Y     */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define PMAX    100 // Nro maximo de individuos da populacao
#define NGER    50  // Nro de geracoes
#define PCROSS  60  // Qtde de filhos que serao gerados
#define PMUT    1   // Prob de mutacao

/*          Formato do gene 
    indice|0|1|2|3|4|5|6|7|8|9|
    letra |S|E|N|D|M|O|R|Y|-|-|     */
struct ind { 
    int gene[10]; 
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
    for (i = 0; i < 10; i++) {
        // Gera enquanto o valor ja existir em v
        while (true) {
            val = rand() % 10;
            // Verifica se val ja existe em v[0..i-1]
            found = false;
            for (j = 0; j < i; j++) {
                if (individuo.gene[j] == val) {
                    found = true;
                    break;
                }
            }
            // Se nao existir sai do laco e atribui val a letra
            if (!found) break;
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

/* Reliza o crossover ciclico entre ind1 e ind2 e retorna dois novos individuos */
void crossover(ind i1, ind i2, ind filhos[]) {
    int i, pt_cross;
    bool flag = true;
    
    // Inicia em um ponto de crossover aleatorio
    pt_cross = rand() % 10;
    // Repete enquanto existir pts de crossover
    while (flag) {
        // Troca os valores dos genes no pt de crossover
        std::swap(i1.gene[pt_cross], i2.gene[pt_cross]);
        // Procura o proximo pt de crossover (onde ha repeticao do valor)
        flag = false;
        for (i = 0; i < 10; i++) {
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
    int pt_mut1 = rand() % 10;
    int pt_mut2 = rand() % 10;
    while (pt_mut1 == pt_mut2) 
        pt_mut2 = rand() % 10;
    // Troca os valores dos genes do individuo nos pts sorteados
    std::swap(i->gene[pt_mut1], i->gene[pt_mut2]);
    // Recalcula o fitness do individuo
    i->fit = fitness(*i);
}

int main(int argc, char *argv[]) {
    ind pop[PMAX], filhos[PCROSS], ger[PMAX+PCROSS], ind1, ind2, result[2];
    int i;
    //*
    int fit_pop = 0, n_0 = 0, n_1 = 0, n_100 = 0, fit_100 = 0, melhor; 
    //*/
    
    srand(time(NULL));
	// Gera 100 individuos aleatorios para a populacao inicial
    for (i = 0; i < PMAX; i++) {
    	pop[i] = gera_individuo();
       	//* 
        fit_pop += pop[i].fit;
        if (pop[i].gene[4] == 0)      n_0++;
        else if (pop[i].gene[4] == 1) n_1++;
        if (pop[i].fit <= 100) {  
            n_100++;
            fit_100 += pop[i].fit;
        }
        if (i == 0 || pop[i].fit < melhor) melhor = pop[i].fit;
        //*/
    }
        
    //* Testes
    printf("Populacao inicial\n");
    printf("Media: %.2f\n", fit_pop / (PMAX * 1.0));
	printf("Nro de ind < 100: %d\n", n_100);
    printf("Media dos ind < 100: %.2f\n", (n_100 == 0) ? 0 : (fit_100 / (n_100 * 1.0)));
    printf("Nro de ind com M = 0: %d\n", n_0);
    printf("Nro de ind com M = 1: %d\n", n_1);
    printf("Melhor individuo: %d\n", melhor);
    //*/
    //printf("%.2f %d %.2f %d %d %d ", fit_pop / (PMAX * 1.0), n_100, (n_100 == 0) ? 0 : (fit_100 / (n_100 * 1.0)), n_0, n_1, melhor);
        
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
    fit_pop = 0, n_0 = 0, n_1 = 0, n_100 = 0, fit_100 = 0; 
    for (i = 0; i < PMAX; i++) {
        pop[i] = ger[i];
        //printf("%d\n", pop[i].fit);
        //* 
        fit_pop += pop[i].fit;
        if (pop[i].gene[4] == 0)      n_0++;
        else if (pop[i].gene[4] == 1) n_1++;
        if (pop[i].fit <= 100) {  
            n_100++;
            fit_100 += pop[i].fit;
        }
        if (i == 0 || pop[i].fit < melhor) melhor = pop[i].fit;
        //*/
    }
        
    //* Testes
    printf("\nPopulacao gerada\n");
    printf("Media: %.2f\n", fit_pop / (PMAX * 1.0));
    printf("Nro de ind < 100: %d\n", n_100);
    printf("Media dos ind < 100: %.2f\n", (n_100 == 0) ? 0 : (fit_100 / (n_100 * 1.0)));
    printf("Nro de ind com M = 0: %d\n", n_0);
    printf("Nro de ind com M = 1: %d\n", n_1);
    printf("Melhor individuo: %d\n", melhor);
    //*/
    //printf("%.2f %d %.2f %d %d %d\n", fit_pop / (PMAX * 1.0), n_100, (n_100 == 0) ? 0 : (fit_100 / (n_100 * 1.0)), n_0, n_1, melhor);

    return 0;   
}
