#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Declaração das funções
float calcular_salario_bruto(float salarioMensal, float horasMensais);
float calcular_valeTransporte(float salarioMensal, float custoTransporte);
float calcular_salario_liquido(float salarioMensal, float valeTransporte);
float calcular_inss(float salarioMensal); // Função para calcular o INSS
float ler_float();


int main() {   
    setlocale(LC_ALL,"Portuguese_Brazil");
    char continuar; 


    do {
        float salarioMensal, horasMensais, custoTransporte;

        printf("Digite o valor do seu salario mensal:\n");
        salarioMensal = ler_float(); // Usa a função personalizada

        printf("Digite a quantidade de horas trabalhadas por mês:\n"); 
        horasMensais = ler_float(); // Usa a função personalizada

        printf("Digite o custo total do transporte no mês:\n");
        custoTransporte = ler_float(); // Usa a função personalizada

        // Validação das entradas
        if (salarioMensal <= 0 || horasMensais <= 0 || custoTransporte < 0) {
            printf("\nErro: Todos os valores devem ser positivos. O custo do transporte pode ser zero.\n\n");
            continue; 
        }
        
        // Chamadas das funções
        float valorHora = calcular_salario_bruto(salarioMensal, horasMensais); 
        float valeTransporte = calcular_valeTransporte(salarioMensal, custoTransporte);
        float inssDesconto = calcular_inss(salarioMensal); 
        float salarioLiquido = calcular_salario_liquido(salarioMensal, valeTransporte + inssDesconto); 
        
        // Imprimir resultados
        printf("O valor da hora trabalhada é: R$ %.2f\n", valorHora);
        printf("O salário bruto deste mês é: R$ %.2f\n", salarioMensal);
        printf("Desconto do vale transporte: R$ %.2f\n", valeTransporte);
        printf("Desconto do INSS: R$ %.2f\n", inssDesconto);
        printf("Salário líquido: R$ %.2f\n", salarioLiquido);
        
        getchar(); 
        
        printf("\nDeseja fazer outro cálculo? (S/N): ");
        scanf(" %c", &continuar); 
        
    } while(continuar == 'S' || continuar == 's');

    printf("\nObrigada por usar o programa. Até a próxima!\n");
    return 0;
}


// Sua função ler_float
float ler_float() {
    char entrada[100];
    char *ptr;

    // Lê a entrada como string
    scanf("%s", entrada);

    // Substitui vírgulas por pontos
    for (ptr = entrada; *ptr != '\0'; ++ptr) {
        if (*ptr == ',') {
            *ptr = '.';
        }
    }

    // Converte a string para float
    return strtof(entrada, NULL);
}


// Funções auxiliares 
float calcular_salario_bruto(float salarioMensal, float horasMensais) {
    return salarioMensal / horasMensais; // Divisão pelo total de horas trabalhadas no mês
}

float calcular_valeTransporte(float salarioMensal, float custoTransporte) {
    float descontoMaximo = salarioMensal * 0.06;
    return (custoTransporte < descontoMaximo) ? custoTransporte : descontoMaximo;
}

float calcular_salario_liquido(float salarioMensal, float descontosTotais) {
    return salarioMensal - descontosTotais; // Subtrai todos os descontos (vale transporte + INSS)
}

float calcular_inss(float salarioMensal) {
    float salarioMinimo = 1518.00; // Salário mínimo de 2025
    float descontoInss = 0.00;
    if(salarioMensal < 1518.00){
        descontoInss =  0.075;
    } else if(salarioMensal > 1518.00 && salarioMensal <=  2793.88) {
        descontoInss =  0.09;
    } else if(salarioMensal > 2793.88 && salarioMensal <=  4190.83) {
        descontoInss =  0.12;
    } else if(salarioMensal > 4190.83 && salarioMensal <=  8157.41) {
        descontoInss =  0.14;
    } else if(salarioMensal > 8157.41 && salarioMensal <=  13969.49) {
        descontoInss =  0.145;
    } else if(salarioMensal > 13969.49 && salarioMensal <=  27938.95) {
        descontoInss =  0.165;
    } else if(salarioMensal >  27938.95 && salarioMensal <=  54480.97) {
        descontoInss =  0.19;
    } else if(salarioMensal > 54480.97) {
        descontoInss =  0.22;
    }
    
    float descontoInss = salarioMensal * 0.075; // 7,5% sobre o salário mensal
    float maxInss = 951.63; // Desconto máximo

    // Se o salário for menor ou igual ao salário mínimo, aplica 7,5% do salário
    if (salarioMensal <= salarioMinimo) {
        return descontoInss;
    }
    // Se for maior que o salário mínimo, aplica o desconto máximo
    return (descontoInss > maxInss) ? maxInss : descontoInss;
}
