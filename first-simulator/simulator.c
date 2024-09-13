#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct {
    unsigned long int num_eventos;
    double tempo_anterior;
    double soma_areas;
} little;

double uniforme(){
    double u = rand() / ((double) RAND_MAX + 1);
    u = 1.0 - u;
    return u;
}

double gera_tempo(double l){
    return (-1.0/l) * log(uniforme());
}

double min(double n1, double n2){
    if (n1 < n2) return n1;
    return n2;
}

void inicia_little(little *n){
    n->num_eventos = 0;
    n->soma_areas = 0.0;
    n->tempo_anterior = 0.0;
}

void simula_cenario(double taxa_chegada, double taxa_saida, double tempo_simulacao){
    double tempo_decorrido = 0.0;
    double tempo_chegada = gera_tempo(taxa_chegada);
    double tempo_saida = DBL_MAX;

    unsigned long int fila = 0;
    unsigned long int fila_max = 0;

    double soma_ocupacao = 0.0;

    little en;
    little ew_chegadas;
    little ew_saidas;
    inicia_little(&en);
    inicia_little(&ew_chegadas);
    inicia_little(&ew_saidas);

    int tempo_coleta = 100;

    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = min(tempo_coleta, min(tempo_chegada, tempo_saida));

        if(tempo_decorrido == tempo_coleta) {
            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
            ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;

            en.tempo_anterior = tempo_decorrido;
            ew_chegadas.tempo_anterior = tempo_decorrido;
            ew_saidas.tempo_anterior = tempo_decorrido;

            double en_final = en.soma_areas / tempo_decorrido;
            double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
            double lambda = ew_chegadas.num_eventos / tempo_decorrido;

            printf("E[N]: %lf\n", en_final);
            printf("E[W]: %lf\n", ew_final);
            printf("Erro de Little: %lf\n", en_final - lambda * ew_final);

            tempo_coleta += 100;
        }else if(tempo_decorrido == tempo_chegada){
            // sistema está ocioso?
            if(!fila){
                tempo_saida = tempo_decorrido + gera_tempo(taxa_saida);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }
            fila++;
            fila_max = fila > fila_max ? fila : fila_max;
            tempo_chegada = tempo_decorrido + gera_tempo(taxa_chegada);

            // Little
            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
            en.num_eventos++;
            en.tempo_anterior = tempo_decorrido;

            ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
            ew_chegadas.num_eventos++;
            ew_chegadas.tempo_anterior = tempo_decorrido;

            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;
            ew_saidas.num_eventos++;
            ew_saidas.tempo_anterior = tempo_decorrido;
        } else {
            fila--;
            tempo_saida = DBL_MAX;
            // tem mais requisições na fila?
            if(fila){
                tempo_saida = tempo_decorrido + gera_tempo(taxa_saida);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }

            // Little
            en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
            en.num_eventos--;
            en.tempo_anterior = tempo_decorrido;

            ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;
            ew_saidas.num_eventos++;
            ew_saidas.tempo_anterior = tempo_decorrido;
        }
    }

    ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
    ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;

    printf("Maior tamanho de fila alcançado: %lu\n", fila_max);
    printf("Ocupacao: %lf\n", soma_ocupacao / tempo_decorrido);
    double en_final = en.soma_areas / tempo_decorrido;
    double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
    double lambda = ew_chegadas.num_eventos / tempo_decorrido;

    printf("E[N]: %lf\n", en_final);
    printf("E[W]: %lf\n", ew_final);
    printf("Erro de Little: %lf\n", en_final - lambda * ew_final);
}

int main(){
    srand(time(NULL));
    double tempos[4] = {0.80, 0.90, 0.95, 0.99}; 
    double tempo_simulacao = 100000.0; 

    for(int i = 0; i < 4; i++) {
        double ocupacao = tempos[i];
        printf("\nCenario de ocupacao: %.2f\n", ocupacao);
        double taxa_saida = 1.0 / (ocupacao / (1.0 - ocupacao)); 
        double taxa_chegada = 1.0 / ((1.0 - ocupacao) / ocupacao); 
        simula_cenario(taxa_chegada, taxa_saida, tempo_simulacao);
    }

    return 0;
}
