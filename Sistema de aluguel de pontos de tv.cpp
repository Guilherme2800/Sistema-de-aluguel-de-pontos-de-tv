#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
typedef struct {
	char nome[50];
	int sexo, idade, pacote, quantidade, rg, mensalidade;
}registro_cliente;

registro_cliente cliente,cliente_nulo,cliente_aux;

FILE *arquivo_cliente;



void linha(){
	int i;
	for (i=1; i<=80; i++){
		printf("*");
	}
}

void menu(){
	system("cls");
	linha();
	setlocale(LC_ALL, "Portuguese");
	printf("\n                          Empresa de TV/Telefonia/Internet\n");
	linha();
	printf("\n\n\n MENU:");
	printf("\n\n 1.Cadastrar Cliente");
	printf("\n 2.Listagem Geral");
	printf("\n 3.Relatório Estatístico");
	printf("\n 4.Editar Cliente");
	printf("\n 5.Remover Cliente");
	printf("\n 6.Listar clientes por Pacote");
	printf("\n 0.Sair");
	printf("\n \n Opção:");
	
}

int procura(int rg){
	
	int p;
	p=0;
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	while(feof(arquivo_cliente)==0){
	 if (cliente.rg == rg)
	 return p;
	 else {
		 fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
		 p++;
		}	
	}
	return -1;
	
	
}

void cadastrar(){
	int outro,aux, aux1,posicao,rrg;
	do{
	arquivo_cliente=fopen("cliente.txt","a+b");
	linha();
	printf("\n                          Empresa de TV/Telefonia/Internet\n");
	linha();
	printf("\n\n                               Cadastrar Cliente");
	printf("\n\n Nome:");
	fflush(stdin);
	gets(cliente.nome);
	
	
	printf("\n Sexo(1-Fem/2-Mas):");
	scanf("%d",&cliente.sexo);
	if(cliente.sexo != 1 && cliente.sexo != 2){
		do{
		printf("\n Opção invalida, digite novamente:");
		scanf("%d",&cliente.sexo);
		}while((cliente.sexo != 1 &&  cliente.sexo != 2));
	}
	
	
	printf("\n Idade:");
	scanf("%d",&cliente.idade);
	
	printf("\n RG (Digite sem pontuação):");
	scanf("%d",&cliente.rg);
	
	if(cliente.rg < 100000000 || cliente.rg >999999999){
		do{
			
			printf("\n Tamanho do RG é invalido, Digite novamente:");
			scanf("%d",&cliente.rg);
			
		}while(cliente.rg < 100000000 || cliente.rg >999999999);
	}
	
	printf("\n Pacote(1-Premium/2-Ouro/3-Standard):");
	scanf("%d",&cliente.pacote);
	if((cliente.pacote != 1 && cliente.pacote != 2 && cliente.pacote!= 3)){
		do{
		printf("\n Opção invalida, digite novamente:");
		scanf("%d",&cliente.pacote);
		}while(cliente.pacote != 1 && cliente.pacote != 2 && cliente.pacote !=3);
	}
	
	printf("\n Quantidade de pontos:");
	scanf("%d",&cliente.quantidade);
	
	if(cliente.idade <18){
		printf("\n Não é possivel realizar o cadastro de menores de idade.");
		printf("\n\n O CADASTRAMENTO NÃO PODE SER CONCLUIDO.");
		fseek(arquivo_cliente,sizeof(registro_cliente),SEEK_SET);
		fwrite(&cliente_nulo,sizeof(registro_cliente),1,arquivo_cliente);
		aux=1;
	}
	

    
	cliente_aux.idade=cliente.idade;
	cliente_aux.sexo=cliente.sexo;
	cliente_aux.pacote=cliente.pacote;
	cliente_aux.quantidade=cliente.quantidade;
	cliente_aux.rg=cliente.rg;
	strcpy(cliente_aux.nome,cliente.nome);
	
	rrg=cliente.rg;
	posicao=procura(rrg);
	if (posicao != -1){
		printf("\n");
		linha();
	printf("\n Este RG já estar cadastrado");
	printf("\n\n O CADASTRAMENTO NÃO PODE SER CONCLUIDO.\n");
	linha();
	aux=1;
}
	cliente.idade=cliente_aux.idade;
	cliente.pacote=cliente_aux.pacote;
	strcpy(cliente.nome,cliente_aux.nome);
	cliente.quantidade=cliente_aux.quantidade;
	cliente.sexo=cliente_aux.sexo;
	cliente.rg=cliente_aux.rg;
	if(aux!=1){
	if(cliente.pacote == 1){
	cliente.mensalidade= 220 + (cliente.quantidade * 32);
}
if(cliente.pacote == 2){
	cliente.mensalidade = 170 +(cliente.quantidade * 27);
}
if (cliente.pacote == 3){
	cliente.mensalidade = 120 + (cliente.quantidade * 21);
}
	fseek(arquivo_cliente,0,SEEK_END);
	fwrite(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	printf("\n\nCliente cadastrado com sucesso!");
}
	printf("\n\n Cadastrar outro(1-sim/0-não)?");
	scanf("%d",&outro);
	if(outro != 1 && outro != 0){
		do{
		printf("\n Opção invalida, digite novamente:");
		scanf("%d",&outro);
		}while(outro != 0 && outro != 1);
	}
	system("cls");
	fclose(arquivo_cliente);
	
}while(outro != 0);
}

void listagem(){
	int i;
	arquivo_cliente=fopen("cliente.txt","r+b");
	linha();
	printf("\n                      Empresa de TV/Telefonia/Internet\n");
	linha();
	printf("\n                             Listagem Geral \n\n\n");
	rewind(arquivo_cliente);
	if(arquivo_cliente != NULL){
	
	printf(" Nome     idade    RG      sexo   pacote  pontos  mensalidade\n");
	linha();
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	while(feof(arquivo_cliente)==0){
		if(cliente.rg != 0){
			
			printf("\n  %s    %d   %d    %d    %d       %d         %d ", cliente.nome,cliente.idade,cliente.rg,cliente.sexo,cliente.pacote,cliente.quantidade,cliente.mensalidade);
		}
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
}else{
	printf("\n\n Arquivo não encontrado.");
}
	printf("\n");
	linha();
	printf("\n \nTecle ENTER para voltar ao menu...");
	getche();
}

void relatorio1(){
		int i, mulheres=0,mulheresouro=0,percentual=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	setlocale(LC_ALL, "Portuguese");
	linha();
	printf("\n                    Empresa de TV/Telefonia/Internet");
		printf("\n");
		linha();
		printf("\n \n                        Relatório Estatístico");
		printf("\n");
	
	if(arquivo_cliente != NULL){
		
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	
	while(feof(arquivo_cliente)==0){
		if(cliente.sexo == 1){
		mulheres++;	
		}
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
	
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	
		while(feof(arquivo_cliente)==0){
		if(cliente.sexo == 1 && cliente.pacote == 2){
		mulheresouro++;	
		}
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
	if(mulheres > 1){
	percentual= (mulheresouro*100)/mulheres;
	printf("\n");
	printf("\n Percentual de mulheres que solicitaram pacote ouro: %d PORCENTO\n \n",percentual);
}else{
	printf("\n Percentual de mulheres que solicitaram pacote ouro: NÃO HÁ REGISTROS\n \n");
}
}else{
	printf("\n Percentual de mulheres que solicitaram pacote ouro: NÃO HÁ ARQUIVO\n ");
}
	fclose(arquivo_cliente);
	
}

void relatorio2(){
	
		int i, clientep=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	setlocale(LC_ALL, "Portuguese");
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	
	if(arquivo_cliente != NULL){
	while(feof(arquivo_cliente)==0){
		if(cliente.quantidade > 3){
		clientep++;	
		}
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
	if(clientep > 1){
	printf("\n");
	printf("\n Quantidade de cliente com mais de 3 pontos de TV: %d \n",clientep);
}else{
	printf("\n Quantidade de cliente com mais de 3 pontos de TV: NÃO HÁ REGISTROS\n");
}
}else{
	printf("\n Quantidade de cliente com mais de 3 pontos de TV: NÃO HÁ ARQUIVO\n");
}
	fclose(arquivo_cliente);
	
		
}

void relatorio3(){
	int i, media=0, total=0,cont=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	setlocale(LC_ALL, "Portuguese");
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	
		if(arquivo_cliente != NULL){
	while(feof(arquivo_cliente)==0){
		if(cliente.quantidade != 0){
		total=cliente.quantidade+total;
		cont++;
	}
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
	if(total>1){
	media=total/cont;
	printf("\n");
	printf("\n Média da quantidade de pontos de TV: %d \n",media);
}else{
	printf("\n Média da quantidade de pontos de TV: NÃO HÁ REGISTROS\n");
}
}else{
	printf("\n Média da quantidade de pontos de TV: NÃO HÁ ARQUIVO\n");
}
	fclose(arquivo_cliente);
	
}

void relatorio4(){
		int i, total=0,media=0,count=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	setlocale(LC_ALL, "Portuguese");
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	
	if(arquivo_cliente != NULL){
	
	while(feof(arquivo_cliente)==0){
		if(cliente.idade > 60){
		total=cliente.mensalidade+total;
		count++;	
		}
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
	printf("\n");
	if(total>1){
	media=total/count;
	printf("\n Média da mensalidade dos clientes com mais de 60 anos: %d \n",media);
}else{
	printf("\n Média da mensalidade dos clientes com mais de 60 anos: NÃO HÁ REGISTROS\n");
}
}else{
	printf("\n Média da mensalidade dos clientes com mais de 60 anos: NÃO HÁ ARQUIVO\n");
}
	fclose(arquivo_cliente);
	
}

void relatorio5(){
	
		int i, total=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	setlocale(LC_ALL, "Portuguese");
	rewind(arquivo_cliente);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	
	if(arquivo_cliente != NULL){
	while(feof(arquivo_cliente)==0){
		total=cliente.mensalidade+total;
		fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	}
	printf("\n");
	if(total >1){
	printf("\n Valor arrecadado pela empresa: R$ %d \n",total);
}else{
	printf("\n Valor arrecadado pela empresa: 0");
}
}else{
	printf("\n Valor arrecadado pela empresa: NÃO HÁ ARQUIVO");
}
	fclose(arquivo_cliente);
	printf("\n");
	linha();
	printf("\n \nTecle ENTER para voltar ao menu...");
	getche();

}

void mostre(int pos){
	fseek(arquivo_cliente, pos*sizeof(registro_cliente),SEEK_SET);
	fread(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
	printf("\n \n");
	linha();
	printf("\n Nome      RG     sexo idade pacote quantidade");
	printf("\n %s  %d  %d    %d     %d       %d",cliente.nome,cliente.rg, cliente.sexo, cliente.idade, cliente.pacote,cliente.quantidade);
}

void editar(){
	int rg, conf, resp, posicao,q,continuar=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	if(arquivo_cliente != NULL){
	do{
		arquivo_cliente=fopen("cliente.txt","r+b");
		linha();
		printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
		printf("\n\n Informe o RG para busca:");
		scanf("%d",&rg);
		posicao = procura(rg);
		if (posicao == -1){
			printf("\n não encontrado!!");
		}else{
			mostre(posicao);
			printf("\n\n Editar cliente (1-sim/2-nao) ?");
			scanf("%d",&conf);
			if(conf == 1){
				do{
					system("cls");
				linha();
		printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
		printf("\n\n Informe o RG para busca:");
		mostre(posicao);
		printf("\n\n Editar cliente (1-sim/2-nao) ?");		
				printf("\n Editar nome - 1");
				printf("\n Editar sexo - 2");
				printf("\n Editar idade - 3");
				printf("\n Editar pacote - 4");
				printf("\n Editar quantidade de pontos - 5");
				printf("\n Opção:");
				scanf("%d",&q);
				if(q != 1 && q != 2 && q != 3 && q != 4 && q != 5){
					do{
						system("cls");
						linha();
		printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
		printf("\n\n Informe o RG para busca:");
		mostre(posicao);
		printf("\n\n Editar cliente (1-sim/2-nao) ?\n");
		printf("\n Editar nome - 1");
				printf("\n Editar sexo - 2");
				printf("\n Editar idade - 3");
				printf("\n Editar pacote - 4");
				printf("\n Editar quantidade de pontos - 5");
		printf("\n Opção invalida, Digite novamente:");
				scanf("%d",&q);	
					}while(q != 1 && q != 2 && q != 3 && q != 4 && q != 5);
				}
				if(q==1){
					
					printf("\n Digite o novo nome:");
					fflush(stdin);
					gets(cliente.nome);
					fseek(arquivo_cliente,posicao*sizeof(registro_cliente),SEEK_SET);
				fwrite(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
				}else if(q==2){
					printf("\n\n (1-fem/2-mas)");
					printf("\n Digite o novo sexo:");
					scanf("%d",&cliente.sexo);
					if(cliente.sexo != 1 && cliente.sexo != 2){
						do{
							system("cls");
						linha();
						printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
		printf("\n\n Informe o RG para busca:");
		mostre(posicao);
		printf("\n\n Editar cliente (1-sim/2-nao) ?\n");
		printf("\n Editar nome - 1");
				printf("\n Editar sexo - 2");
				printf("\n Editar idade - 3");
				printf("\n Editar pacote - 4");
				printf("\n Editar quantidade de pontos - 5");
				printf("\n\n (1-fem/2-mas)");
				printf("\n Opção invalida, Digite novamente:");
				scanf("%d",&cliente.sexo);
						}while(cliente.sexo != 1 && cliente.sexo != 2);
					}
				fseek(arquivo_cliente,posicao*sizeof(registro_cliente),SEEK_SET);
				fwrite(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
				
				
				}else if(q==3){
					printf("\n Digite a nova idade:");
					scanf("%d",&cliente.idade);
					if(cliente.idade<18){
						do{
						system("cls");
						linha();
						printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
		printf("\n\n Informe o RG para busca:");
		mostre(posicao);
		printf("\n\n Editar cliente (1-sim/2-nao) ?\n");
		printf("\n Editar nome - 1");
				printf("\n Editar sexo - 2");
				printf("\n Editar idade - 3");
				printf("\n Editar pacote - 4");
				printf("\n Editar quantidade de pontos - 5");
				printf("\n\n Não é possivel clientes abaixo de 18 anos. \n\n Informe novamente:");
				scanf("%d",&cliente.idade);
						}while(cliente.idade <18);
					}
				fseek(arquivo_cliente,posicao*sizeof(registro_cliente),SEEK_SET);
				fwrite(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
				
				
				}else if(q==4){
				printf("\n Pacote(1-Premium/2-Ouro/3-Standard)");
				printf("\n Novo pacote:");
				scanf("%d",&cliente.pacote);
				if(cliente.pacote != 1 && cliente.pacote !=2 && cliente.pacote !=3){
					do{
						system("cls");
						linha();
		printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
		printf("\n\n Informe o RG para busca:\n");
		mostre(posicao);
		printf("\n\n Editar cliente (1-sim/2-nao) ?\n");
		printf("\n Editar nome - 1");
				printf("\n Editar sexo - 2");
				printf("\n Editar idade - 3");
				printf("\n Editar pacote - 4");
				printf("\n Editar quantidade de pontos - 5");
				printf("\n\n Pacote(1-Premium/2-Ouro/3-Standard)");
				printf("\n Opção invalida, Digite novamente:");
				scanf("%d",&cliente.pacote);
					}while(cliente.pacote != 1 && cliente.pacote != 2 && cliente.pacote != 3 );
				}
				fseek(arquivo_cliente,posicao*sizeof(registro_cliente),SEEK_SET);
				fwrite(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
				printf("\n ");
			}else if(q ==5){
				printf("\n Nova quantidade de pontos:");
				scanf("%d",&cliente.quantidade);
				fseek(arquivo_cliente,posicao*sizeof(registro_cliente),SEEK_SET);
				fwrite(&cliente,sizeof(registro_cliente),1,arquivo_cliente);
				printf("\n ");
			}
			printf("\n \n Cliente editado com sucesso !");
			printf("\n Deseja continuar editando o mesmo cliente (1-sim/2-não) ?");
			scanf("%d",&continuar);
		}while(continuar == 1);
			}else{
				printf("\n operação cancelada \n\n");
			}
		
		}
		printf("\n\n deseja editar outro (1-sim/2-não) ?");
		scanf("%d",&resp);
		fclose(arquivo_cliente);
		system("cls");
	}while(resp == 1);
}else{
	linha();
		printf("\n                      Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                              Editar Cliente");
	printf("\n\n\n NÃO HÁ ARQUIVOS\n");
	linha();
	printf("\n\n Precione ENTER para voltar ao menu...");
	getche();
}
}

void remover(){
	int rg, conf, resp, posicao,i;
	cliente_nulo.rg=0;
	cliente_nulo.sexo=0;
	cliente_nulo.idade=0;
	arquivo_cliente=fopen("cliente.txt","r+b");
	
	if(arquivo_cliente != NULL){
	do{
		system("cls");
		linha();
	printf("\n                       Empresa de TV/Telefonia/Internet\n");
	linha();
	printf("\n                               Remover Cliente");
		printf("\n Informe o RG para busca:");
		scanf("%d",&rg);
		posicao = procura(rg);
		if(posicao == -1){
			printf("\n cliente não encontrado");
		}else {
			mostre(posicao);
			printf("\n\n Deseja remover o cliente (1-sim/2-não) ?");
			scanf("%d",&conf);
			if(conf == 1){
				fseek(arquivo_cliente,posicao*sizeof(registro_cliente),SEEK_SET);
				fwrite(&cliente_nulo,sizeof(registro_cliente),1,arquivo_cliente);
				printf("\n\n Cliente removido com sucesso!");
			}else{
				printf("\n\n Remoção cancelada!");
			}	
		}
		printf("\n\n\n Deseja remover outro (1-sim/2-não)?");
		scanf("%d",&resp);
		
	}while(resp == 1);
	fclose(arquivo_cliente);
	}else {
		linha();
		printf("\n                       Empresa de TV/Telefonia/Internet\n");
		linha();
		printf("\n                               Remover Cliente");
		printf("\n\n NÃO EXISTE ARQUIVO CRIADO.");
		printf("\n");
	}
	linha();
	printf("\n \nTecle ENTER para voltar ao menu...");
	getche();
	fclose(arquivo_cliente);
}

void pacote1(){
	linha();
	printf("\n                      Empresa de TV/Telefonia/Internet\n");
	linha();
	printf("\n                             Listagem por pacote");
	printf("\n \n                                 PACOTE 1\n");
	int i;
	arquivo_cliente=fopen("cliente.txt","r+b");
	rewind(arquivo_cliente);

	if(arquivo_cliente != NULL){
	printf("\n    Nome      idade    sexo       pacote  pontos\n");
	linha();
	fread(&cliente,sizeof(cliente),1,arquivo_cliente);
	
	while(feof(arquivo_cliente)==0){
		if(cliente.pacote == 1 ){
			printf("\n  %s   %d        %d           %d      %d ", cliente.nome,cliente.idade,cliente.sexo,cliente.pacote, cliente.quantidade);
		}
		fread(&cliente,sizeof(cliente),1,arquivo_cliente);
	}
	

	
}else{
	printf("\n\n NÃO EXISTEM DADOS.");
}
	printf("\n");
	linha();
	printf("\n \nTecle ENTER para proxima pagina...");
	getche();
	system("cls");
}

void pacote2(){
	linha();
	printf("\n                      Empresa de TV/Telefonia/Internet\n");
	linha();
printf("\n                             Listagem por pacote");
printf("\n \n                                 PACOTE 2\n");

	int i;
	arquivo_cliente=fopen("cliente.txt","r+b");
	rewind(arquivo_cliente);

	if(arquivo_cliente != NULL){
	printf("\n    Nome      idade    sexo       pacote  pontos\n");
	linha();
	fread(&cliente,sizeof(cliente),1,arquivo_cliente);
	
	while(feof(arquivo_cliente)==0){
		if(cliente.pacote == 2 ){
			printf("\n  %s           %d        %d           %d        %d", cliente.nome,cliente.idade,cliente.sexo,cliente.pacote,cliente.quantidade);
		}
		fread(&cliente,sizeof(cliente),1,arquivo_cliente);
	}
	

	
}else{
	printf("\n\n NÃO EXISTEM DADOS.");
}
	printf("\n");
	linha();
	printf("\n \nTecle ENTER para proxima pagina...");
	getche();
	system("cls");
	
}

void pacote3(){
	linha();
	printf("\n                      Empresa de TV/Telefonia/Internet\n");
	linha();
	printf("\n                             Listagem por pacote");
	printf("\n \n                                 PACOTE 3\n");
	int i;
	arquivo_cliente=fopen("cliente.txt","r+b");
	rewind(arquivo_cliente);

	if(arquivo_cliente != NULL){
	printf("\n    Nome      idade    sexo       pacote  pontos\n");
	linha();
	fread(&cliente,sizeof(cliente),1,arquivo_cliente);
	
	while(feof(arquivo_cliente)==0){
		if(cliente.pacote == 3 ){
			printf("\n  %s          %d        %d           %d      %d", cliente.nome,cliente.idade,cliente.sexo,cliente.pacote,cliente.quantidade);
		}
		fread(&cliente,sizeof(cliente),1,arquivo_cliente);
	}
	

	
}else{
	printf("\n\n NÃO EXISTEM DADOS.");
}
	printf("\n");
	linha();
	printf("\n \nTecle ENTER para voltar ao menu...");
	getche();
	system("cls");
	
}

main (){
	int op;
	do{
	menu ();
	scanf("%d",&op);
	system("cls");
	
	if((op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op!= 6 && op !=0)){
		do{
		menu();
		printf("\n Opção invalida, Digite novamente:");
		scanf("%d",&op);
		}while((op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op!= 6 && op !=0));
	}
	
	if ( op == 1){
	cadastrar();
	}else if ( op == 2){
	listagem();
}else if (op == 3){
	relatorio1();relatorio2();relatorio3();relatorio4();relatorio5();
}else if ( op == 4){
	editar();
}else if (op ==5 ){
	remover();
}else if(op == 6){
	pacote1();pacote2();pacote3();
}		
}while((op == 1 || op == 2 || op == 3 || op == 4 || op == 5 || op== 6));
}
