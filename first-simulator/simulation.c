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

void atualiza_little(little *n, double tempo_atual) {
    n->soma_areas += (tempo_atual - n->tempo_anterior) * n->num_eventos;
    n->tempo_anterior = tempo_atual;
}

void simula_cenario(double taxa_media_chegada, double capacidade, double tempo_simulacao, const char* nome_arquivo){
    double tempo_decorrido = 0.0;
    double tempo_chegada = gera_tempo(taxa_media_chegada);
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

    FILE *arquivo_csv = fopen(nome_arquivo, "w");
    if (arquivo_csv == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", nome_arquivo);
        return;
    }

    // Cabeçalho do CSV
    fprintf(arquivo_csv, "Tempo Decorrido,Taxa Media Chegada,Taxa Saída,E[N],E[W],Lambda, Erro de Little,Ocupacao\n");

    while(tempo_decorrido <= tempo_simulacao){
        tempo_decorrido = min(tempo_coleta, min(tempo_chegada, tempo_saida));

        if(tempo_decorrido == tempo_coleta) {
            atualiza_little(&en, tempo_decorrido);
            atualiza_little(&ew_chegadas, tempo_decorrido);
            atualiza_little(&ew_saidas, tempo_decorrido);

            double en_final = en.soma_areas / tempo_decorrido; 
            double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
            double lambda = ew_chegadas.num_eventos / tempo_decorrido;
            double erro_little = en_final - lambda * ew_final; 

            double ocupacao = soma_ocupacao / tempo_decorrido;

            fprintf(arquivo_csv, "%lf,%.2f,%.2f,%lf,%lf,%lf, %lf,%lf\n", tempo_decorrido, taxa_media_chegada, capacidade, en_final, ew_final, lambda, erro_little, ocupacao);

            tempo_coleta += 100;
        } else if(tempo_decorrido == tempo_chegada) {
            if(!fila){
                tempo_saida = tempo_decorrido + gera_tempo(capacidade);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }
            fila++;
            fila_max = fila > fila_max ? fila : fila_max;
            tempo_chegada = tempo_decorrido + gera_tempo(taxa_media_chegada);

            atualiza_little(&en, tempo_decorrido);
            en.num_eventos++; 

            atualiza_little(&ew_chegadas, tempo_decorrido);
            ew_chegadas.num_eventos++;

        } else {
            fila--;
            tempo_saida = DBL_MAX;
            if(fila){
                tempo_saida = tempo_decorrido + gera_tempo(capacidade);
                soma_ocupacao += tempo_saida - tempo_decorrido;
            }

            atualiza_little(&en, tempo_decorrido);
            en.num_eventos--; 

            atualiza_little(&ew_saidas, tempo_decorrido);
            ew_saidas.num_eventos++; 
        }
    }

    // Última atualização de Little
    atualiza_little(&ew_chegadas, tempo_decorrido);
    atualiza_little(&ew_saidas, tempo_decorrido);

    double en_final = en.soma_areas / tempo_decorrido;
    double ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
    double lambda = ew_chegadas.num_eventos / tempo_decorrido;
    double erro_little = en_final - lambda * ew_final;

    fprintf(arquivo_csv, "%lf,%.2f,%.2f,%lf,%lf,%lf,%lu,%lf\n", tempo_decorrido, taxa_media_chegada, capacidade, en_final, ew_final, erro_little, fila_max, soma_ocupacao / tempo_decorrido);

    fclose(arquivo_csv);
}

int main(){
    srand(time(NULL));
    double tempos[4] = {0.85, 0.90, 0.95, 0.99}; 
    double tempo_simulacao = 100000.0; 

    for(int i = 0; i < 4; i++) {
        double ocupacao = tempos[i];
        double taxa_media_chegada = 5.0; 
        double capacidade = taxa_media_chegada / ocupacao; 

        char nome_arquivo[50];
        snprintf(nome_arquivo, sizeof(nome_arquivo), "resultado_cenario_%.2f.csv", ocupacao);

        simula_cenario(taxa_media_chegada, capacidade, tempo_simulacao, nome_arquivo);
    }

    return 0;
}
