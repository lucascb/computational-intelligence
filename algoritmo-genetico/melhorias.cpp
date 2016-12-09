#include "genetico.h"

/* Realiza a soma digito a digito para o problema CROSS+ROADS=DANGER
int fitness(ind_t i) {
	int x[6], carry, error;

	x[5] = i.gene[3] + i.gene[3]; 			// R = S + S
	carry = 0;
	if (x[5] > 9) {
		x[5] %= 10;
		carry = 1;
	}
	x[4] = i.gene[3] + i.gene[5] + carry; 	// E = S + D
	carry = 0;
	if (x[4] > 9) {
		x[4] %= 10;
		carry = 1;
	}
	x[3] = i.gene[2] + i.gene[4] + carry;	// G = O + A
	carry = 0;
	if (x[3] > 9) {
		x[3] %= 10;
		carry = 1;
	}
	x[2] = i.gene[1] + i.gene[2] + carry;	// N = R + O
	carry = 0;
	if (x[2] > 9) {
		x[2] %= 10;
		carry = 1;
	}
	x[1] = i.gene[0] + i.gene[1] + carry;	// A = C + R
	carry = 0;
	if (x[1] > 9) {
		x[1] %= 10;
		carry = 1;
	}
    x[0] = carry;

    error = 0;
    error += abs(x[5] - i.gene[1]);
    error += abs(x[4] - i.gene[8]);
    error += abs(x[3] - i.gene[7]);
    error += abs(x[2] - i.gene[6]);
    error += abs(x[1] - i.gene[4]);
    error += abs(x[0] - i.gene[5]);

	return 1000000 - error;
}
//*/

// Verdade se o individuo a for igual ao b, falso caso contrario
bool igual(ind_t a, ind_t b) {
    if (a.fit != b.fit) {
        return false;
    }
    for (int i = 0; i < NGEN; i++) {
        if (a.gene[i] != b.gene[i]) {
            return false;
        }
    }
    return true;
}

// Verdade se o individuo i existe na populacao, ou falso caso contrario
bool existe(ind_t i, ind_t pop[]) {
    for (int k = 0; k < PMAX; k++) {
        if (igual(i, pop[k])) {
            return true;
        }
    }
    return false;
}

void povoar(ind_t pop[]) {
    bool flag;

    for (int i = 0; i < PMAX; i++) {
        flag = true;
        while (flag) {
            pop[i] = gera_individuo();
            flag = false;
            // Verifica se o individuo ja existe
            for (int j = 0; j < i; j++) {
                if (igual(pop[i], pop[j])) {
                    flag = true;
                    break;
                }
            }
        }
    }
}
