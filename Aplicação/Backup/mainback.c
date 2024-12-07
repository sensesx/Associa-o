			// Aplicação para associação de moradores de Mauá
// Trabalho realizado sozinho
// Github:
// Objetivo:
// Desenvolvido para sistemas Linux
// Consultar README para mais informações

// Funcionalidades
// 2. Consultas online para informações específicas 
// 3. API para monitorar atividades

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include "external.h"

#define ERR -1
#define EXIT -2

FILE *fp;
FILE *memberFp;

struct dirent *dirp;

char commandBuffer[2048];
char option[3];
char lines[256];
char *USER;
char *prompt = "$";
char *userCommand;
char *k = "[+]";
char *n = "[-]";
char *o = "[!]";
char *a = "[*]";
char *mainpwd;
char *memberPwd;
char *commandReader(void);

int commandParser(char *command);
int info();

int main(int argc, char *argv[]){
	
	// Horário

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if(mainpwd == NULL){
		mainpwd = getenv("PWD");
		strcat(mainpwd, "/");
	}

	int pwdLen = strlen(mainpwd);
	if(argc < 2){
		USER = getenv("USER");
		system("clear");	
		while(true){
			printf("\n");
			printf("====================================================================\n");
			printf("=========== ASSOCIAÇÃO DE MORADORES \033[1;35mPARQUE SÃO VICENTE \033[0;0m=============\n");
			printf("====================================================================\n");
		
			printf("\nDia: %2d/%2d/%d \n", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900);
			printf("Horário: %d:%d \n", tm.tm_hour, tm.tm_min);

			printf("\n\n%s Este programa tem como objetivo auxiliar administrativemente os responsáveis por organizar a associação de moradores do Parque São Vicente.\n", o);

			printf("\nDigite o número da opção desejada ou digite 5 para consultar o manual: ");
			printf("\n\n1. Painel Administrativo\n2. Informações e dúvidas sobre o programa\n3. Sair\n\nR:"); 
			if(!fgets(option, sizeof(option), stdin)){ 
				printf("%s %s", n, strerror(errno)); 
				return EXIT_FAILURE;
			}
			
			if(option[strlen(option) - 1] != '\n'){
				streamCleaner();
				printf("\n Digite apenas um número, por gentileza.");
				continue;
			}
			switch(atoi(option)){
				case 1:
					if(atoi(option) == 1){
						system("clear");
						printf("===================================================================\n");
						printf("==================== Painel Administrativo ========================\n");
						printf("===================================================================\n");
						printf("\nDia: %d/%d/%d", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900);
						printf("\nHorário: %d:%d", tm.tm_hour, tm.tm_min);				
						printf("\n\n%s Este é o painel administrativo, selecione uma função digitando o número da mesma:", o);
						printf("\n\n1. Adicionar Membro");
						printf("\n2. Remover Membro");
						printf("\n3. Atualizar informações do membro");
						printf("\n4. Atualizar informações da associação");
						printf("\n5. Listar todos os membros");
						printf("\n6. Voltar ao menu principal\n\n");
						while(true){ 
							printf("\033[1;31m[Painel Associação] \033[0;32m- \033[1;35m%s: \033[1;0m%s ", USER, prompt);
							fgets(commandBuffer, sizeof(commandBuffer), stdin);
							commandParser(commandBuffer);
						}
					}
					break;
				case 2:
					info();
					break;
				case 3:
					printf("\nAté mais =D\n\n");
					return EXIT_SUCCESS;
				default:
					printf("\n\n%sOpção invalida.\n", n);
					getchar();
			}
		} 
	}else{ 
		printf("\nO programa não aceita argumentos. Digite apenas o nome do programa =D.\n");
		return EXIT_SUCCESS;
	}

} 


int info(){
	int ch;
	char infoAns[3];
	system("clear");
	printf("===================================================================\n");
	printf("================== Painel de informações gerais ===================\n");
	printf("===================================================================\n");

	printf("\n1. Utilidade do programa");
	printf("\n2. Membros da associação");
	printf("\n3. Localização da associação");
	printf("\n4. Como adicionar e remover membros");
	printf("\n5. Como comunicar membros");
	printf("\n6. Desejo facilitar ou sugerir alguma mudança no programa para facilitar a administração.\n\nR: ");
	if(!fgets(infoAns, sizeof(infoAns), stdin)){
		printf("Erro: %s", strerror(errno));
	}
	if(infoAns[strlen(infoAns) - 1] != '\n'){
		streamCleaner();
		printf("\nDigite apenas um número, por favor.\n");
	}
	switch(atoi(infoAns)){
		case 1:
			printf("\n\nPara que a tarefa de organizar os diversos aspectos da associação, essa ferramenta foi criada para que os responsáveis possam ministrar de forma eficiente a organização. Existem funcionalidades que facilitam o processo de gerenciar os membros e atividades gerais da AMPV.");
			printf("\n\nPressione uma tecla para continuar...");
			getchar();
			break;
		case 2:
			if(memberPwd == NULL){
				memberPwd = getenv("PWD");
				strcat(memberPwd, "members/members.csv");
			}
			memberFp = fopen(memberPwd, "r");
			while(fgets(lines, sizeof(lines), memberFp)){
				printf("%s", lines);
			}
			break;
		case 3:
			printf("\nRua Armando Sales de Oliveira, 554 - Parque. São Vicente , Mauá, SP, Brazil");
			printf("\n\nPressione uma tecla para continuar...");
			getchar();
			system("clear");
			break;
		case 4: 
			printf("\nPara administrar as informações dos membros da associação, selecione a opção de Painel Administrativo ao iniciar o programa. Utilizando o painel\n\nDigite manual caso haja alguma dúvida ao utilizar o painel.");
			printf("\n\nPressione uma tecla para continuar...");
			getchar();
			system("clear");
			break;
		case 5:
			printf("\nPara comunicar os membros sobre qualquer eventualidade, utilize a opção de enviar email ao iniciar o programa. \n\nDigite manual caso haja alguma dúvida.\n ");
			printf("\n\nPressione uma tecla para continuar...");
			getchar();
			system("clear");
			break;
		case 6:
			printf("\nCaso surja a necessidade de implementar uma funcionalidade no programa, solucionar erros ou sugerir sugestões, envie um email para \"corp_vini@outlook.com\"");
			printf("\n\nPressione uma tecla para continuar...");
			getchar();
			system("clear");
			break;
		default:
			printf("Opção inválida. ");
	}
	

	return 0;
}
			FILE *delFpFile;
			FILE *tempDel;
int commandParser(char *command){
	int lineDigitDel = 0;
	int delCountFunc = 0;


	command[strcspn(command, "\n")] = 0;

	if(strcmp(command, "1") == 0){
		addMember();
	}else if(strcmp(command, "2") == 0){
		delMember();
	}else if(strcmp(command, "3") == 0){
		updateMember();
	}else if(strcmp(command, "6") == 0){
		return EXIT;
	}else{
		printf("%s", command);
		printf("Opção inválida. Digite 9 para consultar todas as funções disponíveis");
	}
	return 0;
}


	char *commandReader(void){ 

char *commandPtr = NULL; 
int commandBufferLen;
	
	printf("\033[1;31m[Painel Associação] \033[0;32m- \033[1;35m%s: \033[1;0m%s ", USER, prompt);
	fgets(commandBuffer, sizeof(commandBuffer), stdin);
	commandPtr = commandBuffer;
	
	return commandPtr;	
}
