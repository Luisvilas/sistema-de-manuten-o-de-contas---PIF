# Sistema de Gerenciamento Bancário em C

Este projeto é um sistema de manutenção de contas bancárias desenvolvido em linguagem C. O objetivo principal é demonstrar o uso eficiente de **arquivos binários** e técnicas de **acesso direto** para persistência de dados.

## Funcionalidades

O sistema oferece um menu interativo com as seguintes operações:

1. **Cadastrar Cliente**: Adiciona um cliente em uma posição específica do arquivo.
2. **Consultar Cliente**: Busca informações através do número da conta.
3. **Atualizar Saldo**: Modifica o saldo de um cliente existente.
4. **Encerrar Conta**: Remove a conta do sistema (remoção lógica).
5. **Listar Clientes**: Exibe todos os registros ativos.
6. **Restaurar Leitura**: Utiliza `rewind()` para reiniciar o ponteiro do arquivo.
7. **Sair**: Finaliza a execução do programa.

## Tecnologias Utilizadas

*   **Linguagem**: C
*   **Persistência**: Arquivos binários (`.bin`)
*   **Funções de Arquivo**: `fseek()`, `fread()`, `fwrite()`, `rewind()`, `fopen()`, `fclose()`

| **Cadastrar** | `fseek()` + `fwrite()` | Move o ponteiro para o offset exato (`pos * sizeof(Cliente)`) e grava o registro. |

| **Consultar** | `fread()` | Percorre o arquivo sequencialmente para localizar o `numeroConta` correspondente. |

| **Atualizar** | `fseek()` + `fwrite()` | Após localizar o registro, retrocede o ponteiro (`fseek` com offset negativo) para sobrescrever apenas aquele bloco. |

| **Encerrar** | `fseek()` + `fwrite()` | Sobrescreve o registro com dados "zerados" (remoção lógica), mantendo a integridade do arquivo. |

| **Listar** | `rewind()` | Reseta o ponteiro para o início do arquivo antes de iniciar a leitura, garantindo que nenhum dado seja omitido. |

## Como Compilar e Executar

Certifique-se de ter o GCC instalado em seu sistema.

No terminal:
   gcc main.c -o sistema_bancario

Em seguida:
   ./sistema_bancario
