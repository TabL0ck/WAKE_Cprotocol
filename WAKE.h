#ifndef __WAKE_H
#define __WAKE_H

#include <stdint.h>
#include <stdio.h>

#define MAX_RX_LEN 270

/*Control bytes WAKE*/
#define WAKE_FEND 0xC0
#define WAKE_FESC 0xDB
#define WAKE_TFEND 0xDC
#define WAKE_TFESC 0xDD

/*Address*/
#define WAKE_SELF_ADDRESS (0x69 | 0x80)
#define WAKE_BROADCAST 0x00

/*CRC8*/
#define WAKE_CRC8_POLYNOMINAL 0x0131
#define WAKE_CRC8_INIT 0xDE

typedef struct parsedWAKEString_t {
  uint8_t address;
  uint8_t cmd;
  uint32_t len;
  uint8_t matchCRC;
  uint8_t *data;
} parsedWAKEString;

void convertRxDataToSargan(uint8_t *data);
void decodeInput(uint8_t *data, uint32_t len, parsedWAKEString *out);
uint8_t calcCRC8(const uint8_t *data, uint32_t len);
uint32_t createMsg(uint8_t addr, uint8_t cmd, uint8_t *data, uint32_t len,
                   uint8_t *outData, uint8_t hasAddr, uint8_t hasCRC);
uint32_t changeDataToWAKE(uint32_t len, uint8_t *in, uint8_t *out);
#endif
