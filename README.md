# Sistema de Atendimento Médico

Sistema desenvolvido para gerenciar pacientes e seu atendimento em uma clínica médica. O sistema utiliza conceitos de listas encadeadas, filas, pilhas e árvores binárias para gerenciar os dados de pacientes, consultas e históricos de atendimento.

## Desenvolvedores

- Paulo Hudson (Matrícula: 22.222.013-9)
- Danillo (Matrícula: 22.222.008-9)

## Requisitos

- Compilador C 
- Sistema operacional: Qualquer (desde que consiga compilar código C)

## Funcionalidades

### 1. Cadastro de Pacientes
- Cadastrar novos pacientes com nome, idade, RG e data de entrada.
- 
### 2. Gerenciamento de Pacientes
- Consultar, atualizar e remover pacientes cadastrados.

### 3. Fila de Atendimento
- Enfileirar e desenfileirar pacientes para atendimento.
- Desfazer o último atendimento realizado.

### 4. Árvore de Pesquisa
- Filtro de pacientes por ano, mês, dia de registro ou idade usando uma árvore binária.

### 5. Persistência
- Salvamento e carregamento de dados de pacientes em um arquivo de texto.

# Estruturas de Dados Utilizadas

Lista Encadeada: Para armazenar os pacientes cadastrados.
Fila: Para gerenciar pacientes aguardando atendimento.
Pilha: Para armazenar o histórico de atendimentos realizados.
Árvore Binária: Para filtrar e ordenar pacientes com base em diferentes critérios.
