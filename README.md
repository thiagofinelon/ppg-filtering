# Filtragem e análise de sinal PPG para microcontroladores STM32F4

## Filtro digital IIR

Está sendo usado um filtro de topologia chebyshev tipo II de quarta ordem. Sendo essa topologia a que tem melhor performance para filtragem de sinais PPG de curta duração. Os parametros de sintonização do filtro são:

 - $\omega_{corte}$: $4hz$
 - $\omega_{amostragem}$: $25hz$
 - Atenuação de banda de rejeição: $-20db$

 Para o filtro projetado temos a seguinte resposta em frequencia:

 ![plot](C:\Users\thiag\Documents\Faculdade\TCC\repo\ppg-filtering\filter\freq_response.png)

 ## Sensor de sinal PPG 
Foi usado nesse projeto o sensor de baixo custo Amped

![plot](C:\Users\thiag\Documents\Faculdade\TCC\repo\ppg-filtering\data\sensor_amped.png)
