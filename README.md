# 🚀 AndrewScript v1.0

Uma linguagem de script leve, interpretada linha por linha, construída do zero sobre C++. O motor executa em tempo real através de um REPL (terminal interativo) com suporte a variáveis dinâmicas, operações aritméticas básicas, condicionais estruturadas e loops de repetição.

---

## 🏗️ Arquitetura do Projeto

Para garantir alta manutenibilidade, o interpretador foi modularizado e dividido em 4 arquivos com responsabilidades bem definidas:

* **`environment.hpp`**: Gerencia a memória global da linguagem (o mapa de variáveis compartilhado).
* **`evaluator.hpp` / `.cpp`**: O cérebro matemático. Avalia expressões aritméticas (`+`, `-`, `*`, `/`), resolve valores e processa condições lógicas (`>`, `<`, `==`, `!=`).
* **`parser.hpp` / `.cpp`**: O diretor de tráfego. Varre as strings brutas do terminal, identifica o comando correto (`write`, `read`, `if`, `for` ou atribuição) e direciona para execução.
* **`main.cpp`**: O ponto de entrada que gerencia o loop principal do terminal interativo (REPL).

---

## 📜 Sintaxe da Linguagem

### 1. Criação e Atribuição de Variáveis
Não precisa declarar tipo. Basta atribuir um valor matemático ou direto.

```
x = 10
y = 5
resultado = x * y + 2
nome = "Andrew"
```
### 2. Entrada e Saída (I/O)
`write(expressão)`: Imprime o resultado de uma variável ou conta matemática na tela.

`read(variável)`: Pausa o terminal e espera o usuário digitar um número para salvar na variável.

```
read(idade)
write(idade + 1)
write("Hello world!")
```

### 3. Condicionais (if)

Executa um comando na mesma linha se a condição interna for verdadeira. Suporta `>`, `<`, `==` e `!=`.

```
if(x > 5) write(x * 2)
```

### 4. Estrutura de Repetição (for)

Loop compacto indexado por vírgulas. Define (atribuição inicial, condição de parada, incremento).

```
for(i = 0, i < 10, 2) write(i)
```

### 5. Executar Arquivos de Script

No interpretador, use `sc_open(nome_do_arquivo)` para abrir um arquivo AndrewScript.

### 6. Outras Funções

|Função|Descrição|
|---|---|
|`delay(x)`|Delay em milissegundos|
|`import(nome_arquivo)`|Importa arquivos de código-fonte para o projeto|
|`clear()`|Limpa o console|

### 🛠️ Como Compilar e Rodar
Como o projeto está separado em múltiplos arquivos, o compilador do C++ (g++) precisa juntar todos os arquivos de implementação (.cpp) de uma vez só.

```
g++ main.cpp parser.cpp evaluator.cpp -o andrewscript && ./andrewscript
```

Digite o código no terminal, linha a linha. Para sair, digite `return`.