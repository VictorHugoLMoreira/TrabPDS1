//Exemplo de entrada:

//Digite o número de pontos (n): 3
//Digite os valores de x e y separados por espaço:
//Ponto 1: 1 2
//Ponto 2: 2 3
//Ponto 3: 3 5
//Digite um novo valor de x para prever y: 4


#include <stdio.h>
#include <math.h>

// Função para calcular b1 (inclinação)
double calcular_b1(int n, double x[], double y[], double sumX, double sumY, double sumXY, double sumX2) {
    return (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
}

// Função para calcular b0 (intercepto)
double calcular_b0(int n, double sumX, double sumY, double b1) {
    return (sumY - b1 * sumX) / n;
}

// Função para calcular o coeficiente de determinação (R^2)
double calcular_r2(int n, double x[], double y[], double b0, double b1) {
    double y_mean = 0, ssr = 0, sst = 0;

    // Calcular a média de y
    for (int i = 0; i < n; i++) {
        y_mean += y[i];
    }
    y_mean /= n;

    // Calcular SSR e SST
    for (int i = 0; i < n; i++) {
        double y_pred = b0 + b1 * x[i]; // Valor previsto
        ssr += (y[i] - y_pred) * (y[i] - y_pred); // Soma dos quadrados dos resíduos
        sst += (y[i] - y_mean) * (y[i] - y_mean); // Soma total dos quadrados
    }

    return 1 - (ssr / sst);
}

// Função para fazer a previsão
double prever_y(double b0, double b1, double x) {
    return b0 + b1 * x;
}

int main() {
    int n, i;
    printf("Digite o número de pontos (n): ");
    scanf("%d", &n);

    double x[n], y[n];
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    // Entrada dos dados
    printf("Digite os valores de x e y separados por espaço:\n");
    for (i = 0; i < n; i++) {
        printf("Ponto %d: ", i + 1);
        scanf("%lf %lf", &x[i], &y[i]);

        // Cálculo das somas necessárias
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    // Calcular os coeficientes usando funções
    double b1 = calcular_b1(n, x, y, sumX, sumY, sumXY, sumX2);
    double b0 = calcular_b0(n, sumX, sumY, b1);

    printf("\nCoeficientes da regressão linear:\n");
    printf("b0 (intercepto): %.2lf\n", b0);
    printf("b1 (inclinação): %.2lf\n", b1);

    // Calcular R²
    double r2 = calcular_r2(n, x, y, b0, b1);
    printf("\nCoeficiente de determinação (R²): %.2lf\n", r2);

    // Previsão para novos valores de x
    double x_new;
    printf("\nDigite um novo valor de x para prever y: ");
    scanf("%lf", &x_new);

    double y_pred = prever_y(b0, b1, x_new);
    printf("Para x = %.2lf, a previsão de y é: %.2lf\n", x_new, y_pred);

    return 0;
}