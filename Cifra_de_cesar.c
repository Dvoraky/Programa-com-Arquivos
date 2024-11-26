#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void codificar(char *texto, int chave)
{
    for(int i = 0; texto[i] != '\0'; i++) 
    {
        if(isalpha(texto[i])) 
        {
            char offset = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = ((texto[i] - offset + chave) % 26) + offset;
        }
    }
}

void decodificar(char *texto, int chave) 
{
    for(int i = 0; texto[i] != '\0'; i++)
    {
        if(isalpha(texto[i]))
        {
            char offset = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = ((texto[i] - offset - chave + 26) % 26) + offset;
        }
    }
}

void processarArquivo(FILE *arquivoEntrada, FILE *arquivoSaida, int chave, int modo)
{
    char linha[256];
    while(fgets(linha, sizeof(linha), arquivoEntrada) != NULL)
    {            
        if(modo == 1) codificar(linha, chave);
        else if(modo == 2) decodificar(linha, chave);

        fprintf(arquivoSaida, "%s", linha);
    }
}

int main() 
{
    int chave, modo;
    FILE *arquivoEntrada = fopen("input.txt", "r");
    FILE *arquivoSaida = fopen("output.txt", "w");

    if(arquivoEntrada == NULL || arquivoSaida == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return 0;
    }

    printf("Digite a chave para a cifra de César: ");
    scanf("%d", &chave);
    printf("Escolha o modo (1 para codificar, 2 para decodificar): ");
    scanf("%d", &modo);

    processarArquivo(arquivoEntrada, arquivoSaida, chave, modo);

    printf("Processo concluído. O arquivo foi salvo em output.txt.\n");

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    return 0;
}
