#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDIDORES 50
typedef struct Piscina{
	char dia[50], data[11], quimico[30];
	float produto;
	float ph[3];
	int quantidadeagua, ativo;
} Medidor;
Medidor medidores[MAX_MEDIDORES];


void menu();
void cadastrar();
void remover();
void inapropriada();
void pesquisar();
void listar ();
void salvar ();

int main() { 
	menu();
	return 0;
}

void menu() {
	int op;
	do{	
		system("cls");
		printf("\n1 - Cadastrar Dados\n2 - Remover Dados\n");
		printf("\n3 - Dados Inapropriados\n4 - Pesquisar Dados\n");
		printf("\n5 - Listar Dados\n6 - Salvar\n");
		printf("\n0 - Sair\n\n");
		scanf("%d", &op);
		getchar();
		switch(op) {
			case 1:
				cadastrar();
			break;
			case 2:
				remover();
			break;
			case 3:
				inapropriada();
			break;
			case 4:
				pesquisar();
			break;
			case 5:
				listar();
			break;
			case 6:
				salvar();
			break;
		}
		getchar();
	}while(op!=0);
}

void cadastrar() {
	system("cls");
	char dia[50], quimico[30];
	float produto;
	char data[11];
	float ph[3];
	int quantidadeagua;
	int op; 
	do{	
		system("cls");
		printf("\nDia da semana: ");
		fgets(dia, sizeof(dia), stdin);
		printf("\nData da medicao no formato -> ano, mes e dia XXXX-XX-XX: ");
		setbuf(stdin, NULL);
		gets(data);
		printf("\nProduto quimico usado hoje: ");
		setbuf(stdin, NULL);
		gets(quimico);
		printf("\nPH do primeiro periodo: ");
		scanf("%f", &ph[0]);
		printf("\nPH do segundo periodo: ");
		scanf("%f", &ph[1]);
		printf("\nPH do terceiro periodo: ");
		scanf("%f", &ph[2]);
		printf("\nQuantidade de agua coletada em MLs: ");
		scanf("%i", &quantidadeagua);
		printf("\nQuantidade de Cloro na agua em gramas: ");
		scanf("%f", &produto);
		
		for (int i = 0; i < MAX_MEDIDORES; i++){
			if (medidores[i].ativo==0){ //variavel ativo é extremamente importante para a função de remoção e listagem, quando ela está com valor 1 está ativa para listar e 0 inativa
				
				medidores[i].ph[0]= ph[0];
				medidores[i].ph[1] = ph[1];
				medidores[i].ph[2] = ph[2];
				strcpy(medidores[i].dia, dia);
				strcpy(medidores[i].data, data);
				strcpy(medidores[i].quimico, quimico);
				medidores[i].produto = produto;
				medidores[i].quantidadeagua = quantidadeagua;
				medidores[i].ativo=1; //sempre ao final, adicionamos ativo = 1 para mostrar que o dado é válido
				break;
			}
		}
		printf("\n1 - Continuar\n0 - Sair\n");
		scanf("%d", &op);	
		getchar();
	}while(op!=0);
}

void remover() {
	int registro;
	listar();
	printf("\n Qual registro deve ser removido: ");
	scanf("%d", &registro);
	--registro;
	medidores[registro].ativo=0; // quando inativamos um registro, adicionamos o valor de 0 no ativo para que quando listarmos o mesmo não apareça mais, pois não faz mais parte dos cadastros ativos
	printf("\nDados do registro removidos!");
	getchar();
}

void inapropriada() {
	system("cls");
	float media;
	float *resultado;
	printf("\n Piscinas que estao inapropriadas para uso\n");
	for (int i = 0; i < MAX_MEDIDORES; i++){
	
		if (medidores[i].ativo==1){
			media = 0;
			media = medidores[i].ph[0] + medidores[i].ph[1] + medidores[i].ph[2];
			media = media/3;
			resultado = &media; //uso de ponteiro apontando para o endereço da variável media
			if (*resultado < 7.2 || *resultado > 7.6) {
	
				printf("\nregistro %d\n", i+1);
				printf("\nDia: %s\n", medidores[i].dia);
				printf("\nData: %s\n", medidores[i].data);
				printf("\nProduto usado: %s\n", medidores[i].quimico);
				printf("1 periodo: %0.2f\n", medidores[i].ph[0]);
				printf("2 periodo: %0.2f\n", medidores[i].ph[1]);
				printf("3 periodo: %0.2f\n", medidores[i].ph[2]);
				printf("Quantidade de cloro encontrado na agua em gramas: %0.2f\n",medidores[i].produto);
				printf("Quantidade de agua coletada em MLs: %i\n",medidores[i].quantidadeagua);
				printf("\n ------------------\n");
			}
	
		}
	}
}


void pesquisar() {
	char dia[50];
	int op;
	do{
		system("cls");
		printf("\n Digite o dia que deseja pesquisar: ");
		fgets(dia, sizeof(dia),stdin);
		for (int i = 0; i < MAX_MEDIDORES; i++) {
		
			if (strstr(medidores[i].dia,dia)!=NULL){ // utilizado função STRSTR para ver se a strings são iguais
							
				printf("\nregistro %d\n", i+1);
				printf("\nDia: %s\n", medidores[i].dia);
				printf("\nData: %s\n", medidores[i].data);
				printf("\nProduto usado: %s\n", medidores[i].quimico);
				printf("1 periodo: %0.2f\n", medidores[i].ph[0]);
				printf("2 periodo: %0.2f\n", medidores[i].ph[1]);
				printf("3 periodo: %0.2f\n", medidores[i].ph[2]);
				printf("Quantidade de cloro encontrado na agua em gramas: %0.2f\n",medidores[i].produto);
				printf("Quantidade de agua coletada em MLs: %i\n",medidores[i].quantidadeagua);
				printf("\n ------------------\n");
				
			}
		}
		printf("\nDeseja efetuar uma nova pesquisa?\n \nCaso sim, digite 1\nPara sair, digite 0 \n ");	
		scanf("%d", &op);
		getchar();
	}while(op!=0);
	
}

void listar() {
	system("cls");
	printf("\n LISTA DE DADOS\n");
	for (int i = 0; i < MAX_MEDIDORES; i++) {
		if (medidores[i].ativo==1) {
			
			printf("\nregistro %d\n", i+1); //o registro é essencial para criarmos uma sequencia de número por cadastro e também será nosso parametro na função remover para saber qual dado será excluido
			printf("\nDia da semana: %s", medidores[i].dia);
			printf("\nData da coleta: %s\n", medidores[i].data);
			printf("\nProduto usado: %s\n", medidores[i].quimico);
			printf("1 periodo: %0.2f\n", medidores[i].ph[0]);
			printf("2 periodo: %0.2f\n", medidores[i].ph[1]);
			printf("3 periodo: %0.2f\n", medidores[i].ph[2]);
			printf("Quantidade de cloro encontrado na agua em gramas: %0.2f\n",medidores[i].produto);
			printf("Quantidade de agua coletada em MLs: %i\n",medidores[i].quantidadeagua);
			printf("\n ------------------\n");
		}
	} 
}

void salvar() {
	FILE *arq;
	arq = fopen("arquivo.txt", "w");
	
	if(arq == NULL) {
		printf("arquivo não pode ser aberto");
		getchar();
	}
	
	for (int i = 0; i < MAX_MEDIDORES; i++) {
		if (medidores[i].ativo==1) {  // note que aqui a variavel ativo é importante também, pois sem ele o loop percorre as 50 posições do array max_medidor e traz as posição que ainda não foram preenchidas também
			
			fprintf(arq, "Dia: %s\n", medidores[i].dia);
			fprintf(arq, "Data: %s\n", medidores[i].data);
			fprintf(arq, "Produto usado: %s\n", medidores[i].quimico);
			fprintf(arq, "1 periodo: %0.2f\n", medidores[i].ph[0]);
			fprintf(arq, "2 periodo: %0.2f\n", medidores[i].ph[1]);
			fprintf(arq, "3 periodo: %0.2f\n", medidores[i].ph[2]);
			fprintf(arq, "Quantidade de cloro encontrado na agua em gramas: %0.2f\n", medidores[i].produto);
			fprintf(arq, "Quantidade de agua coletada em MLs: %i\n", medidores[i].quantidadeagua);
		}
	}
	fclose(arq);
	
	printf("\nArquivo criado com sucesso");
	getchar();
}
	
	
