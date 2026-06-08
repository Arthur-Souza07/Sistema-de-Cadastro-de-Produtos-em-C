#include <stdio.h>
#include <math.h>
struct Item{
	int codigo_produto;
	char nome[50];
	float preco;
	};
int main() {
	FILE *bancoDados;
	int opcao;
	int proximo_codigo = 001;
	struct Item produto;
	do {
		printf("----MENU----\n");
		printf("Escolha o que deseja.\n");
		printf("1-Cadastrar item\n");
		printf("2-Procurar Item\n");
		printf("3-Sair\n");
		scanf("%i", &opcao);
		switch(opcao) {
			case 1:
				printf("Digite o nome do produto: \n");
				scanf(" %[^\n]", produto.nome);
				printf("Digite o preço: ");
				scanf("%f", &produto.preco);
				produto.codigo_produto = proximo_codigo;
				proximo_codigo++;
				bancoDados = fopen("bancoDados.txt", "a");
				fprintf(bancoDados, "%i\n%s\n%f\n", produto.codigo_produto, produto.nome, produto.preco);
				fclose(bancoDados);
				break;
			case 2:
				return 1;
				break;
			case 3:
				break;
		}
	} while(opcao != 3);
}