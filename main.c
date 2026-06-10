#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numeroConta;
    char nome[50];
    float saldo;
} Cliente;

const char *NOME_ARQUIVO = "contas.bin";

// Protótipos
void cadastrarCliente();
void consultarCliente();
void atualizarSaldo();
void encerrarConta();
void listarClientes();

int main() {
    int opcao;
    do {
        printf("\n--- SISTEMA BANCARIO ---\n");
        printf("1. Cadastrar cliente em posicao especifica\n");
        printf("2. Consultar cliente pelo numero da conta\n");
        printf("3. Atualizar saldo\n");
        printf("4. Encerrar conta (remover)\n");
        printf("5. Listar todos os clientes\n");
        printf("6. Restaurar leitura (rewind)\n");
        printf("7. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: consultarCliente(); break;
            case 3: atualizarSaldo(); break;
            case 4: encerrarConta(); break;
            case 5: listarClientes(); break;
            case 6: printf("Leitura restaurada com rewind().\n"); break;
            case 7: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}

void cadastrarCliente() {
    FILE *fp = fopen(NOME_ARQUIVO, "rb+");
    if (!fp) fp = fopen(NOME_ARQUIVO, "wb+");

    Cliente c;
    int pos;
    printf("Digite o numero da conta, nome e saldo: ");
    scanf("%d %s %f", &c.numeroConta, c.nome, &c.saldo);
    printf("Digite a posicao (0 para a primeira): ");
    scanf("%d", &pos);

    fseek(fp, pos * sizeof(Cliente), SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, fp);
    fclose(fp);
}

void consultarCliente() {
    FILE *fp = fopen(NOME_ARQUIVO, "rb");
    int busca, achou = 0;
    Cliente c;
    printf("Digite o numero da conta para buscar: ");
    scanf("%d", &busca);

    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.numeroConta == busca) {
            printf("Conta: %d | Nome: %s | Saldo: %.2f\n", c.numeroConta, c.nome, c.saldo);
            achou = 1;
            break;
        }
    }
    if (!achou) printf("Conta nao encontrada.\n");
    fclose(fp);
}

void atualizarSaldo() {
    FILE *fp = fopen(NOME_ARQUIVO, "rb+");
    int busca;
    Cliente c;
    printf("Digite o numero da conta para atualizar saldo: ");
    scanf("%d", &busca);

    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.numeroConta == busca) {
            printf("Novo saldo: ");
            scanf("%f", &c.saldo);
            fseek(fp, -((long)sizeof(Cliente)), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, fp);
            break;
        }
    }
    fclose(fp);
}

void encerrarConta() {
    // Para remover em arquivos binários de tamanho fixo, marca-se o registro como vazio
    // ou sobrescreve com uma estrutura zerada.
    FILE *fp = fopen(NOME_ARQUIVO, "rb+");
    int busca;
    Cliente c, vazio = {0, "", 0.0};
    printf("Digite o numero da conta para encerrar: ");
    scanf("%d", &busca);

    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.numeroConta == busca) {
            fseek(fp, -((long)sizeof(Cliente)), SEEK_CUR);
            fwrite(&vazio, sizeof(Cliente), 1, fp);
            printf("Conta removida.\n");
            break;
        }
    }
    fclose(fp);
}

void listarClientes() {
    FILE *fp = fopen(NOME_ARQUIVO, "rb");
    rewind(fp); // Exemplo de uso de rewind() antes de listar
    Cliente c;
    printf("\n--- LISTAGEM ---\n");
    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.numeroConta != 0)
            printf("Conta: %d | Nome: %s | Saldo: %.2f\n", c.numeroConta, c.nome, c.saldo);
    }
    fclose(fp);
}