#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include <time.h>
#include <ctype.h>

	struct estoque{
		int cod;
		char modo;
		double qtd_estoque;
		double preco_unit;
		double lucro;
	};

	struct vendas{
		int ano;
		int mes;
		int dia;
		int cod_p;
		double qtd_vendida;
		double preco_venda;
		const char *uf;
		int icms;
	};

struct imposto{
	const char *uf;
	int icms;
};
	int carregar_dias (int Mes);
	int carregar_estoque();
	int DiaSemana(int dd, int mm, int aa);
	int carregar_struct_imposto();
	
	
	int NDiasMes, Mes;
	int Ano, cont;
	
	imposto v_estados[27];

	estoque *produto;
	int TamProduto;
	int QtdeVendasDia;

int main (){
	int i,p;
	int dia;
	printf ("Inicio das vendas-> ../....\nDigite o mes das vendas:  ");
	scanf("%d",&Mes);
	while (Mes > 12){
		printf ("\nDigite um mes valido:  ");
		scanf("%d",&Mes);
	}
	system("cls");
	printf ("Inicio das vendas-> %02d/....\nDigite o ano das vendas:  ",Mes);
	scanf("%d",&Ano);
	while (Ano<2016 || Ano>9999){
		printf ("\nOBS: ano minimo 2016");
		printf ("\nDigite um ano valido:  ");
		scanf("%d",&Ano);
	}
	system("cls");
	printf ("Inicio das vendas-> %02d/%04d\n",Mes,Ano);
	
	printf ("\n\nDigite a quantidade diaria de lancamentos de vendas:  ");
	scanf("%d",&QtdeVendasDia);
	while (QtdeVendasDia>3 || QtdeVendasDia<=0){
		printf ("\n\nDigite uma quantidade valida entre 1 e 3:  ");
	scanf("%d",&QtdeVendasDia);
	}
	
	printf("\n");
	
	carregar_dias (Mes);
	
	carregar_estoque();
	/*printf("\n\t  ESTOQUE");
	printf("\n===================================\n");
    for(i = 0; i < TamProduto; i++) {
		printf("%d ",produto[i].cod);
		printf("%c ",produto[i].modo);
		printf("%.3lf ",produto[i].qtd_estoque);
		printf("%.2lf ",produto[i].preco_unit);
		printf("%.2lf \n",produto[i].lucro);
	}	
*/
//	system("pause");
	system("cls");
	
	int total_vendas, y=1,w=0;
	int rand_prod,r;

	total_vendas= NDiasMes*QtdeVendasDia;
	int menos_dom, dom;
	srand((unsigned)time(NULL));
	
	vendas *v_vendas;
	v_vendas = NULL;
	v_vendas = (vendas *)realloc(v_vendas, sizeof (vendas) * total_vendas);
	
	// arquivo de saida
	FILE *arq_vendas;
	arq_vendas = fopen("vendas.txt","a");


	// percorrer todos os dias do mes
	w=0;
	menos_dom=1;
	for (dia = 1; dia <= NDiasMes; dia++){
		for (y = 0; y < QtdeVendasDia; y++){
			dom = DiaSemana(dia, Mes, Ano);
			if (dom==0){
				menos_dom++;
			}
			
			else{
				v_vendas[w].dia = dia;
				w++;
			}
	   }
	}
	
	total_vendas=total_vendas-menos_dom;
	
	v_vendas = (vendas *)realloc(v_vendas, sizeof (vendas) * total_vendas);
	
	carregar_struct_imposto();
	int rand_imposto;
	//sortear os produtos do estoque e a qtd
	for ( r = 0; r < total_vendas; r++){

		v_vendas[r].ano = Ano;
		v_vendas[r].mes = Mes;
		// rand algum icms
		rand_imposto = rand () % 27;
		v_vendas[r].icms = v_estados[rand_imposto].icms;
		v_vendas[r].uf = v_estados[rand_imposto].uf;
		// randomiza o ind de algum prod
		rand_prod = rand () % TamProduto;
		v_vendas[r].cod_p = produto[rand_prod].cod;
		
		if (produto[rand_prod].modo == 'U'){
			v_vendas[r].qtd_vendida = 1 + rand()/40;
		}else 
			v_vendas[r].qtd_vendida = 100 + rand()/100.000;
		v_vendas[r].preco_venda = produto[rand_prod].preco_unit * (1 + produto[rand_prod].lucro/100);
	}
	

	
	double aux_lucro;
	int t_porc = total_vendas * 0.35;
	srand(time(NULL));
	for (int x = 0; x < t_porc; x++){
		w = rand () % total_vendas;
		//rand i do prod
		//rand o lucro
	//	printf("\n VALOR ANTES %.2lf",v_vendas[w].preco_venda);
		aux_lucro =(1+ rand() % 16-8)/100.00;
		while (aux_lucro == 0.00){
			aux_lucro =(1+ rand() % 16-8)/100.00;
		}
	//	printf("\n MUDANCA %.2lf %d",aux_lucro,w);	
		
			v_vendas[w].preco_venda = v_vendas[w].preco_venda + (v_vendas[w].preco_venda * aux_lucro);
		
		
		
	//	printf("\n VALOR DEPOIS %.2lf",v_vendas[w].preco_venda);
	}

	
	
	
	// loop para fazer a leitura de todas as vendas
	for ( r = 0; r<total_vendas;r++){
		fprintf(arq_vendas,"%d;",v_vendas[r].ano);
		fprintf(arq_vendas,"%02d;",v_vendas[r].mes);
		fprintf(arq_vendas,"%02d;",v_vendas[r].dia);
		fprintf(arq_vendas,"%d;",v_vendas[r].cod_p);
		fprintf(arq_vendas,"%.3lf;",v_vendas[r].qtd_vendida);
		fprintf(arq_vendas,"%.2lf;",v_vendas[r].preco_venda);
		fprintf(arq_vendas,"%s;",v_vendas[r].uf);
		fprintf(arq_vendas,"%d%%\n",v_vendas[r].icms);
		
	/*	printf("%d;",v_vendas[r].ano);
		printf("%02d;",v_vendas[r].mes);
		printf("%02d;",v_vendas[r].dia);
		printf("%d;",v_vendas[r].cod_p);
		printf("%.3lf;",v_vendas[r].qtd_vendida);
		printf("%.2lf;",v_vendas[r].preco_venda);	
	    printf("%s;",v_vendas[r].uf);
		printf("%d%%\n",v_vendas[r].icms);                      
	*/
	}
	r=0;

	
	printf("\n\nAs %d vendas foram cadastradas com sucesso!\n\n",total_vendas);
	fclose(arq_vendas);


	return 0;

}


int carregar_dias (int Mes){
		if (Mes == 1){
			NDiasMes = 31;
		}
		if (Mes == 2){
			NDiasMes = 28;
		}
		if (Mes == 3){
			NDiasMes = 31;
		}
		if (Mes == 4){
			NDiasMes = 30;
		}
		if (Mes == 5){
			NDiasMes = 31;
		}
		if (Mes == 6){
			NDiasMes = 30;
		}
		if (Mes == 7){
			NDiasMes = 31;
		}
		if (Mes == 8){
			NDiasMes = 31;
		}
		if (Mes == 9){
			NDiasMes = 30;
		}
		if (Mes == 10){
			NDiasMes = 31;
		}
		if (Mes == 11){
			NDiasMes = 30;
		}
		if (Mes == 12){
			NDiasMes = 31;
		}

	return (NDiasMes);
}


int DiaSemana(int dd, int mm, int aa) {
 time_t hora;
 struct tm *phora;
 time(&hora);
 phora = localtime(&hora);
 phora->tm_year = aa - 1900;
 phora->tm_mon = mm - 1;
 phora->tm_mday = dd;
 mktime(phora);
 return phora->tm_wday;
 //. Ela retorna 0 para Domingo, 1 para segunda-feira, 2 para
//terça-feira e assim por diante
}

int carregar_struct_imposto(){

	v_estados[0].uf = "AM";
	v_estados[0].icms = 0;
	
	v_estados[1].uf= "RO" ;
	v_estados[1].icms = 0;
	
	v_estados[2].uf="RR";
	v_estados[2].icms = 0;
	
	v_estados[3].uf="SP" ;
	v_estados[0].icms = 18;
	
	for (int x=4;x<10;x++){
		v_estados[x].icms = 12;
	}
	v_estados[4].uf="ES" - 12;
	v_estados[5].uf= "MG" - 12; 
	v_estados[6].uf= "RJ" - 12;
	v_estados[7].uf="PR" - 12;
	v_estados[8].uf="SC" - 12;
	v_estados[9].uf="RS" - 12;
	
	for(int x=10; x<27 ; x++){
		v_estados[x].icms = 7;
	}
	v_estados[10].uf="AC" ;
	v_estados[11].uf="AL" ;
	v_estados[12].uf="AP" ;
	v_estados[13].uf="BA"; 
	v_estados[14].uf="CE";
	v_estados[15].uf= "DF";   
	v_estados[16].uf= "GO"; 
	v_estados[17].uf= "MA"; 
	v_estados[18].uf= "MT";
	v_estados[19].uf= "MS"; 
	v_estados[20].uf= "PA";
	v_estados[21].uf= "PB"; 
	v_estados[22].uf= "PE"; 
	v_estados[23].uf=  "PI"; 
	v_estados[24].uf= "RN";
	v_estados[25].uf= "SE";
	v_estados[26].uf= "TO";
	return 1;
}

int carregar_estoque(){
	FILE *arq_produtos;
	estoque aux;
	
	arq_produtos = fopen("produtos.txt","r");
	
	if(arq_produtos == NULL){
		printf("\nNão foi possivel abrir o arquivo\n");
		return 0;
	}
	
	system("cls");
	produto = NULL;
	TamProduto = 0;
	while(fscanf(arq_produtos,"%d;%c;%lf;%lf;%lf\n", &aux.cod, &aux.modo, &aux.qtd_estoque, &aux.preco_unit, &aux.lucro) != EOF) {
		
	
		TamProduto++;
		produto = (estoque *)realloc(produto, sizeof (estoque) * TamProduto);
		produto[TamProduto-1] = aux;
	} 

	fclose(arq_produtos);
	return 1;
}

