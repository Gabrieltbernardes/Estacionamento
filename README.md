# 🚗 Sistema de Estacionamento com Filas em C

Este projeto implementa um sistema de controle de estacionamento usando a linguagem C, com estrutura de **filas encadeadas** para gerenciar:

- Estacionamento (capacidade máxima de 5 carros)
- Fila de espera
- Rua auxiliar (para manobras de saída)

## 🧠 Funcionalidades

- Adicionar carro ao estacionamento ou à fila de espera
- Prioridade para veículos (emergência)
- Remoção de veículos do estacionamento
- Contabilização de deslocamentos para cada carro
- Visualização do estado atual das filas

## 🗃️ Estruturas Utilizadas

- `TipoItem`: representa um carro (placa, prioridade e deslocamentos)
- `TipoFila`: fila encadeada com ponteiros para frente e trás
- Funções auxiliares para enfileirar, desenfileirar, exibir e mover veículos
