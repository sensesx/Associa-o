#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <regex.h>
#include <ctype.h>
#include "external.h"

char name[64];
char cpf[13]; 
char email[64];
FILE *funcFp;
char *memberFile;
char line[528];
char delLine[528];
char fileLine[256];
char *funcPwd = NULL;
int lineCount = 0;
int ch = 0;

char *lineDigit;
char lineStr[256];
char *lineStrnum = lineStr;


void getPwd(){
	if(funcPwd== NULL){
		funcPwd = getenv("PWD");
		memberFile = funcPwd;
		strcat(funcPwd, "members/members.csv");
	}
}

char * getFileLine(){
	while(fgets(fileLine, sizeof(fileLine), funcFp)){
		lineCount++;
	}
	sprintf(lineStr, "%d", lineCount);
	return lineStrnum;
}

void addMember(){
	getPwd();
	system("clear");
	char *digit;

	while(true){
		bool nonCharPresent = false;
		printf("Informe o nome do membro a ser integrado: ");
		if(!fgets(name, sizeof(name), stdin)){
			printf("%s", strerror(errno));
		}
		name[0] = toupper(name[0]);
		for(int i = 0; i < strlen(name) - 1; i++){
			if(isalpha(name[i]) == 0){
				printf("\n[-] Apenas letras, por favor.\n\n");
				nonCharPresent = true;
				break;
			}
		}
		if((name[strlen(name)] != 0)){
			while(((ch = getchar() != '\n') && ch != EOF)){
			}
			printf("\n[!] Por favor, digite até 64 letras.\n\n");
			printf("%x", name[strlen(name)]);
			continue;
		}
		if(nonCharPresent == false){
				break;
			}
	}

	while(true){
		bool nonDigitPresent = false;
		printf("\nInforme o CPF do membro: ");
		if(!fgets(cpf, sizeof(cpf), stdin)){
			printf("%s", strerror(errno));

		}
		cpf[strcspn(cpf, "\n")] = 0;
		if(strlen(cpf) != 11){
			printf("\n[-] CPF precisa ter 11 digitos.\n\n");
			printf("Pressione enter para continuar...");
			if((cpf[strlen(cpf) - 1] != '\n')){
				while(((ch = getchar() != '\n') && ch != EOF)){
				}
				continue;
			}
		
		}
		for(int i = 0; i < strlen(cpf); i++){
			if(!isdigit(cpf[i])){
				printf("\n\n[!] Apenas números, por favor.");
				nonDigitPresent = true;
			}
		}
		if(nonDigitPresent == false){
			break;
		}
	}

	while(true){
		printf("\nInforme o email do membro: ");
		if(!fgets(email, sizeof(email), stdin)){
			printf("%s", strerror(errno));
		}
		break;
	}

	cpf[strcspn(cpf, "\n")] = 0;
	name[strcspn(name, "\n")] = 0;
		strcat(name, ",");
	strcat(name, cpf);
	strcat(name, ",");
	strcat(name, email);
	strcat(line, name); 
	memset(name, '0', strlen(name));
	// Funciona, mas poderia ser melhor implementado. Função insegura.
	funcFp = fopen(memberFile, "a+");

	if(fwrite(line, 1, strlen(line), funcFp)){
		printf("\n[+] Membro adicionado com sucesso.\n\n");
	}else{
		printf("Erro: %s", strerror(errno));
	}
	fclose(funcFp);
	
}

FILE *delFp;

void delMember(){
	int delDigit = 0;
	int lineCount = 0;

	system("clear");
	printf("============== Remoção de membro ==============\n");
	getPwd();
	char deloption[5];
		printf("\nSelecione uma opção digitando seu número: \n\n1. Listar todos os membros registrados\n2. Digitar o nome do integrante a ser removido\n\nr:");
		fgets(deloption, sizeof(deloption), stdin);
		switch(atoi(deloption)){
			case 1:
				printf("\n\nListando todos os membros...\n\n");
				listMember();
				funcFp = fopen(memberFile, "r");
				delDigit = atoi(getFileLine());
				while(true){
					printf("\n\nDigite o número da linha do membro que deseja excluir: ");
					if(!fgets(deloption, sizeof(deloption), stdin)){
						printf("Erro: %s", strerror(errno));
					}
					if(atoi(deloption) > delDigit || atoi(deloption) < 0){
						printf("Por favor, digite um número entre 0 e %d", delDigit);
						continue;
					}
					break;

				}
				rewind(funcFp);
				while(fgets(line, sizeof(line), funcFp)){
					lineCount++;
					if(atoi(deloption) == lineCount){
						printf("\n\nVocê deseja excluir este membro?\n\n%s", line);
					}
				}
				
					break;
				
				fclose(funcFp);
				break;
			case 2:
				printf("Informe o CPF ou nome do membro a ser listado: ");
				break;
			default:
				printf("\n[-] Opção invalida, tente novamente.\n");
		}
	}


void listMember(){	
	printf("\n");
	getPwd();
	int count = 1;
	int element;
	char *tokCpf, *token;
	char *cpfTok;
	char *nameTok;

	funcFp = fopen(memberFile, "r");
	nameTok = strtok(line, ",");
	while(fgets(line, sizeof(line), funcFp)){
		tokCpf = token = strtok(line, ",");
		for(;(tokCpf = strtok(NULL, ",")) != NULL; token = tokCpf){
			if(strlen(token) == 11){
				if(count == 1){
					nameTok = strtok(line, ",");
				}
				cpfTok = token;
				break;
			}
		}
		printf("%d - CPF: %s | Name: %s\n", count++, cpfTok, nameTok);
	}

	fclose(funcFp);
	printf("\n");

}

void updateMember(){
	getPwd();
	char updateOption[3];
	printf("\nSelecione uma opção\n\n1. Listar todos os membros registrados\n2. Digitar o nome do integrante a ser removido\n\nr:");
	fgets(updateOption, sizeof(updateOption), stdin);
	switch(atoi(updateOption)){
		case 1:
			printf("\n\nListando todos os membros...\n");
			listMember();
			break;
		case 2:
			printf("Informe o nome do membro a ser listado: ");
			break;
		default:
			printf("Opção invalida, tente novamente.\n");
	}

}

