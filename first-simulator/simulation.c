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

void simula_cenario(double taxa_media_chegada, double capacidade, double tempo_simulacao, const char* arquivo_ocupacao,  const char* arquivo_ew,  const char* arquivo_en, const char* arquivo_lambda, const char* arquivo_little){
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

    FILE *arquivo_txt= fopen(arquivo_ocupacao, "w");
    if (arquivo_txt == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", arquivo_ocupacao);
        return;
    }

    FILE *arquivo_txt2 = fopen(arquivo_ew, "w");
    if (arquivo_txt2 == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", arquivo_ew);
        return;
    }

    FILE *arquivo_txt3 = fopen(arquivo_en, "w");
    if (arquivo_txt3 == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", arquivo_en);
        return;
    }

    FILE *arquivo_txt4 = fopen(arquivo_lambda, "w");
    if (arquivo_txt4 == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", arquivo_lambda);
        return;
    }

    FILE *arquivo_txt5 = fopen(arquivo_little, "w");
    if (arquivo_txt5 == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", arquivo_little);
        return;
    }

    // Cabeçalho do CSV
    fprintf(arquivo_txt, "Tempo Decorrido,Ocupacao\n");
    fprintf(arquivo_txt2, "Tempo Decorrido,E[W]\n");
    fprintf(arquivo_txt3, "Tempo Decorrido,E[N]\n");
    fprintf(arquivo_txt4, "Tempo Decorrido,Lambda\n");
    fprintf(arquivo_txt5, "Tempo Decorrido,Little\n");

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

            fprintf(arquivo_txt, "%lf,%.2f\n", tempo_decorrido, ocupacao);
            fprintf(arquivo_txt2, "%lf,%.2f\n", tempo_decorrido, ew_final);
            fprintf(arquivo_txt3, "%lf,%.2f\n", tempo_decorrido, en_final);
            fprintf(arquivo_txt4, "%lf,%.2f\n", tempo_decorrido, lambda);
            fprintf(arquivo_txt5, "%lf,%.20f\n", tempo_decorrido, erro_little);

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
    
    // ocupacao
    double ocupacao = soma_ocupacao / tempo_decorrido;


    fprintf(arquivo_txt, "%lf,%.2f\n", tempo_decorrido, ocupacao);
    fprintf(arquivo_txt2, "%lf,%.2f\n", tempo_decorrido, ew_final);
    fprintf(arquivo_txt3, "%lf,%.2f\n", tempo_decorrido, en_final);
    fprintf(arquivo_txt4, "%lf,%.2f\n", tempo_decorrido, lambda);
    fprintf(arquivo_txt5, "%lf,%.2f\n", tempo_decorrido, erro_little);

    fclose(arquivo_txt);
    fclose(arquivo_txt2);
    fclose(arquivo_txt3);
    fclose(arquivo_txt4);
    fclose(arquivo_txt5);
}

int main(){
    srand(5);
    double tempos[4] = {0.85, 0.90, 0.95, 0.99}; 
    double tempo_simulacao = 100000.0; 

    for(int i = 0; i < 4; i++) {
        double ocupacao = tempos[i];
        double taxa_media_chegada = 5.0; 
        double capacidade = taxa_media_chegada / ocupacao; 

        char arquivo_ocupacao[50];
        snprintf(arquivo_ocupacao, sizeof(arquivo_ocupacao), "resultado_cenario_%.2f_ocupacao.txt", ocupacao);

        char arquivo_ew[50];
        snprintf(arquivo_ew, sizeof(arquivo_ew), "resultado_cenario_%.2f_ew.txt", ocupacao);

        char arquivo_en[50];
        snprintf(arquivo_en, sizeof(arquivo_en), "resultado_cenario_%.2f_en.txt", ocupacao);

        char arquivo_lambda[50];
        snprintf(arquivo_lambda, sizeof(arquivo_lambda), "resultado_cenario_%.2f_lambda.txt", ocupacao);

        char arquivo_little[50];
        snprintf(arquivo_little, sizeof(arquivo_little), "resultado_cenario_%.2f_little.txt", ocupacao);

        simula_cenario(taxa_media_chegada, capacidade, tempo_simulacao, arquivo_ocupacao, arquivo_ew, arquivo_en, arquivo_lambda, arquivo_little);
    }

    return 0;
}
