# 🧮 Avaliador de Expressões Numéricas

Um programa em C capaz de converter e avaliar expressões matemáticas escritas em notação pós-fixa (RPN), utilizando pilhas como estrutura de dados principal.

## O que ele faz?

Você fornece uma expressão em notação pós-fixa e o programa:

- Converte a expressão para a forma infixa;
- Calcula seu valor numérico;
- Aplica operações aritméticas e funções matemáticas;
- Detecta expressões inválidas.

## Operações suportadas

### Operadores básicos

| Operador | Operação |
|-----------|-----------|
| + | Soma |
| - | Subtração |
| * | Multiplicação |
| / | Divisão |
| % | Resto da divisão |
| ^ | Potenciação |

### Funções matemáticas

| Função | Operação |
|---------|---------|
| raiz | Raiz quadrada |
| sen | Seno |
| cos | Cosseno |
| tg | Tangente |
| log | Logaritmo decimal |

> As funções trigonométricas utilizam ângulos em graus.

## Exemplos

### Entrada (Pós-fixa)

```text
3 4 + 5 *
```

### Saída (Infixa)

```text
(3+4)*5
```

### Resultado

```text
35
```

---

### Entrada (Pós-fixa)

```text
45 60 + 30 cos *
```

### Saída (Infixa)

```text
(45+60)*cos(30)
```

### Resultado

```text
90.93
```

## O que o programa retorna?

- Expressão convertida para forma infixa;
- Valor numérico da expressão;
- Mensagens de erro para entradas inválidas.

## Como compilar e executar?

```bash
gcc implementacao.c main.c -o calculadora.exe
./calculadora.exe
```

## Conceitos utilizados

- Pilhas (Stack)
- Notação Pós-fixa (RPN)
- Notação Infixa
- Expressões Matemáticas
- Estruturas de Dados em C