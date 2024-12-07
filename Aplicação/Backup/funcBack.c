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
FILE *temp;

char *memberFile;
char line[10000];
char delLine[10000];
char fileLine[10000];
char *funcPwd = NULL;
int lineCount = 0;
int ch = 0;
bool funcDec = false;

char *lineDigit;
char lineStr[100000];
char *lineStrnum = lineStr;




char* getPwd(){
	if(funcPwd== NULL){
		funcPwd = getenv("PWD");
		memberFile = funcPwd;
		strcat(funcPwd, "members/members.csv");
	}
	return funcPwd;
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


int delMember(){
	FILE *tempFile;
	int delLineCount = 0;
	int delDigit = 0;
	int delCount = 0;
	char delAnswer[256];
	int remover = 0;
	char deloption[5];
	char dellLine[256];
	

	printf("Verifique todos os membros e informe o número do que deseja excluir: ");
	listMember();
	printf("\nR:");
	fgets(delAnswer, sizeof(delAnswer), stdin);
	rewind(funcFp);
	funcFp = fopen(memberFile, "r");
	while(fgets(dellLine, sizeof(dellLine), funcFp)){
		delCount++;
		if(delCount == atoi(delAnswer)){
			printf("Você deseja excluir este membro? Digite 1 para sim e 0 para não\n\n%s", dellLine);
			fgets(deloption, sizeof(deloption), stdin);
			switch(atoi(deloption)){
				case 1:
					remover = 1;
					fclose(funcFp);
					break;
				case 0:
					printf("\n\nFechando...");
					fclose(funcFp);
					return 0;
					break;
				default:
					printf("Opção inválida.");
					return -1;
					break;

			}
			break;
		}
	}
	if(remover == 1){
		printf("ola amigo");
		FILE *removerFp;
		removerFp = fopen(memberFile, "r");
		tempFile = fopen("tempMember.txt", "w");
		while(fgets(line, sizeof(line), funcFp)){
			delLineCount++;
			if(delLineCount == atoi(delAnswer)){
				continue;
			}
			fputs(line, tempFile);
	}
	fclose(removerFp);
	fclose(tempFile);
	removerFp = fopen(memberFile, "w");
	tempFile = fopen("tempMember.txt", "r");
	while(fgets(line, sizeof(line), tempFile)){
		fputs(line, removerFp);
	}
	remove("tempMember.txt");
	fclose(removerFp);
	fclose(tempFile);
}
}

void listMember(){	
	printf("\n");
	getPwd();
	int count = 1;
	int element;
	char *tokCpf, *token;
	char *nameTok;
	char *cpfTok;

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
