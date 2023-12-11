#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DECLARANDO ESTRUTURA DOS ELEMENOS A SEREM ORDENADOS NO VETOR
struct Vetor
{
    int chave;
    float real;
};
typedef struct Vetor estrutura_vetor;

//FUNÇÃO TESTE
void imprime_teste (estrutura_vetor *v,int tamanho)
{
    for (int i=0;i<tamanho;i++)
    {
        printf ("\nChave [%d] = %d",tamanho,v[i].chave);
        printf ("\nReal [%d] = %f",tamanho,v[i].real);
    }
}

// FUNÇÃO QUE TESTA SE O VETOR ESTÁ ORDENADO
int teste_ordenada (estrutura_vetor *v, int tamanho)
{
    for (int i=0;i<tamanho;i++)
    {
        if(v[i].chave < v[i+1].chave)
        {
            return 1;
        }
    }

    return 0;
}

void combsort (estrutura_vetor *vetor, int tamanho)
{
    int e,d;
    int intervalo;
    int trocado = 1;
    estrutura_vetor aux;

    intervalo = tamanho;

    while (intervalo > 1 || trocado == 1)
    {
        intervalo = intervalo * 10 / 13;

        if(intervalo == 9 || intervalo == 10)
            intervalo = 11;

        if (intervalo < 1)
            intervalo = 1;

        trocado = 0;

        for (e = 0, d = intervalo; d < tamanho; e++, d++)
		{
			if (vetor[e].chave < vetor[d].chave)
			{
				aux = vetor[e];
				vetor[e] = vetor[d];
				vetor[d] = aux;
				trocado = 1;
			}
		}
    }
}

// QUICK SORT COM PIVO NO MEIO
void quicksort_meio(estrutura_vetor *vetor, int LI, int LS)
{
   int e, d;
   estrutura_vetor pivo, aux;

   e = LI;
   d = LS;
   pivo = vetor[(LI + LS) / 2];

   do
   {
      while(vetor[e].chave > pivo.chave)
        e++;

      while(vetor[d].chave < pivo.chave)
        d--;

      if(e <= d)
      {
         aux = vetor[e];
         vetor[e] = vetor[d];
         vetor[d] = aux;
         e++;
         d--;
      }

   }while(e <= d);

   if(LI < d)
      quicksort_meio(vetor, LI, d);
   if(e < LS)
      quicksort_meio(vetor, e, LS);
}

// FUNÇÃO QUICK COM O PIVO NO FIM PARTE 2
int particao_fim(estrutura_vetor *v,int LI, int LS)
{
    int e = LI;
    int d = LS;
    estrutura_vetor pivo = v[LS];
    estrutura_vetor aux;

    while (e < d)
    {
        while((v[e].chave > pivo.chave) && (e < LS))
        {
            e++;
        }

        while((v[d].chave <= pivo.chave) && (d > LI))
        {
            d--;
        }

        if(e < d)
        {
            aux = v[e];
            v[e] = v[d];
            v[d] = aux;
        }
    }
        aux = v[LS];
        v[LS] = v[e];
        v[e] = aux;

    return e;
}

// FUNÇÃO QUICK COM O PIVO NO FIM PARTE 1
void quicksort_fim(estrutura_vetor *v, int LI, int LS)
{
    if(LI < LS)
    {
        int p,i;

        p = particao_fim(v,LI,LS);

        quicksort_fim(v,LI,p-1);
        quicksort_fim(v,p+1,LS);
    }
}

// FUNÇÃO QUICK COM PIVO NO INICIO PARTE 2
int particao_inicio(estrutura_vetor *v,int LI, int LS)
{
    int e = LI;
    int d = LS;
    estrutura_vetor pivo = v[LI];
    estrutura_vetor aux;

    while (e < d)
    {
        while((v[e].chave >= pivo.chave) && (e < LS))
        {
            e++;
        }

        while((v[d].chave < pivo.chave) && (d > LI))
        {
            d--;
        }

        if(e < d)
        {
            aux = v[e];
            v[e] = v[d];
            v[d] = aux;
        }
    }
        aux = v[LI];
        v[LI] = v[d];
        v[d] = aux;

    return d;
}

// FUNÇÃO QUICK COM PIVO NO INICIO PARTE 1
void quicksort_inicio(estrutura_vetor *v, int LI, int LS)
{
    if(LI < LS)
    {
        int p,i;

        p = particao_inicio(v,LI,LS);

        quicksort_inicio(v,LI,p-1);
        quicksort_inicio(v,p+1,LS);
    }
}

// SHELLSORT
void shellsort(estrutura_vetor *vetor, int tamanho)
{
    int i = 0;
    int j = 0;
    int h = 0;
    estrutura_vetor aux;

    for (h = 1; h < tamanho; h = 3 * h + 1)
    {
        int tempH = h; // Armazena o valor original de h

        while (tempH > 0)
        {
            tempH = (tempH - 1) / 3;

            for (i = tempH; i < tamanho; i++)
            {
                aux = vetor[i];
                j = i;

                while (j >= tempH && vetor[j - tempH].chave < aux.chave)
                {
                    vetor[j] = vetor[j - tempH];
                    j -= tempH;
                }

                vetor[j] = aux;
            }
        }
    }
}

// MERGE SORT PARTE 2
void merge(estrutura_vetor* vetor, int ini, int meio,int fim,int tamanho)
{
    int i = 0;
    int j = 0;
    int k = 0;
    estrutura_vetor *aux;

    aux = (estrutura_vetor*)malloc(tamanho*sizeof(estrutura_vetor));

    i = ini;
    j = meio+1;
    k = ini;

    while(i<=meio && j<=fim)
    {
        if(vetor[i].chave > vetor[j].chave)
        {
            aux[k]=vetor[i];
            i++;
        }
        else
        {
            aux[k] = vetor [j];
            j++;
        }
        k++;
    }

    while(i<=meio)
    {
        aux[k] = vetor[i];
        i++;
        k++;
    }

    while(j<=fim)
    {
        aux[k]=vetor[j];
        j++;
        k++;
    }

    for(i=ini; i<=fim;i++)
    {
        vetor[i]=aux[i];
    }

    free(aux);
}

// MERGE SORT PARTE 1
void merge_sort(estrutura_vetor* vetor, int ini, int fim, int tamanho)
{
    int meio;

    if(ini < fim)
    {
        meio = (ini+fim)/2 ;
        merge_sort(vetor,ini,meio,tamanho);
        merge_sort(vetor,meio+1,fim,tamanho);
        merge(vetor,ini,meio,fim,tamanho);
    }
}

// BUBBLE SORT
void bubbleSort(estrutura_vetor *vetor, int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (vetor[j].chave < vetor[j + 1].chave)
            {
                estrutura_vetor temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// INSERTION SORT
void insertionSort(estrutura_vetor* vetor, int tamanho)
{
    estrutura_vetor aux;
    int i = 0;
    int j = 0;

    for (i = 1; i < tamanho; i++)
    {
        aux = vetor[i];

        j = i - 1;

        while (j >= 0 && vetor[j].chave < aux.chave)
        {
            vetor[j + 1].chave = vetor[j].chave;
            vetor[j + 1].real = vetor[j].real;
            j--;
        }
        vetor[j+1]=aux;
    }
}

// FUNÇÃO PARA CRIAR O VETOR
void cria_vetor(estrutura_vetor *vetor, int seed, int tamanho)
{
    clock_t start_time, end_time; // Cronometro
    double elapsed_time;          // Cronometro
    int opcao;
    int resultado;

    // Gerando Conjunto de Numeros aleatórios de acordo com a seed (razão = 10) - FORMA 1s
    for(seed = 10; seed <= 100; seed += 10)
    {
        vetor = (estrutura_vetor *)malloc(tamanho * sizeof(estrutura_vetor));

        // Gernando valores aleatórios
        srand(seed);

        // Preenchendo o vetor - Forma 1
        for (int i = 0; i < tamanho; i++)
        {
            vetor[i].chave = rand()% 101;
            vetor[i].real = 100.0 + (float)rand() / RAND_MAX * (1000.0 - 100.0);
        }

        printf ("FORMA 1\n\nVetor de Tamanho = %d \nSemente = %d \nEscolha o metodo de ordenacao: ",tamanho,seed);
        printf ("\n\n[1]. InsertionSort");
        printf ("\n[2]. BubleSort");
        printf ("\n[3]. ShellSort");
        printf ("\n[4]. MergeSort");
        printf ("\n[5]. QuickSort com pivo no inicio");
        printf ("\n[6]. QuickSort com pivo no fim");
        printf ("\n[7]. QuickSort com pivo no meio");
        printf ("\n[8]. CombSort");

        do
        {
            printf ("\n\nOpcao: ");
            opcao = 0;
            scanf  ("%d",&opcao);
        }while(opcao<1 || opcao>8);

        switch(opcao)
        {

            case 1:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                insertionSort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 2:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                bubbleSort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 3:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                shellsort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 4:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                merge_sort(vetor,0,tamanho-1,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;



            case 5:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                quicksort_inicio(vetor,0,tamanho-1);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 6:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                quicksort_fim(vetor,0,tamanho-1);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;


            case 7:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                quicksort_meio(vetor,0,tamanho-1);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;

            case 8:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                combsort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;
        }
        free(vetor);

    }


    // FORMA 2
    for(seed = 10; seed <= 100; seed += 10)
    {
        // Alocação dinâmica para o vetor
        vetor = (estrutura_vetor *)malloc(tamanho * sizeof(estrutura_vetor));

        // Gernando valores aleatórios
        srand(seed);

        // Preenchendo o vetor - Forma 2
        for (int i = 1; i < tamanho; i++)
        {
            vetor[i].chave = vetor[i-1].chave + (rand()%101);
            vetor[i].real = 100.0 + (float)rand() / RAND_MAX * (1000.0 - 100.0);
        }

        printf ("FORMA 2\n\nVetor de Tamanho = %d \nSemente = %d \nEscolha o metodo de ordenacao: ",tamanho,seed);
        printf ("\n\n[1]. InsertionSort");
        printf ("\n[2]. BubleSort");
        printf ("\n[3]. ShellSort");
        printf ("\n[4]. MergeSort");
        printf ("\n[5]. QuickSort com pivo no inicio");
        printf ("\n[6]. QuickSort com pivo no fim");
        printf ("\n[7]. QuickSort com pivo no meio");
        printf ("\n[8]. CombSort");

        do
        {
            printf ("\n\nOpcao: ");
            opcao = 0;
            scanf  ("%d",&opcao);
        }while(opcao<1 || opcao>8);

        switch(opcao)
        {

            case 1:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                insertionSort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 2:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                bubbleSort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 3:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                shellsort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 4:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                merge_sort(vetor,0,tamanho-1,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;



            case 5:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                quicksort_inicio(vetor,0,tamanho-1);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);


            break;

            case 6:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                quicksort_fim(vetor,0,tamanho-1);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;


            case 7:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                quicksort_meio(vetor,0,tamanho-1);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;

            case 8:

                start_time = 0;
                end_time = 0;
                elapsed_time = 0;


                printf ("\n--------------- STATUS ---------------");
                start_time = clock();
                combsort(vetor,tamanho);
                end_time = clock();
                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

                resultado = 0;
                resultado = teste_ordenada(vetor,tamanho);

                if(resultado == 0)
                {
                    printf ("\nTESTE: ESTA ORDENADO");
                }
                if(resultado == 1)
                {
                    printf ("\nTESTE: NAO ORDENADO");
                }

                printf("\nTEMPO DE EXECUCAO EM SEGUNDOS:%f \n--------------------------------------\n\n", elapsed_time);

            break;
        }

        free(vetor);
    }

    system("pause");

}

// FUNÇÃO PRINCIPAL
int main()
{
    // Declarando variáveis
    unsigned int seed;            // Semente

    estrutura_vetor *vetor_1;     // Vetor de tamanho 10 000
    estrutura_vetor *vetor_2;     // Vetor de tamanho 50 000
    estrutura_vetor *vetor_3;     // Vetor de tamanho 100 000
    estrutura_vetor *vetor_4;     // Vetor de tamanho 500 000
    estrutura_vetor *vetor_5;     // Vetor de tamanho 1 000 000

    // Chamando a função para criar o vetor e ordenar com o método desejado
    cria_vetor(vetor_1,seed,10000);

    cria_vetor(vetor_2,seed,50000);

    cria_vetor(vetor_3,seed,100000);

    cria_vetor(vetor_4,seed,500000);

    cria_vetor(vetor_5,seed,1000000);

    return 0;
}
