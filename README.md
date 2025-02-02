# Temporizador de Um Disparo (One Shot) - Raspberry Pi Pico W

Este projeto implementa um sistema de temporização para o acionamento de LEDs utilizando o microcontrolador Raspberry Pi Pico W. O sistema aciona três LEDs (azul, vermelho e verde) com base no clique de um botão (pushbutton) e realiza uma mudança sequencial de estados dos LEDs a cada 3 segundos. O projeto utiliza a função `add_alarm_in_ms()` do Pico SDK para configurar temporizadores e funções callback.

---

## 🎯 **Objetivo**

O objetivo do projeto é criar um sistema de temporização de LEDs em resposta ao clique de um botão, com a mudança de estado dos LEDs acontecendo após um intervalo de 3 segundos. O sistema deve atender aos seguintes requisitos:

1. **Sequência de LEDs**:
   - Quando o botão for pressionado, todos os LEDs (azul, vermelho e verde) serão acionados.
   - Após 3 segundos, o LED azul será desligado, mantendo o LED vermelho e verde acesos.
   - Após mais 3 segundos, o LED vermelho será desligado, mantendo apenas o LED vermelho aceso.
   - Após 3 segundos, o LED vermelho será desligado, finalizando a sequência.

2. **Comportamento do botão**:
   - O botão só poderá alterar o estado dos LEDs quando o último LED for desligado. Durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada de função callback.

3. **Debounce** (Opcional):
   - Implementação de uma rotina em software para atenuação do efeito de "bouncing" no botão (software debounce).

---

## 🛠 **Componentes Necessários**

- **Microcontrolador**: Raspberry Pi Pico W
- **LEDs**: Azul, Vermelho e Verde
- **Resistores**: 3 resistores de 330Ω (1 para cada LED)
- **Botão**: Pushbutton
- **Ferramenta de Simulação**: Wokwi (opcional: BitDogLab)

---

## ⚡ **Esquema de Ligação**

| Componente          | GPIO |
|---------------------|------|
| LED Azul            | 11   |
| LED Vermelho        | 12   |
| LED Verde           | 13   |
| Botão Pushbutton    | 5    |

**Observação**: Para o experimento na **Ferramenta Educacional BitDogLab**, os LEDs estarão nas portas **GPIO 11, 12 e 13**, e o botão estará na **GPIO 05**.

---

## 🚀 **Como Compilar e Executar**

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/adimael/u4c4-timer-shooting.git
   ````
2. **Entre na pasta do projeto**:
   ````
   cd u4c4-timer-shooting
   ````

### **1️⃣ Configurar o Ambiente de Desenvolvimento**
Certifique-se de ter instalado o **Raspberry Pi Pico SDK** e o **compilador C/C++**. Se ainda não configurou, siga as etapas abaixo:

### Passo 1: Baixar o Ninja
   1. Acesse a página oficial de releases do Ninja:  
   [Ninja Releases no GitHub](https://github.com/ninja-build/ninja/releases).
   2. Baixe o arquivo binário mais recente para Windows (geralmente um `.zip`).
   3. Extraia o conteúdo do arquivo `.zip` (haverá um arquivo `ninja.exe`).

   ---

   ### Passo 2: Adicionar o Ninja ao Path do sistema
   Para que o `ninja` seja reconhecido como um comando em qualquer terminal, siga estas etapas:

   1. Clique com o botão direito no botão **Iniciar** e selecione **Configurações**.
   2. Vá em **Sistema** → **Sobre** → **Configurações avançadas do sistema** (no lado direito).
   3. Na aba **Avançado**, clique em **Variáveis de Ambiente**.
   4. Na seção **Variáveis do Sistema**, localize a variável `Path` e clique em **Editar**.
   5. Clique em **Novo** e adicione o caminho completo para o diretório onde você extraiu o `ninja.exe`. Por exemplo:
      ````
      C:\Users\SeuUsuario\Downloads\ninja-win
      ````
   6. Clique em **OK** em todas as janelas.

   ---

   ### Passo 3: Verificar se o Ninja está funcionando
   1. Abra um terminal (PowerShell ou Prompt de Comando).
   2. Digite o comando abaixo para verificar a instalação:
      ```bash
      ninja --version
      ````

   ### Passo 4: Configurar e Compilar o Projeto

   1. Volte ao diretório do projeto e abra um terminal.
   2. Crie ou limpe a pasta `build`:
      ```bash
      rmdir /s /q build
      mkdir build
      cd build
      
   3. Configure o projeto com o CMake:
      ```bash
      cmake -G Ninja ..
      ````
   4. Compile o projeto:

      ```bash
         ninja
      ````

   5. Após isso, o arquivo main.elf será gerado na pasta build.

### Pré-requisitos
- **Placa BitDogLab** configurada e conectada.
- Ambiente de desenvolvimento configurado com **SDK do RP2040**.

   ou

- Use a extensão do Wokwi no VSCode [https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode)