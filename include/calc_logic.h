#ifndef CALC_LOGIC_H
#define CALC_LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUF_SIZE 12

typedef struct {
    double  operandA;
    double  operandB;
    char    op;
    char    inputBuf[INPUT_BUF_SIZE];
    uint8_t inputLen;
    bool    freshResult;
    bool    errorState;
    bool    hasDecimal;
} CalcState;

extern CalcState calc;

static inline double Calc_Evaluate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) { calc.errorState = true; return 0.0; }
            return a / b;
    }
    return a;
}

static inline void Calc_FormatNumber(double val, char *buf, uint8_t maxLen) {
    if (isnan(val) || isinf(val)) {
        strncpy(buf, "ERR", maxLen);
        return;
    }
    if (fabs(val) >= 1e10) {
        strncpy(buf, "OVERFLOW", maxLen);
        return;
    }
    if (val == (double)(long long)val && fabs(val) < 1e10) {
        snprintf(buf, maxLen, "%lld", (long long)val);
        return;
    }
    snprintf(buf, maxLen, "%.6f", val);
    char *dot = strchr(buf, '.');
    if (dot) {
        char *end = buf + strlen(buf) - 1;
        while (end > dot && *end == '0') *end-- = '\0';
        if (*end == '.')                 *end   = '\0';
    }
}

#endif