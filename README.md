# Minishell

Implementação de um shell Unix minimalista em C, desenvolvido como parte do currículo da 42SP.

## 📚 Sobre o Projeto

Este projeto visa criar um shell que interpreta e executa comandos de forma semelhante ao Bash. Os principais objetivos incluem:

- Execução de comandos com argumentos
- Redirecionamentos de entrada e saída (`<`, `>`, `>>`, `<<`)
- Pipes (`|`) para encadeamento de comandos
- Expansão de variáveis de ambiente (ex: `$HOME`)
- Tratamento de sinais (`Ctrl+C`, `Ctrl+D`, etc.)
- Implementação de comandos internos (`cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`)

### 🧩 Estruturas de Dados

Para o gerenciamento eficiente das operações internas, diversas estruturas de dados foram desenvolvidas e utilizadas, incluindo:

- **Listas encadeadas** para armazenar variáveis de ambiente e tokens de comandos.
- **Árvores binárias** utilizadas na construção da árvore de execução, representando comandos, redirecionamentos e pipes em uma estrutura hierárquica.
- **Stacks e filas internas** para manipulação de input e controle de fluxo de execução.

Essas estruturas foram projetadas para oferecer flexibilidade, modularidade e eficiência na execução dos comandos do shell.

## 🛠️ Estrutura do Projeto

- **include/**: Arquivos de cabeçalho (`.h`) com definições de estruturas e funções.
- **src/**: Código-fonte principal do shell.
- **lib/**: Bibliotecas auxiliares, como a `libft`.
- **Makefile**: Script para compilação do projeto.

## 🚀 Compilação e Execução

Para compilar o projeto:

```bash
make
```

Após a compilação, execute o shell com:

```bash
./minishell
```

## 🧪 Testes e Exemplos

Você pode testar o shell utilizando comandos como:

```bash
ls -l | grep minishell > output.txt
echo $HOME
cd ..
```

## 👤 Autor

- [Rafael](https://github.com/leafarRafael)

---

# Minishell

Implementation of a minimalist Unix shell in C, developed as part of the 42SP curriculum.

## 📚 About the Project

This project aims to create a shell that interprets and executes commands similarly to Bash. The main objectives include:

- Execution of commands with arguments
- Input and output redirections (`<`, `>`, `>>`, `<<`)
- Pipes (`|`) for command chaining
- Environment variable expansion (e.g., `$HOME`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, etc.)
- Implementation of built-in commands (`cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`)

### 🧩 Data Structures

To manage the internal operations efficiently, several data structures were developed and used, including:

- **Linked lists** to store environment variables and command tokens.
- **Binary trees** used for building the execution tree, representing commands, redirections, and pipes in a hierarchical structure.
- **Internal stacks and queues** to manage input and control the execution flow.

These structures were designed to provide flexibility, modularity, and efficiency in executing shell commands.

## 🛠️ Project Structure

- **include/**: Header files (`.h`) with structure and function definitions.
- **src/**: Main source code of the shell.
- **lib/**: Auxiliary libraries, such as `libft`.
- **Makefile**: Script for project compilation.

## 🚀 Compilation and Execution

To compile the project:

```bash
make
```

After compilation, run the shell with:

```bash
./minishell
```

## 🧪 Testing and Examples

You can test the shell using commands like:

```bash
ls -l | grep minishell > output.txt
echo $HOME
cd ..
```

## 👤 Author

- [Rafael](https://github.com/leafarRafael)
