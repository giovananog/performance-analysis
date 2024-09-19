# Configurações globais
set terminal svg size 800,600
set key outside # A legenda será colocada fora do gráfico
set datafile separator ','  # Define a vírgula como separador de colunas

# Gráfico 1: Ocupação pelo tempo
set output 'grafico_ocupacao.svg'
set title "Ocupação pelo Tempo Decorrido"
set xlabel "Tempo Decorrido (s)"
set ylabel "Ocupação"
set yrange [0.65:1]  
set ytics ("0.85" 0.85, "0.90" 0.90, "0.95" 0.95, "0.99" 0.99)
set xtics 10000  # Deixa o eixo X mais espaçado, ajustando os intervalos
plot "resultado_cenario_0.85_ocupacao.txt" using 1:2 with lines title "Ocupação 0.85", \
     "resultado_cenario_0.90_ocupacao.txt" using 1:2 with lines title "Ocupação 0.90", \
     "resultado_cenario_0.95_ocupacao.txt" using 1:2 with lines title "Ocupação 0.95", \
     "resultado_cenario_0.99_ocupacao.txt" using 1:2 with lines title "Ocupação 0.99"


# Gráfico 2: E[N] pelo tempo
set output 'grafico_en.svg'
set title "E[N] pelo Tempo Decorrido"
set ylabel "E[N]"
set yrange [0:*]  # Permite que o gráfico se ajuste automaticamente ao maior valor de E[N]
set ytics auto    # Gera intervalos automáticos no eixo Y
plot "resultado_cenario_0.85_en.txt" using 1:2 with lines title "E[N] 0.85", \
     "resultado_cenario_0.90_en.txt" using 1:2 with lines title "E[N] 0.90", \
     "resultado_cenario_0.95_en.txt" using 1:2 with lines title "E[N] 0.95", \
     "resultado_cenario_0.99_en.txt" using 1:2 with lines title "E[N] 0.99"


# Gráfico 3: E[W] pelo tempo
set output 'grafico_ew.svg'
set title "E[W] pelo Tempo Decorrido"
set ylabel "E[W]"
set yrange [0:*]  # Ajusta automaticamente para os valores de E[W]
set ytics auto    # Intervalos automáticos para o eixo Y
plot "resultado_cenario_0.85_ew.txt" using 1:2 with lines title "E[W] 0.85", \
     "resultado_cenario_0.90_ew.txt" using 1:2 with lines title "E[W] 0.90", \
     "resultado_cenario_0.95_ew.txt" using 1:2 with lines title "E[W] 0.95", \
     "resultado_cenario_0.99_ew.txt" using 1:2 with lines title "E[W] 0.99"


# Gráfico 4: Lambda pelo tempo
set output 'grafico_lambda.svg'
set title "Lambda pelo Tempo Decorrido"
set ylabel "Lambda"
set yrange [4.9:*]  # Ajusta o eixo Y entre 0 e 1 para Lambda
set ytics 0.1  # Define intervalos de 0.1 para o eixo Y
plot "resultado_cenario_0.85_lambda.txt" using 1:2 with lines title "Lambda 0.85", \
     "resultado_cenario_0.90_lambda.txt" using 1:2 with lines title "Lambda 0.90", \
     "resultado_cenario_0.95_lambda.txt" using 1:2 with lines title "Lambda 0.95", \
     "resultado_cenario_0.99_lambda.txt" using 1:2 with lines title "Lambda 0.99"


# Gráfico 5: Erro de Little pelo tempo
set output 'grafico_erro_little.svg'
set title "Erro de Little pelo Tempo Decorrido"
set ylabel "Erro de Little"
set yrange [-0.2:0.2]  # Ajusta o eixo Y para variação simétrica (-0.5 a 0.5)
set ytics 0.1  # Define intervalos de 0.1 no eixo Y
plot "resultado_cenario_0.85_little.txt" using 1:2 with lines title "Erro 0.85", \
     "resultado_cenario_0.90_little.txt" using 1:2 with lines title "Erro 0.90", \
     "resultado_cenario_0.95_little.txt" using 1:2 with lines title "Erro 0.95", \
     "resultado_cenario_0.99_little.txt" using 1:2 with lines title "Erro 0.99"
