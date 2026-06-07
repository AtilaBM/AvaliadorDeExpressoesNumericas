#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

int acertos = 0;
int total = 0;

void testar_valor(char *posfixa, float esperado, float tolerancia)
{
    char buf[512];
    strcpy(buf, posfixa);
    float obtido = getValor(buf);

    total++;
    if (!isnan(obtido) && fabsf(obtido - esperado) <= tolerancia)
    {
        acertos++;
        printf("[OK] getValor(\"%s\")\n", posfixa);
        printf("     Obtido  : %.4f\n", obtido);
        printf("     Esperado: %.4f\n\n", esperado);
    }
    else
    {
        printf("[ERRO] getValor(\"%s\")\n", posfixa);
        printf("     Obtido  : %.4f\n", isnan(obtido) ? 0.0f : obtido);
        printf("     Esperado: %.4f\n\n", esperado);
    }
}

void testar_valor_invalido(char *posfixa)
{
    char buf[512];
    strcpy(buf, posfixa);
    float obtido = getValor(buf);

    total++;
    if (isnan(obtido))
    {
        acertos++;
        printf("[OK] getValor(\"%s\") retorna NAN\n", posfixa);
        printf("     Obtido  : NAN\n");
        printf("     Esperado: NAN\n\n");
    }
    else
    {
        printf("[ERRO] getValor(\"%s\") deveria retornar NAN\n", posfixa);
        printf("     Obtido  : %.4f\n", obtido);
        printf("     Esperado: NAN\n\n");
    }
}

void testar_infixa(char *posfixa, char *esperado)
{
    char buf[512];
    strcpy(buf, posfixa);
    char *obtido = getInFixa(buf);

    total++;
    if (obtido != NULL && strcmp(obtido, esperado) == 0)
    {
        acertos++;
        printf("[OK] getInFixa(\"%s\")\n", posfixa);
        printf("     Obtido  : %s\n", obtido);
        printf("     Esperado: %s\n\n", esperado);
    }
    else
    {
        printf("[ERRO] getInFixa(\"%s\")\n", posfixa);
        printf("     Obtido  : %s\n", obtido == NULL ? "NULL" : obtido);
        printf("     Esperado: %s\n\n", esperado);
    }
}

void testar_infixa_invalida(char *posfixa)
{
    char buf[512];
    strcpy(buf, posfixa);
    char *obtido = getInFixa(buf);

    total++;
    if (obtido == NULL)
    {
        acertos++;
        printf("[OK] getInFixa(\"%s\") retorna NULL\n", posfixa);
        printf("     Obtido  : NULL\n");
        printf("     Esperado: NULL\n\n");
    }
    else
    {
        printf("[ERRO] getInFixa(\"%s\") deveria retornar NULL\n", posfixa);
        printf("     Obtido  : %s\n", obtido);
        printf("     Esperado: NULL\n\n");
    }
}

int main(void)
{
    printf("=====================================\n");
    printf(" TESTES EXAUSTIVOS - CALCULADORA     \n");
    printf("=====================================\n\n");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes do enunciado - getValor\n");
    printf("=====================================\n\n");

    testar_valor("3 4 + 5 *", 35.0f, 0.001f);
    testar_valor("7 2 * 4 +", 18.0f, 0.001f);
    testar_valor("8 5 2 4 + * +", 38.0f, 0.001f);
    testar_valor("6 2 / 3 + 4 *", 24.0f, 0.001f);
    testar_valor("9 5 2 8 * 4 + * +", 109.0f, 0.001f);
    testar_valor("2 3 + log 5 /", 0.14f, 0.001f);
    testar_valor("10 log 3 ^ 2 +", 3.0f, 0.001f);
    testar_valor("45 60 + 30 cos *", 90.93f, 0.01f);
    testar_valor("0.5 45 sen 2 ^ +", 1.0f, 0.001f);

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes do enunciado - getInFixa\n");
    printf("=====================================\n\n");

    testar_infixa("3 4 + 5 *", "(3+4)*5");
    testar_infixa("7 2 * 4 +", "7*2+4");
    testar_infixa("8 5 2 4 + * +", "8+5*(2+4)");
    testar_infixa("6 2 / 3 + 4 *", "(6/2+3)*4");
    testar_infixa("9 5 2 8 * 4 + * +", "9+5*(2*8+4)");
    testar_infixa("2 3 + log 5 /", "log(2+3)/5");
    testar_infixa("10 log 3 ^ 2 +", "log(10)^3+2");
    testar_infixa("45 60 + 30 cos *", "(45+60)*cos(30)");
    testar_infixa("0.5 45 sen 2 ^ +", "0.5+sen(45)^2");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de subtracao e divisao\n");
    printf("=====================================\n\n");

    testar_valor("10 3 -", 7.0f, 0.001f);
    testar_valor("20 4 /", 5.0f, 0.001f);
    testar_valor("15 7 -", 8.0f, 0.001f);
    testar_valor("100 4 /", 25.0f, 0.001f);
    testar_infixa("10 3 -", "10-3");
    testar_infixa("20 4 /", "20/4");
    testar_infixa("15 7 -", "15-7");
    testar_infixa("100 4 /", "100/4");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de potenciacao e modulo\n");
    printf("=====================================\n\n");

    testar_valor("2 8 ^", 256.0f, 0.001f);
    testar_valor("3 3 ^", 27.0f, 0.001f);
    testar_valor("10 3 %", 1.0f, 0.001f);
    testar_valor("7 3 %", 1.0f, 0.001f);
    testar_infixa("2 8 ^", "2^8");
    testar_infixa("3 3 ^", "3^3");
    testar_infixa("10 3 %", "10%3");
    testar_infixa("7 3 %", "7%3");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de funcoes trigonometricas\n");
    printf("=====================================\n\n");

    testar_valor("0 sen", 0.0f, 0.001f);
    testar_valor("90 sen", 1.0f, 0.001f);
    testar_valor("0 cos", 1.0f, 0.001f);
    testar_valor("90 cos", 0.0f, 0.001f);
    testar_valor("45 tg", 1.0f, 0.001f);
    testar_valor("0 tg", 0.0f, 0.001f);
    testar_infixa("0 sen", "sen(0)");
    testar_infixa("90 sen", "sen(90)");
    testar_infixa("0 cos", "cos(0)");
    testar_infixa("90 cos", "cos(90)");
    testar_infixa("45 tg", "tg(45)");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de raiz e logaritmo\n");
    printf("=====================================\n\n");

    testar_valor("4 raiz", 2.0f, 0.001f);
    testar_valor("9 raiz", 3.0f, 0.001f);
    testar_valor("25 raiz", 5.0f, 0.001f);
    testar_valor("100 raiz", 10.0f, 0.001f);
    testar_valor("10 log", 1.0f, 0.001f);
    testar_valor("100 log", 2.0f, 0.001f);
    testar_valor("1000 log", 3.0f, 0.001f);
    testar_valor("1 log", 0.0f, 0.001f);
    testar_infixa("4 raiz", "raiz(4)");
    testar_infixa("25 raiz", "raiz(25)");
    testar_infixa("10 log", "log(10)");
    testar_infixa("100 log", "log(100)");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de expressoes compostas\n");
    printf("=====================================\n\n");

    testar_valor("2 3 + 4 *", 20.0f, 0.001f);
    testar_valor("5 1 2 + 4 * + 3 -", 14.0f, 0.001f);
    testar_valor("2 3 4 * +", 14.0f, 0.001f);
    testar_valor("4 2 - 3 *", 6.0f, 0.001f);
    testar_infixa("2 3 + 4 *", "(2+3)*4");
    testar_infixa("5 1 2 + 4 * + 3 -", "5+(1+2)*4-3");
    testar_infixa("2 3 4 * +", "2+3*4");
    testar_infixa("4 2 - 3 *", "(4-2)*3");
    testar_valor("6 2 3 + *", 30.0f, 0.001f);
    testar_valor("10 2 8 - *", -60.0f, 0.001f);
    testar_infixa("6 2 3 + *", "6*(2+3)");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes com numero unico\n");
    printf("=====================================\n\n");

    testar_valor("0", 0.0f, 0.001f);
    testar_valor("1", 1.0f, 0.001f);
    testar_valor("42", 42.0f, 0.001f);
    testar_valor("3.14", 3.14f, 0.001f);
    testar_valor("0.5", 0.5f, 0.001f);
    testar_infixa("0", "0");
    testar_infixa("1", "1");
    testar_infixa("42", "42");
    testar_infixa("3.14", "3.14");
    testar_infixa("0.5", "0.5");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes com funcoes sobre expressoes\n");
    printf("=====================================\n\n");

    testar_valor("2 2 + raiz", 2.0f, 0.001f);
    testar_valor("3 1 + log", 0.602f, 0.001f);
    testar_valor("1 1 + sen", 0.035f, 0.001f);
    testar_infixa("2 2 + raiz", "raiz(2+2)");
    testar_infixa("3 1 + log", "log(3+1)");
    testar_infixa("1 1 + sen", "sen(1+1)");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de entradas invalidas - getValor\n");
    printf("=====================================\n\n");

    testar_valor_invalido("1 0 /");
    testar_valor_invalido("5 0 /");
    testar_valor_invalido("1 0 %");
    testar_valor_invalido("0 log");
    testar_valor_invalido("-1 log");
    testar_valor_invalido("-4 raiz");
    testar_valor_invalido("1 +");
    testar_valor_invalido("+");
    testar_valor_invalido("1 2 3 +");
    testar_valor_invalido("1 2 @");
    testar_valor_invalido("abc");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de entradas invalidas - getInFixa\n");
    printf("=====================================\n\n");

    testar_infixa_invalida("1 2 @");
    testar_infixa_invalida("1 +");
    testar_infixa_invalida("+");
    testar_infixa_invalida("sen");
    testar_infixa_invalida("cos");
    testar_infixa_invalida("log");
    testar_infixa_invalida("raiz");
    testar_infixa_invalida("abc");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de parametros NULL\n");
    printf("=====================================\n\n");

    float vNull = getValor(NULL);
    total++;
    if (isnan(vNull))
    {
        acertos++;
        printf("[OK] getValor(NULL)\n");
        printf("     Obtido  : NAN\n");
        printf("     Esperado: NAN\n\n");
    }
    else
    {
        printf("[ERRO] getValor(NULL)\n");
        printf("     Obtido  : nao NAN\n");
        printf("     Esperado: NAN\n\n");
    }

    char *rNull = getInFixa(NULL);
    total++;
    if (rNull == NULL)
    {
        acertos++;
        printf("[OK] getInFixa(NULL)\n");
        printf("     Obtido  : NULL\n");
        printf("     Esperado: NULL\n\n");
    }
    else
    {
        printf("[ERRO] getInFixa(NULL)\n");
        printf("     Obtido  : nao NULL\n");
        printf("     Esperado: NULL\n\n");
    }

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de associatividade e precedencia\n");
    printf("=====================================\n\n");

    /* Subtracao encadeada */

    testar_valor("10 3 - 2 -", 5.0f, 0.001f);
    testar_infixa("10 3 - 2 -", "10-3-2");

    testar_valor("10 3 2 - -", 9.0f, 0.001f);
    testar_infixa("10 3 2 - -", "10-(3-2)");

    /* Divisao encadeada */

    testar_valor("20 4 / 2 /", 2.5f, 0.001f);
    testar_infixa("20 4 / 2 /", "20/4/2");

    testar_valor("20 4 2 / /", 10.0f, 0.001f);
    testar_infixa("20 4 2 / /", "20/(4/2)");

    /* Potenciacao */

    testar_valor("2 3 ^ 2 ^", 64.0f, 0.001f);
    testar_infixa("2 3 ^ 2 ^", "2^3^2");

    testar_valor("2 3 2 ^ ^", 512.0f, 0.001f);
    testar_infixa("2 3 2 ^ ^", "2^(3^2)");

    /* Modulo encadeado */

    testar_valor("20 7 % 3 %", 0.0f, 0.001f);
    testar_infixa("20 7 % 3 %", "20%7%3");

    testar_valor("20 7 3 % %", 0.0f, 0.001f);
    testar_infixa("20 7 3 % %", "20%(7%3)");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes de funcoes aninhadas\n");
    printf("=====================================\n\n");

    testar_valor("2 2 + raiz log", 0.30103f, 0.001f);
    testar_infixa("2 2 + raiz log", "log(raiz(2+2))");

    testar_valor("90 sen log", 0.0f, 0.001f);
    testar_infixa("90 sen log", "log(sen(90))");

    testar_valor("100 log raiz", 1.4142f, 0.001f);
    testar_infixa("100 log raiz", "raiz(log(100))");

    /* ================================================= */
    printf("=====================================\n");
    printf("Testes com numeros negativos\n");
    printf("=====================================\n\n");

    testar_valor("-5", -5.0f, 0.001f);
    testar_infixa("-5", "-5");

    testar_valor("-5 -3 *", 15.0f, 0.001f);
    testar_infixa("-5 -3 *", "-5*-3");

    testar_valor("-5 2 +", -3.0f, 0.001f);
    testar_infixa("-5 2 +", "-5+2");

    testar_valor("-5 -3 -", -2.0f, 0.001f);
    testar_infixa("-5 -3 -", "-5--3");

    /* ================================================= */
    printf("=====================================\n");
    printf("TOTAL DE TESTES : %d\n", total);
    printf("ACERTOS         : %d\n", acertos);
    printf("PERCENTUAL      : %.2f%%\n", (float)acertos / total * 100.0f);
    printf("=====================================\n");

    return 0;
}