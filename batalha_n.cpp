#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<locale.h>


void gotoxy(int x, int y){
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

char nome_jogador1[30],nome_jogador2[30];
int vetorA[64];

void apresentacao();
void barco(void);
void par_impar(int op, int a);
void apresentacao_matriz_coordenadas(int tab_mat1[][8]);
bool verifica(int l_jogador1[],int c_jogador1[]);
void receber_coordenadas(int l_jogador1[],int c_jogador1[],int i);
void exibir_tabgab(int tab_gab1[][8],int tab_gab2[][8],int a);
void adicionar_1_tabgab(int l_jogador1[],int c_jogador1[],int tab_gab1[][8],int tab_gab2[][8],int a);
void exibicao_tabmat(int tab_mat1[][8],int tab_mat2[][8],int a);
void conferencia_coordenadas(int jogada_jogador1_linha,int jogada_jogador1_coluna,int tab_mat1[][8],
                             int tab_mat2[][8],int *contador1_confere,int a);
void efeito(void);
void resultado(int pontos1,int tentativa1,int pontos2,int tentativa2,int *inicio,int *jogador_2);

int main(void)
{
	
	int tab_gab1[8][8],tab_gab2[8][8],tab_mat1[8][8],tab_mat2[8][8],i=0,j=0;
	int l_jogador1[3],c_jogador1[3],inicio=1;		
	int op=0;
	
//-----------------------------------------------------------------------------------------------//
	
	                              //1) Tela de apresentação

//-----------------------------------------------------------------------------------------------//	
	system("Color 0A");
	setlocale(LC_ALL,"Portuguese");
		
	apresentacao();
	getch();			
	system("cls");
//-----------------------------------------------------------------------------------------------//
	
	                        //2) Tela para escolher o jogadores

//-----------------------------------------------------------------------------------------------//
	barco();
		
	printf("\n\n");
	
	printf("\t Escolha uma das opções para decidir quem irá começar\n\n");
	printf("\t        [1] JOGADOR[1] - PAR   e JOGADOR[2] - ÍMPAR\n");
	printf("\t        [2] JOGADOR[1] - ÍMPAR e JOGADOR[2] - PAR\n\n");
	
	printf("Opção: ");
	scanf("%d",&op);
	
	srand(time(NULL));
	int a=0;
	a=rand()%100;
	
	par_impar(op,a);
	
//-----------------------------------------------------------------------------------------------//
	
	
	                    //3) Preenchendo as posições das matrizes com 0
	
//-----------------------------------------------------------------------------------------------//	
	
	for(i=0;i<8;i++)
    {
    	for(j=0;j<8;j++)
    	{
    		tab_mat1[i][j]=0;
    		tab_mat2[i][j]=0;
    		tab_gab1[i][j]=0;
			tab_gab2[i][j]=0;
		}
	}
	
//-----------------------------------------------------------------------------------------------//	

   //4) Tela referente ao posicionamento dos barcos nas matrizes tab_gab1[8][8] e tab_gab2[8][8]
	
//-----------------------------------------------------------------------------------------------//	
	
	//JOGADOR QUE VENCEU PAR OU ÍMPAR - Leitura das coordenadas do JOGADOR
	
	
	
	for(int aa=0;aa<64;aa++)
	{
		vetorA[aa]=aa;
	}
	
	while(inicio==1)//laço que testa se as três coordenadas são adjacentes. Caso seja o laço estoura e segue
	{
	
		for(i=0;i<3;i++)//laço para receber três coordenadas(linha,coluna) do jogador
		{
			system("cls");
		
			do//laço que testa se as coordenadas de linha e coluna estão entre 0 e 7
			{
				
				system("cls");
				printf("%s, posicione o seu barco\n\n\n",nome_jogador1);
				apresentacao_matriz_coordenadas(tab_mat1); //função que apenas exibe a matriz com 0 para o jogador ver as coordenadas
				receber_coordenadas(l_jogador1,c_jogador1,i); //função que recebe as coordenadas e exibe se elas são aceitas ou não
					
			}while((l_jogador1[i]<0)||(l_jogador1[i]>7)||(c_jogador1[i]<0)||(c_jogador1[i]>7));
		}
		
		if(verifica(l_jogador1,c_jogador1))//função que irá testar se as três coordenadas(linha,coluna) são adjacentes 
		{
			printf("\n\tSuas coordenadas foram testadas e aceitas");
			inicio=2;
		}
		else
		{
			printf("\n\tSuas coordenadas foram testadas e não foram aceitas");
			printf("\n\t Por gentileza, as coordenadas devem ser adjacentes");
		}
		
		getch();
	}
	
	adicionar_1_tabgab(l_jogador1,c_jogador1,tab_gab1,tab_gab2,1);//função que adiciona o número "1" nas tab_gab com base nas coordenadas informadas
	exibir_tabgab(tab_gab1,tab_gab2,1);//função que exibe a matriz com posicionamento do barco
	getch();
	
	//JOGADOR QUE PERDEU PAR OU ÍMPAR  - Leitura das coordenadas do JOGADOR - mesmas informações para do jogador acima
	
	system("cls");
	inicio=1;//para iniciar o laço do jogador 2
	
	while(inicio==1)
	{
	
		for(i=0;i<3;i++)
		{
			system("cls");
		
			do
			{
				system("cls");
				printf("%s, posicione o seu barco\n\n\n",nome_jogador2);
				apresentacao_matriz_coordenadas(tab_mat1);
				receber_coordenadas(l_jogador1,c_jogador1,i);
			
			}while((l_jogador1[i]<0)||(l_jogador1[i]>7)||(c_jogador1[i]<0)||(c_jogador1[i]>7));
		}
		
		if(verifica(l_jogador1,c_jogador1))
		{
			printf("\n\tSuas coordenadas foram testadas e aceitas");
			inicio=2;
		}
		else
		{
			printf("\n\tSuas coordenadas foram testadas e não foram aceitas");
			printf("\n\t Por gentileza, as coordenadas devem ser adjacentes");
		}
		
		getch();
	}
	
	adicionar_1_tabgab(l_jogador1,c_jogador1,tab_gab1,tab_gab2,0);
	exibir_tabgab(tab_gab1,tab_gab2,0);
	getch();
	
//-----------------------------------------------------------------------------------------------//	

                          //5) Tela referente ao início do jogo
	
//-----------------------------------------------------------------------------------------------//	
	
	i=0;
	
	while(i<2)
	{
		system("cls");
		barco();
		printf("\t                 %s x %s \n",nome_jogador1,nome_jogador2);
		printf("\t         Preparem-se para o íncio da batalha\n\n");
		printf("\t                   Carregando");
		
		for(j=0;j<5;j++)
		{
			printf(".");
			Sleep(900);
		}
		i++;
	}

//-----------------------------------------------------------------------------------------------//	

            //6) Tela que mostra a batalha entre Jogador1 x Jogador2 e o Resultado Final
	
//-----------------------------------------------------------------------------------------------//	
	
	system("cls");
	inicio=1;
	int jogador_1=1,jogador_2=1,contador1_confere=0;
	int jogada_jogador1_linha=0,jogada_jogador1_coluna=0;
	int pontos1=0,tentativa1=5,pontos2=0,tentativa2=5;
		
	while(inicio==1)//laço que controla o jogo do início até o final 
	{
		
		if(jogador_1==1 && tentativa1>0)//condição para o jogador que venceu o par ou ímpar iniciar
		{
			system("cls");
			
			do//esse laço recebe as coordenadas do para o tiro 
			{
				system("cls");
				
				do//esse laço verifica se as coordenadas estão entre 0 e 7
				{
					system("cls");
					contador1_confere=0;
					printf("%s, informe as coordenadas para o seu tiro\n\n\n",nome_jogador1);
					printf("Pontos: %d\n",pontos1); //pontuação
					printf("Tentativas: %d\n\n\n",tentativa1);//tentativas
				
					exibicao_tabmat(tab_mat1,tab_mat2,0);//função que exibe da tab_mat2
			
					printf("\n Coordenada\n");//informar as cooredenadas
			
					printf("\n Digite linha: ");
					scanf("%d",&jogada_jogador1_linha);
			
					printf("\n Digite coluna: ");
					scanf("%d",&jogada_jogador1_coluna);
					
					if((jogada_jogador1_linha<0)||(jogada_jogador1_linha>7)||(jogada_jogador1_coluna<0)||(jogada_jogador1_coluna>7))
					{
						printf("\n\t A linha e coluna devem estar entre 0 e 7!\n");
						getch();
					}
					
				}while((jogada_jogador1_linha<0)||(jogada_jogador1_linha>7)||(jogada_jogador1_coluna<0)||(jogada_jogador1_coluna>7));
				
				conferencia_coordenadas(jogada_jogador1_linha,jogada_jogador1_coluna,tab_mat1,tab_mat2,
										&contador1_confere,1);//função que confere se as coordenadas informadas são repetidas
				
				if(contador1_confere>0)//se o retorno da função for maior que 0 a coordenada é aceita
				{
					printf("\n\n\tCoordenada aceita!");
				}
				else//se o retorno da função for 0 a coordenada não é aceita
				{
					printf("\n\n\t  Essa coordenada já foi informada!\n");
					printf("\tPor favor, entre com uma nova coordenada!");
					getch();
				}
				
			}while(contador1_confere==0);//se a coordenada foi aceita o laço de verificação é estourado
						
			for(i=0;i<8;i++)//laço que irá comparar as coordenadas informadas com o gabarito(tab_gab2)
			{
				if(jogada_jogador1_linha==i)
				{
					for(j=0;j<8;j++)
					{
						if(jogada_jogador1_coluna==j)
						{
							if(tab_gab2[i][j]==0)//se as coordenadas informadas indicarem valor 0 na tab_gab2
							{
								tab_mat2[i][j]=9;//tab_mat2 irá receber valor 9
							
							}
							else
							{
								tab_mat2[i][j]=1;//tab_mat2 irá receber valor1
								pontos1++;//adiciona um ponto, pois adiciona onde o barco está localizado
								tentativa1++;//por ter acertado, ganha uma tentativa
								
							}
						}
								
					}		
				}	
			}
			tentativa1--;//retirada de uma tentativa após a jogada	
		
			getch();
			system("cls");
			printf("%s, veja a posição do seu tiro no tabuleiro\n\n\n",nome_jogador1);
			printf("Pontos: %d\n",pontos1); //pontuação
			printf("Tentativas: %d\n\n\n",tentativa1);//tentativas
				
			exibicao_tabmat(tab_mat1,tab_mat2,0);//função que exibe da tab_mat2
			efeito();
		
			printf("\n\n\tPressione ENTER para o próximo jogador jogar");
		
			getch();	
		}
		
		resultado(pontos1,tentativa1,pontos2,tentativa2,&inicio,&jogador_2);//função que testa o resultado final
		
		if(jogador_2==1 && tentativa2>0)//condição para o jogador que perdeu o par ou ímpar iniciar
		{
			system("cls");
			
			do//esse laço recebe as coordenadas para o tiro 
			{
				system("cls");
				
				do//esse laço verifica se as coordenadas estão entre 0 e 7
				{
					system("cls");
					
					contador1_confere=0;
					printf("%s, informe as coordenadas para o seu tiro\n\n\n",nome_jogador2);
					printf("Pontos: %d\n",pontos2); //pontuação
					printf("Tentativas: %d\n\n\n",tentativa2);//tentativas
				
					exibicao_tabmat(tab_mat1,tab_mat2,1);//função que exibe da tab_mat1
			
					printf("\n Coordenada\n");//informar as coordenadas
			
					printf("\n Digite linha: ");
					scanf("%d",&jogada_jogador1_linha);
			
					printf("\n Digite coluna: ");
					scanf("%d",&jogada_jogador1_coluna);
					
					if((jogada_jogador1_linha<0)||(jogada_jogador1_linha>7)||(jogada_jogador1_coluna<0)||(jogada_jogador1_coluna>7))
					{
						printf("\n\t A linha e coluna devem estar entre 0 e 7!\n");
						getch();
					}
					
				}while((jogada_jogador1_linha<0)||(jogada_jogador1_linha>7)||(jogada_jogador1_coluna<0)||(jogada_jogador1_coluna>7));
				
				conferencia_coordenadas(jogada_jogador1_linha,jogada_jogador1_coluna,tab_mat1,tab_mat2,
										&contador1_confere,0);//função que confere se as coordenadas informadas são repetidas
				
				if(contador1_confere>0)//se o retorno da função for maior que 0 a coordenada é aceita
				{
					printf("\n\n\tCoordenada aceita!");
				}
				else//se o retorno da função for 0 a coordenada não é aceita
				{
					printf("\n\n\t  Essa coordenada já foi informada!\n");
					printf("\tPor favor, entre com uma nova coordenada!");
					getch();
				}
				
			}while(contador1_confere==0);//se a coordenada foi aceita o laço de verificação é estourado
						
			for(i=0;i<8;i++)//laço que irá comparar as coordenadas informadas com o gabarito(tab_gab2)
			{
				if(jogada_jogador1_linha==i)
				{
					for(j=0;j<8;j++)
					{
						if(jogada_jogador1_coluna==j)
						{
							if(tab_gab1[i][j]==0)//se as coordenadas informadas indicarem valor 0 na tab_gab1
							{
								tab_mat1[i][j]=9;//tab_mat1 irá receber valor 9
								
							}
							else
							{
								tab_mat1[i][j]=1;//tab_mat1 irá receber valor1
								pontos2++;//adiciona um ponto, pois adiciona onde o barco está localizado
								tentativa2++;//por ter acertado, ganha uma tentativa
								
							}
						}
								
					}		
				}	
			}
			tentativa2--;//retirada de uma tentativa após a jogada
			
			getch();
			system("cls");
			printf("%s, veja a posição que o seu tiro no tabuleiro\n\n\n",nome_jogador2);
			printf("Pontos: %d\n",pontos2); //pontuação
			printf("Tentativas: %d\n\n\n",tentativa2);//tentativas
				
			exibicao_tabmat(tab_mat1,tab_mat2,1);//função que exibe da tab_mat1
			efeito();
		
			printf("\n\n\tPressione ENTER para o próximo jogador jogar");
		
		}
		
		getch();
	}
	
	printf("\n\n\n");
	system("pause");
	return (0);
}

void apresentacao(){
	
	char b[10]={'*','*','*','*','*','*','*','*','*','*'};
	char apre[40]={"BATALHA NAVAL"};
	int ii=0,nn=0,kk=0,l=0,n=0;
	
	for (ii=0;ii<=3;ii++)
	{
		system("color 0A");
		system("cls");
		
		printf("\t\t\t  ");
		
		for(l=0;l<=14;l++)
		{
			printf("%c",apre[l]);
		}
		
		printf("\n\n\n\n");
		printf("          ___                                        ___ \n");
		printf("         |___|                                      |___|\n");
		printf("       _____|____                                ____|_____\n");
		printf("       \\________/                                \\________/");
		
		gotoxy(18,7);
		
		for(nn=0;nn<10;nn++)
		{
			printf(" %c ",b[nn]);
			Sleep(200);
		}
		
		for(kk=0;kk<=3;kk++)
		{
			Sleep(150);
			system("color 0C");
			Sleep(150);
			system("color 0E");
		}
		system("color 0A");	
	}
	
	system("cls");
	
	printf("\t\t\t  ");
		
	for(l=0;l<=14;l++)
	{
		
		printf("%c",apre[l]);
	}
	
	printf("\n\n\n\n");
	printf("          ___                                                 \n");
	printf("         |___|                                                \n");
	printf("       _____|____                                !!!!!BOOM!!!!!\n");
	printf("       \\________/                                               ");

	
	gotoxy(18,7);
		
	for(n=0;n<10;n++)
	{
		printf(" %c ",b[n]);
	}
	
	gotoxy(18,10);
	
	printf("Digite ENTER para entrar no JOGO");
}

void barco(void){
	
	printf("\t\t         _______               \n");
	printf("\t\t        |_______|              \n");
	printf("\t\t                |              \n");
	printf("\t\t                |              \n");
	printf("\t\t________________|_______________\n");
	printf("\t\t\\______________________________/\n");
		
	printf("\n\n\n");
}
void par_impar(int op, int a){
	
	
	if(op==1)
	{
		
		if(a%2==0)
		{
			printf("\n\tNÚMERO SORTEADO: %d\n\n",a);
			printf("\n\tNOME JOGADOR[1]: ");
			fflush(stdin);
			gets(nome_jogador1);
		
			printf("\n\tNOME JOGADOR[2]: ");
			fflush(stdin);
			gets(nome_jogador2);
		}
		else
		{
			printf("\n\tNÚMERO SORTEADO: %d\n\n",a);
			printf("\n\tNOME JOGADOR[2]: ");
			fflush(stdin);
			gets(nome_jogador1);
		
			printf("\n\tNOME JOGADOR[1]: ");
			fflush(stdin);
			gets(nome_jogador2);
		}
		
	}
	
	if(op==2)
	{
		
		if(a%2==0)
		{
			
			printf("\n\tNÚMERO SORTEADO: %d\n\n",a);
			printf("\n\tNOME JOGADOR[2]: ");
			fflush(stdin);
			gets(nome_jogador1);
		
			printf("\n\tNOME JOGADOR[1]: ");
			fflush(stdin);
			gets(nome_jogador2);
		}
		else
		{
			printf("\n\tNÚMERO SORTEADO: %d\n\n",a);
			printf("\n\tNOME JOGADOR[1]: ");
			fflush(stdin);
			gets(nome_jogador1);
		
			printf("\n\tNOME JOGADOR[2]: ");
			fflush(stdin);
			gets(nome_jogador2);
		}
		
	}
}

void apresentacao_matriz_coordenadas(int tab_mat1[][8]){
	
	int i=0,j=0;
	
	printf("\t    L\\C");
	
	for(i=0;i<8;i++)
	{
		printf(" %d ",i);
	}
	
	printf("\n\n");
		
	for(i=0;i<8;i++)
    {
    	printf("\t     %d ",i);
    	
		for(j=0;j<8;j++)
    	{
    		printf(" %d ",tab_mat1[i][j]);
    		
		}
		
		printf("\n\t    ---------------------------",tab_mat1[i][j]);
		printf("\n");
	}
	
}

void receber_coordenadas(int l_jogador1[],int c_jogador1[],int i){
	
	printf("\n Coordenada %d\n",i+1);
			
	printf("\n Digite linha: ");
	scanf("%d",&l_jogador1[i]);
			
	printf("\n Digite coluna: ");
	scanf("%d",&c_jogador1[i]);
			
	if((l_jogador1[i]<0)||(l_jogador1[i]>7)||(c_jogador1[i]<0)||(c_jogador1[i]>7))
	{
		printf("\n\t A linha e coluna devem estar entre 0 e 7!\n");
		getch();
	}
	else
	{
		printf("\n\t Coordenadas aceitas!\n");
		getch();
	}
	
}

bool verifica(int l_jogador1[],int c_jogador1[]){
	
	int i=0,j=1,a=1,aux=0,b=0,c=0;
	
	for(i=0;i<3;i++)
	{
		for(;j<3;j++)
		{
			if(l_jogador1[i]>l_jogador1[j])
			{
				aux=l_jogador1[i];
				l_jogador1[i]=l_jogador1[j];
				l_jogador1[j]=aux;
			}
		}
		a++;
		j=a;
	}
	
	a=1,j=1,aux=0;
	
	for(i=0;i<3;i++)
	{
		for(;j<3;j++)
		{
			if(c_jogador1[i]>c_jogador1[j])
			{
				aux=c_jogador1[i];
				c_jogador1[i]=c_jogador1[j];
				c_jogador1[j]=aux;
			}
		}
		a++;
		j=a;
	}
		
	if((l_jogador1[0]==l_jogador1[1])&&(l_jogador1[1]==l_jogador1[2]))
	{
		b=c_jogador1[1]-c_jogador1[0];
		c=c_jogador1[2]-c_jogador1[1];
				
		if((b-c)==0)
		{
			return(1);
		}
		else
		{
			return(0);
		}
	}
	
	if((c_jogador1[0]==c_jogador1[1])&&(c_jogador1[1]==c_jogador1[2]))
	{
		b=l_jogador1[1]-l_jogador1[0];
		c=l_jogador1[2]-l_jogador1[1];
		
		if((b-c)==0)
		{
			return(1);
		}
		else
		{
			return(0);
		}
	}
	
	if((l_jogador1[0]!=l_jogador1[1])&&(l_jogador1[1]!=l_jogador1[2])||
	   (l_jogador1[0]==l_jogador1[1])&&(l_jogador1[1]!=l_jogador1[2])||
	   (l_jogador1[0]!=l_jogador1[1])&&(l_jogador1[1]==l_jogador1[2])||
	   (l_jogador1[0]==l_jogador1[2])&&(l_jogador1[1]!=l_jogador1[2])
	)
	{
		return(0);
	}
	
	if((c_jogador1[0]!=c_jogador1[1])&&(c_jogador1[1]!=c_jogador1[2])||
	   (c_jogador1[0]==c_jogador1[1])&&(c_jogador1[1]!=c_jogador1[2])||
	   (c_jogador1[0]!=c_jogador1[1])&&(c_jogador1[1]==c_jogador1[2])||
	   (c_jogador1[0]==c_jogador1[2])&&(c_jogador1[1]!=c_jogador1[2])
	)
	{
		return(0);
	}
	
}

void adicionar_1_tabgab(int l_jogador1[],int c_jogador1[],int tab_gab1[][8],int tab_gab2[][8],int a){
	
	int w=0,l=0,i=0;
	
	if(a==1)
	{
		if((l_jogador1[0]==l_jogador1[1])&&(l_jogador1[1]==l_jogador1[2]))
		{
			w=l_jogador1[0];
			
			for(i=0;i<3;i++)
			{
				l=c_jogador1[i];
				tab_gab1[w][l]=1;
			}
		}
		else
		{
			w=c_jogador1[0];
			
			for(i=0;i<3;i++)
			{
				l=l_jogador1[i];
				tab_gab1[l][w]=1;
			}
		}
	}
	else
	{
		if((l_jogador1[0]==l_jogador1[1])&&(l_jogador1[1]==l_jogador1[2]))
		{
			w=l_jogador1[0];
			
			for(i=0;i<3;i++)
			{
				l=c_jogador1[i];
				tab_gab2[w][l]=1;
			}
		}
		else
		{
			w=c_jogador1[0];
			
			for(i=0;i<3;i++)
			{
				l=l_jogador1[i];
				tab_gab2[l][w]=1;
			}
		}
	}
	
}

void exibir_tabgab(int tab_gab1[][8],int tab_gab2[][8],int a){
	
	int i=0,j=0;
	
	if(a==1)
	{
	
		printf("\n\n\n\tVeja a posição de seu barco no tabuleiro\n\n");
	
		printf("\t    L\\C");
	
		for(i=0;i<8;i++)
		{
			printf(" %d ",i);
		}
	
		printf("\n\n");
		
		for(i=0;i<8;i++)
    	{	
    		printf("\t     %d ",i);
    	
			for(j=0;j<8;j++)
    		{
    			printf(" %d ",tab_gab1[i][j]);
    		
			}
		
			printf("\n\t    ---------------------------",tab_gab1[i][j]);
			printf("\n");
		}
	}
	else
	{
		printf("\n\n\n\tVeja a posição de seu barco no tabuleiro\n\n");
	
		printf("\t    L\\C");
	
		for(i=0;i<8;i++)
		{
			printf(" %d ",i);
		}
	
		printf("\n\n");
		
		for(i=0;i<8;i++)
    	{	
    		printf("\t     %d ",i);
    	
			for(j=0;j<8;j++)
    		{
    			printf(" %d ",tab_gab2[i][j]);
    		
			}
		
			printf("\n\t    ---------------------------",tab_gab2[i][j]);
			printf("\n");
		}
	}
}

void exibicao_tabmat(int tab_mat1[][8],int tab_mat2[][8],int a){
	
	int i=0,j=0;
	
	if(a==1)
	{
		printf("\t    L\\C");
	
		for(i=0;i<8;i++)
		{
			printf(" %d ",i);
		}
	
		printf("\n\n");
		
		for(i=0;i<8;i++)
    	{
    		printf("\t     %d ",i);
    	
			for(j=0;j<8;j++)
    		{
    			printf(" %d ",tab_mat1[i][j]);
    		
			}
		
			printf("\n\t    ---------------------------",tab_mat1[i][j]);
			printf("\n");
		}
	}
	else
	{
		printf("\t    L\\C");
	
		for(i=0;i<8;i++)
		{
			printf(" %d ",i);
		}
	
		printf("\n\n");
		
		for(i=0;i<8;i++)
    	{
    		printf("\t     %d ",i);
    	
			for(j=0;j<8;j++)
    		{
    			printf(" %d ",tab_mat2[i][j]);
    		
			}
		
			printf("\n\t    ---------------------------",tab_mat2[i][j]);
			printf("\n");
		}
	}
	
}

void conferencia_coordenadas(int jogada_jogador1_linha,int jogada_jogador1_coluna,int tab_mat1[][8],
                        int tab_mat2[][8],int *contador1_confere,int a){


	int i=0,j=0;
	
	if(a==1)
	{
		for(i=0;i<8;i++)
		{
			if(jogada_jogador1_linha==i)
			{
				for(j=0;j<8;j++)
				{
					if(jogada_jogador1_coluna==j)
					{
						if(tab_mat2[i][j]==0)
						{
							*contador1_confere=*contador1_confere+1;
						}
					}
								
				}
						
			}	
		}
		
	}
	else
	{
		for(i=0;i<8;i++)
		{
			if(jogada_jogador1_linha==i)
			{
				for(j=0;j<8;j++)
				{
					if(jogada_jogador1_coluna==j)
					{
						if(tab_mat1[i][j]==0)
						{
							*contador1_confere=*contador1_confere+1;
						}
					}
								
				}
						
			}	
		}
	}
	
}

void efeito(void){
	
	int kk=0;
	
	for(kk=0;kk<=3;kk++)
		{
			Sleep(150);
			system("color 0C");
			Sleep(150);
			system("color 0E");
		}
		system("color 0A");
	
}

void resultado(int pontos1,int tentativa1,int pontos2,int tentativa2,int *inicio,int *jogador_2){
	
	if(pontos1==3 && tentativa1>=0)
		{
			*inicio=2;
			*jogador_2=2;
			
			system("cls");
			printf("\t\t*****Resultado Final*****\n\n");
			
			printf("\t%s, você é o vencedor da Batalha!\n",nome_jogador1);
			printf("\t    Pontos:     %d\n",pontos1);
			printf("\t    Tentativas: %d\n\n",tentativa1);
			
			printf("\t%s, você perdeu a Batalha!\n",nome_jogador2);
			printf("\t    Pontos:     %d\n",pontos2);
			printf("\t    Tentativas: %d\n",tentativa2);
		}
		else
		{
			if(pontos2==3 && tentativa2>=0)
			{
				
				*inicio=2;
				*jogador_2=2;
				
				system("cls");
				printf("\t\t*****Resultado Final*****\n\n");
			
				printf("\t%s, você é o vencedor da Batalha!\n",nome_jogador2);
				printf("\t    Pontos:     %d\n",pontos2);
				printf("\t    Tentativas: %d\n\n",tentativa2);
			
				printf("\t%s, você perdeu a Batalha!\n",nome_jogador1);
				printf("\t    Pontos:     %d\n",pontos1);
				printf("\t    Tentativas: %d\n",tentativa1);
			}
			else
			{
				if(((pontos1<3)&&(tentativa1==0))&&((pontos1<3)&&(tentativa1==0)))
				{
					if(pontos1>pontos2)
					{
						
						*inicio=2;
						*jogador_2=2;
						
						system("cls");
						printf("\t\t*****Resultado Final*****\n\n");
			
						printf("\t%s, você é o vencedor da Batalha!\n",nome_jogador1);
						printf("\t    Pontos:     %d\n",pontos1);
						printf("\t    Tentativas: %d\n\n",tentativa1);
			
						printf("\t%s, você perdeu a Batalha!\n",nome_jogador2);
						printf("\t    Pontos:     %d\n",pontos2);
						printf("\t    Tentativas: %d\n",tentativa2);
					}
					
					if(pontos1<pontos2)
					{
						*inicio=2;
						*jogador_2=2;
						
						system("cls");
						printf("\t\t*****Resultado Final*****\n\n");
			
						printf("\t%s, você é o vencedor da Batalha!\n",nome_jogador2);
						printf("\t    Pontos:     %d\n",pontos2);
						printf("\t    Tentativas: %d\n\n",tentativa2);
			
						printf("\t%s, você perdeu a Batalha!\n",nome_jogador1);
						printf("\t    Pontos:     %d\n",pontos1);
						printf("\t    Tentativas: %d\n",tentativa1);
					}
					
					if(pontos1==pontos2)
					{
						*inicio=2;
						*jogador_2=2;
						
						system("cls");
						printf("\t\t*****Resultado Final*****\n\n");
						
						printf("\t\t         Empate\n\n");
						
						printf("\t%s: \n",nome_jogador1);
						printf("\t    Pontos:     %d\n",pontos1);
						printf("\t    Tentativas: %d\n\n",tentativa1);
			
						printf("\t%s: você perdeu a Batalha!\n",nome_jogador2);
						printf("\t    Pontos:     %d\n",pontos2);
						printf("\t    Tentativas: %d\n",tentativa2);
					}
					
				}
			}
		}
	
}

