#include <stdio.h>
#include <stdlib.h>

float **matriz(unsigned long int num_lin, unsigned long int num_col){
	unsigned long int lin;
	float **vect;

	vect=(float **)malloc(num_lin*sizeof(float *));
	if (vect==NULL){
		printf("###Memoria Insuficiente###\n");
		return NULL;
	}
	for(lin=0;lin<num_lin;lin++){
		vect[lin]=(float *)malloc(num_col*sizeof(float));
		if (vect[lin]==NULL){
			printf("\n###Memoria_Insuficiente###\n\n");
			for(lin--;lin>0;lin--){
				free(vect[lin]);
			}
			free(vect[0]);
			free(vect);
			return NULL;
		}
	}
	return vect;
}

void sum_line(float ** vect,unsigned long int pos_1,unsigned long int pos_2,unsigned long int max,float coef,int mode){
	unsigned long int i;

	for(i=0;i<max;i++){
		if(mode==1){
			vect[pos_1][i]+=(coef*vect[pos_2][i]);
		}else if(mode==2){
			vect[i][pos_1]+=(coef*vect[i][pos_2]);
		}
	}
}

double calc_det(float **vect,unsigned long int max){
	unsigned long int lin,col,i;
	float **calc;
	double det;
	int check_lin,check_col;

	for(lin=0;lin<max;lin++){
		check_col=0;
		check_lin=0;
		for (col=0;col<max;col++){
			if(vect[lin][col]!=0){
				check_lin=1;
			}
			if(vect[col][lin]){
				check_col=1;
			}
		}
		if(check_lin==0){
			printf(">Linha nula\n");
			return 0;
		}
		if(check_col==0){
			printf(">Coluna nula\n");
			return 0;
		}
	}

	calc=matriz(max,max);
	
	if(calc==NULL){
		return 0;
	}

	for(col=0;col<max;col++){
		for(lin=0;lin<max;lin++){
			calc[lin][col]=vect[lin][col];
		}
	}

	for(i=0;i<max;i++){
		if(calc[i][i]==0){
			for(lin=0;lin<max;lin++){
				if(vect[i][lin]!=0){
					sum_line(calc,i,lin,max,1,2);
				}else if(vect[lin][i]!=0){
					sum_line(calc,i,lin,max,1,1);
				}
			}
		}
	}

	for(i=0;i<max;i++){
		if(calc[i][i]==0){
			for(lin=i+1;lin<max;lin++){
				if(vect[i][lin]!=0){
					sum_line(calc,i,lin,max,1,2);
				}else if(vect[lin][i]!=0){
					sum_line(calc,i,lin,max,1,1);
				}
			}
		}
		for(lin=i+1;lin<max;lin++){
			sum_line(calc,lin,i,max,-(calc[lin][i]/calc[i][i]),1);
		}
	}

	det=1;
	for(i=0;i<max;i++){
		det*=calc[i][i];
	}

	for(lin=0;lin<max;lin++){
		free(calc[lin]);
	}
	free(calc);
	return det;
}


unsigned long int ask_num(char str[],unsigned long int limit, int mode){
	unsigned long int num;
	int i;
	i=1;
	while(i){
		printf("%s\n",str);
		if(mode==1){
			printf("Max:%lu\n",limit-1);
		}else if(mode==2){
			printf("Min:%lu\n",limit-1);
		}
		scanf("%lu",&num);
		while(getchar()!='\n'){}
		if(num<limit&&mode==1){
			i=0;
		}else if(num>limit&&mode==-1){
			i=0;
		}else{
			printf("###Numero Invalido###\n");
		}
	}
	return num;
}

int main(){
	unsigned long int lin,col,num_lin,num_col;
	float **vect=NULL;
	double sum,det;
	char ask[4];
	ask[0]='~';
	lin=0;
	col=0;
	while(ask[0]!='0'){
		printf("Criar matriz?\n");
		printf("(1)Sim   (0)Nao\n");	
		fgets(ask,3,stdin);
		if(ask[0]=='1'){
			num_lin=ask_num("Quantidade de linhas:",0,-1);
			num_col=ask_num("Quantidade de colunas:",0,-1);
			vect=matriz(num_lin,num_col);
		}else if(ask[0]!='0'){
			printf("###Comando Invalido###\n");
		}
		while(vect!=NULL){
			printf("O que fazer:\n\n");
			printf("(1)Consultar valor   |   (2)Alterar valor    |   (3)Determinante\n");
			printf("(4)Soma de linha     |   (5)Soma de coluna   |\n");
			printf("(6)Imprimir matriz   |   (7)Excluir matriz   |\n");
			fgets(ask,3,stdin);
			if(ask[0]=='1'){
				lin=ask_num("Linha:",num_lin,1);
				col=ask_num("Coluna:",num_col,1);
				printf("%f\n",vect[lin][col]);
			}else if(ask[0]=='2'){
				lin=ask_num("Linha:",num_lin,1);
				col=ask_num("Coluna:",num_col,1);
				printf("Valor atual de (%lu,%lu):\n",lin,col);
				printf("%f\n",vect[lin][col]);
				printf("Novo valor de (%lu,%lu):\n",lin,col);
				scanf("%f",&(vect[lin][col]));
				while(getchar()!='\n'){}
			}else if(ask[0]=='3'){
				if(num_lin==num_col){
					det=calc_det(vect,num_lin);
					printf("O determinante eh %.5lf\n",det);
				}else{
					printf("###Matriz nao eh quadrada###\n");
				}
			}else if(ask[0]=='4'){
				lin=ask_num("Linha:",num_lin,1);
				sum=0;
				for(col=0;col<num_col;col++){
					sum+=vect[lin][col];
				}
				printf("A soma da linha %lu é:\n",lin);
				printf("%.5lf\n",sum);
			}else if(ask[0]=='5'){
				col=ask_num("Coluna:",num_col,1);
				sum=0;
				for(lin=0;lin<num_lin;lin++){
					sum+=vect[lin][col];
				}
				printf("A soma da coluna %lu é:\n",col);
				printf("%.5lf\n",sum);
			}else if(ask[0]=='6'){
				for(lin=0;lin<num_lin;lin++){
					for(col=0;col<num_col;col++){
						printf("%.2f   ",vect[lin][col]);
					}
					printf("\n");
				}
			}else if(ask[0]=='7'){
				for(lin=0;lin<num_lin;lin++){
					free(vect[lin]);
				}
				free(vect);
				vect=NULL;
			}else{
				printf("###Comando Invalido###\n");
			}
		}
	}
}