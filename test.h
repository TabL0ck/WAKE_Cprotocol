#ifndef __TEST_H
#define __TEST_H

#include "WAKE.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_LENGTH 500
#define ZERO_LENGTH 0
#define TEN_LENGTH 10
#define FIFTY_LENGTH 50
#define HUNDRED_LENGHT 127
#define OVERFLOW_LENGHT 254

int32_t testOutputMsg(void);
int32_t NNZtest(uint8_t *output);
int32_t NYZtest(uint8_t *output);
int32_t YYZtest(uint8_t *output);
int32_t YNZtest(uint8_t *output);
int32_t YYTtest(uint8_t *output);
int32_t YYFtest(uint8_t *output);
int32_t YYHtest(uint8_t *output);
int32_t NYHtest(uint8_t *output);
int32_t YNHtest(uint8_t *output);
int32_t NNHtest(uint8_t *output);
int32_t Overflow_test(uint8_t *output);

int32_t testInputMsg(void);
int32_t NNZtestI(void);
int32_t NYZtestI(void);
int32_t YNZtestI(void);
int32_t YYZtestI(void);
int32_t YYTtestI(void);
int32_t YYFtestI(void);
int32_t YYHtestI(void);
int32_t NYHtestI(void);
int32_t YNHtestI(void);
int32_t NNHtestI(void);
int32_t StiffingParseTest(void);

#endif
