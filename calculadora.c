#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

float getValor(char *Str)
{
    if (Str == NULL)
        return NAN;

    float *pilha = (float *)malloc(512 * sizeof(float));
    if (pilha == NULL)
        return NAN;

    int topo = -1;

    char *buf = (char *)malloc(512 * sizeof(char));
    if (buf == NULL)
    {
        free(pilha);
        return NAN;
    }
    strcpy(buf, Str);

    char *tok = strtok(buf, " ");
    while (tok != NULL)
    {
        if (strcmp(tok, "+") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float b = pilha[topo--];
            float a = pilha[topo--];
            pilha[++topo] = a + b;
        }
        else if (strcmp(tok, "-") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float b = pilha[topo--];
            float a = pilha[topo--];
            pilha[++topo] = a - b;
        }
        else if (strcmp(tok, "*") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float b = pilha[topo--];
            float a = pilha[topo--];
            pilha[++topo] = a * b;
        }
        else if (strcmp(tok, "/") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float b = pilha[topo--];
            float a = pilha[topo--];
            if (b == 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            pilha[++topo] = a / b;
        }
        else if (strcmp(tok, "%") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float b = pilha[topo--];
            float a = pilha[topo--];
            if (b == 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            pilha[++topo] = fmodf(a, b);
        }
        else if (strcmp(tok, "^") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float b = pilha[topo--];
            float a = pilha[topo--];
            pilha[++topo] = powf(a, b);
        }
        else if (strcmp(tok, "sen") == 0)
        {
            if (topo < 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float a = pilha[topo--];
            pilha[++topo] = sinf(a * 3.14159265f / 180.0f);
        }
        else if (strcmp(tok, "cos") == 0)
        {
            if (topo < 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float a = pilha[topo--];
            pilha[++topo] = cosf(a * 3.14159265f / 180.0f);
        }
        else if (strcmp(tok, "tg") == 0)
        {
            if (topo < 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float a = pilha[topo--];
            pilha[++topo] = tanf(a * 3.14159265f / 180.0f);
        }
        else if (strcmp(tok, "log") == 0)
        {
            if (topo < 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float a = pilha[topo--];
            if (a <= 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            pilha[++topo] = log10f(a);
        }
        else if (strcmp(tok, "raiz") == 0)
        {
            if (topo < 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            float a = pilha[topo--];
            if (a < 0)
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            pilha[++topo] = sqrtf(a);
        }
        else
        {
            char *fim;
            float v = strtof(tok, &fim);
            if (*fim != '\0')
            {
                free(pilha);
                free(buf);
                return NAN;
            }
            pilha[++topo] = v;
        }

        tok = strtok(NULL, " ");
    }

    if (topo != 0)
    {
        free(pilha);
        free(buf);
        return NAN;
    }

    float resultado = pilha[0];
    free(pilha);
    free(buf);
    return resultado;
}

char *getInFixa(char *Str)
{
    if (Str == NULL)
        return NULL;

    static char resultado[512];

    char **pilha = (char **)malloc(512 * sizeof(char *));
    if (pilha == NULL)
        return NULL;

    int *prioridade = (int *)malloc(512 * sizeof(int));
    if (prioridade == NULL)
    {
        free(pilha);
        return NULL;
    }

    int topo = -1;

    char *buf = (char *)malloc(512 * sizeof(char));
    if (buf == NULL)
    {
        free(pilha);
        free(prioridade);
        return NULL;
    }
    strcpy(buf, Str);

    char *tok = strtok(buf, " ");
    while (tok != NULL)
    {
        if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 ||
            strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0 ||
            strcmp(tok, "%") == 0 || strcmp(tok, "^") == 0)
        {
            if (topo < 1)
            {
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }

            char *dir = (char *)malloc(512 * sizeof(char));
            if (dir == NULL)
            {
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }
            int prioDir = prioridade[topo];
            strcpy(dir, pilha[topo]);
            free(pilha[topo--]);

            char *esq = (char *)malloc(512 * sizeof(char));
            if (esq == NULL)
            {
                free(dir);
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }
            int prioEsq = prioridade[topo];
            strcpy(esq, pilha[topo]);
            free(pilha[topo--]);

            int prioOp = 1;
            if (strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0 || strcmp(tok, "%") == 0)
                prioOp = 2;
            if (strcmp(tok, "^") == 0)
                prioOp = 3;

            char *txtEsq = (char *)malloc(512 * sizeof(char));
            char *txtDir = (char *)malloc(512 * sizeof(char));
            char *tmp = (char *)malloc(512 * sizeof(char));
            if (txtEsq == NULL || txtDir == NULL || tmp == NULL)
            {
                free(esq);
                free(dir);
                free(txtEsq);
                free(txtDir);
                free(tmp);
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }

            if (prioEsq > 0 && prioEsq < prioOp)
                sprintf(txtEsq, "(%s)", esq);
            else
                strcpy(txtEsq, esq);

            if (prioDir > 0 && prioDir < prioOp)
                sprintf(txtDir, "(%s)", dir);
            else if (prioDir > 0 && prioDir == prioOp &&
                     (strcmp(tok, "-") == 0 || strcmp(tok, "/") == 0 || strcmp(tok, "%") == 0))
                sprintf(txtDir, "(%s)", dir);
            else
                strcpy(txtDir, dir);

            sprintf(tmp, "%s%s%s", txtEsq, tok, txtDir);
            free(esq);
            free(dir);
            free(txtEsq);
            free(txtDir);

            pilha[++topo] = tmp;
            prioridade[topo] = prioOp;
        }
        else if (strcmp(tok, "sen") == 0 || strcmp(tok, "cos") == 0 ||
                 strcmp(tok, "tg") == 0 || strcmp(tok, "log") == 0 ||
                 strcmp(tok, "raiz") == 0)
        {
            if (topo < 0)
            {
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }

            char *esq = (char *)malloc(512 * sizeof(char));
            char *tmp = (char *)malloc(512 * sizeof(char));
            if (esq == NULL || tmp == NULL)
            {
                free(esq);
                free(tmp);
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }

            strcpy(esq, pilha[topo]);
            free(pilha[topo--]);

            if (esq[0] == '(')
                sprintf(tmp, "%s%s", tok, esq);
            else
                sprintf(tmp, "%s(%s)", tok, esq);

            free(esq);

            pilha[++topo] = tmp;
            prioridade[topo] = 0;
        }
        else
        {
            char *fim;
            strtof(tok, &fim);
            if (*fim != '\0')
            {
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }

            char *tmp = (char *)malloc(512 * sizeof(char));
            if (tmp == NULL)
            {
                free(pilha);
                free(prioridade);
                free(buf);
                return NULL;
            }
            strcpy(tmp, tok);
            pilha[++topo] = tmp;
            prioridade[topo] = 0;
        }

        tok = strtok(NULL, " ");
    }

    if (topo != 0)
    {
        free(pilha);
        free(prioridade);
        free(buf);
        return NULL;
    }

    strcpy(resultado, pilha[0]);
    free(pilha[0]);
    free(pilha);
    free(prioridade);
    free(buf);
    return resultado;
}
