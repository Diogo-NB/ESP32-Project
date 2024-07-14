# Descrição

Projeto que utiliza um microcontrolador ESP32 para coletar dados de volume de líquido presente em um recipiente e representar esses dados em tempo real em um website.
Dispositivos e Ferramentas Utilizadas

* **Microcontrolador:** ESP32 + Sensor ultrassônico HC-SR04 (utilizando a placa de prototipação [Vespa](https://www.robocore.net/placa-robocore/vespa))
* **Banco de Dados:** [MongoDB Atlas](https://www.mongodb.com/atlas)
* **Back-end:** Node.js + Express framework
* **Front-end:** HTML, CSS, JavaScript utilizando a biblioteca [Chart.js](https://www.chartjs.org/) para exibição de gráficos

# Como Funciona

1. **Medição da Distância:** O sensor ultrassônico é posicionado no topo do recipiente para medir a distância até o nível do líquido.
2. **Cálculo do Volume:** O ESP32 coleta o sinal do sensor e calcula a distância. A distância é utilizada para calcular o volume do líquido por meio de um polinômio de segundo grau, cujos coeficientes foram obtidos usando uma regressão quadrática.
3. **Envio dos Dados:** O ESP32 envia o volume calculado periodicamente para o back-end via requisições HTTP.
4. **Armazenamento dos Dados:** O back-end armazena cada volume no banco de dados MongoDB.
5. **Visualização em Tempo Real:** O website periodicamente coleta as últimas leituras de volume do back-end e atualiza um gráfico para representar as mudanças de volume ao longo do tempo.

# Como Configurar o Back-end

1. **Configurar o MongoDB:**
    * Crie uma instância no MongoDB com um banco de dados chamado `ESP32` e uma coleção chamada `water-level`.
    * Permita o acesso do banco de dados ao back-end adicionando o IP do servidor à whitelist de IPs do MongoDB.

2. **Configurar o Servidor:**
    * Navegue até a pasta `server`.
    * Crie um arquivo `.env` no diretório raiz do servidor e preencha o arquivo com:
      ```env
      MONGODB_URL="URL_CONEXAO_MONGODB"
      ```
    * Instale as dependências executando npm install no terminal.
      ```terminal
      npm install
      ```
    * Inicie o servidor executando npm start no terminal.
      ```terminal
      npm start
      ```

4. **Configurar o ESP32:**
    No código do ESP32, configure SSID da rede Wi-Fi, senha da rede Wi-Fi, endereço IP e porta do servidor (HOST).
    ```cpp
    #define STASSID "WIFI_SIID"
    #define STAPSK "WIFI_PSSWD"
    #define HOST "SERVER_IP"
    #define PORT 3000
    ```

Observação: Certifique-se que o Server e o ESP32 estejam na mesma rede
