#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char linha[100], curso[50], curso_maior_taxa[50], taxa[10];
    double maior_taxa = 0, taxa_numerica;
    int contador_de_virgula, k, tamanho_curso, ano = 0;

    FILE *arq = fopen("Arquivo.csv", "r"); // Abre o arquivo e armazena ele em "arq"

    if(arq == NULL) // Se o arquivo não existir irá dar esse erro
    {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    while(1) // Aqui serve para questionar o ano que o usuário quer escolher
    {
        printf("Qual ano gostaria de analisar a maior taxa de sucesso? (2022, 2023, 2024)\n");
        scanf("%d", &ano);
        if(ano < 2022 || ano > 2024) printf("Insira uma das opções válidas.\n");
        else break;
    }

    while(fgets(linha, 100, arq) != NULL) // Lê as linhas e enquanto conseguir ler o loop continua
    {
        contador_de_virgula = 0; tamanho_curso = 0; k = 0;
        memset(taxa, 0, sizeof(taxa)); // Limpa o array antes de usá-lo trocando todas os valores por 0

        for(int i = 0; linha[i] != '\0'; i++) // "\0" é o caractere que indica o final da linha
        {
            if(linha[i] == ',') // Aumenta o contador
            {
                contador_de_virgula++;
            }
            else if(contador_de_virgula == 0) // Armazena o nome do curso
            {
                curso[tamanho_curso] = linha[i];
                tamanho_curso++;
            }
            else if(contador_de_virgula == ano - 2021 && linha[i] != '%') // Armazena a taxa de sucesso do ano escolhido
            {
                taxa[k] = linha[i];
                k++;
            }
        }

        curso[tamanho_curso] = '\0'; // \0 é o caractere que indica o final da linha
        taxa_numerica = atof(taxa);  // Converte a taxa para número

        if(taxa_numerica > maior_taxa)
        {
            maior_taxa = taxa_numerica;
            strcpy(curso_maior_taxa, curso); // Copia o nome do curso com a maior taxa
        }
    }

    printf("O curso %s é o que apresenta a maior taxa sendo ela %.2f%%.\n", curso_maior_taxa, maior_taxa);

    fclose(arq);

    return 0;   
}
