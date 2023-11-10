#include "WAKE.h"

static uint8_t checkStaffingRX(uint8_t firstByte, uint8_t secondByte) {
  uint8_t retVal;

  if (firstByte == WAKE_FESC) {
    if (secondByte == WAKE_TFEND)
      retVal = WAKE_FEND;
    else if (secondByte == WAKE_TFESC)
      retVal = WAKE_FESC;
  } else {
    retVal = firstByte;
  }

  return retVal;
}

static void staffing(uint8_t data, uint8_t *out) {
  out[0] = 0x00;
  out[1] = 0x00;

  if (data == WAKE_FEND) {
    out[0] = WAKE_FESC;
    out[1] = WAKE_TFEND;
  } else if (data == WAKE_FESC) {
    out[0] = WAKE_FESC;
    out[1] = WAKE_TFESC;
  } else {
    out[0] = data;
    out[1] = 0x00;
  }
}

void decodeInput(uint8_t *data, uint32_t len, parsedWAKEString *out) {
  uint32_t idx = 0;
  uint8_t correctCRC;
  uint8_t realCRC;

  /*Проверка начала пакета*/
  if (data[idx++] != WAKE_FEND)
    return;

  /*Проверка адреса*/
  if (data[idx] & 0x80) {
    out->address = checkStaffingRX(data[idx], data[idx + 1]);
    if ((out->address == WAKE_FEND) || (out->address == WAKE_FESC))
      idx++;
    idx++;
    out->address &= 0x7F;
  }

  /*Тип команды*/
  out->cmd = data[idx++];

  /*Длина пакета*/
  out->len = checkStaffingRX(data[idx], data[idx + 1]);
  if ((out->len == WAKE_FEND) || (out->len == WAKE_FESC))
    idx++;
  idx++;

  /*Расчет CRC8*/
  if (idx + out->len < len) {
    correctCRC = calcCRC8(data, idx + out->len);
    realCRC = checkStaffingRX(data[idx + out->len], data[idx + out->len + 1]);
    if (correctCRC != realCRC) {
      out->matchCRC = 0;
    } else {
      out->matchCRC = 1;
    }
  } else {
    out->matchCRC = 2;
  }

  /*Get Data*/
  for (uint32_t i = idx, j = 0; i < len; i++, j++) {
    out->data[j] = checkStaffingRX(data[i], data[i + 1]);
    if ((out->data[j] == WAKE_FEND) || (out->data[j] == WAKE_FESC)) {
      out->len--;
      i++;
    }
  }
}

uint32_t createMsg(uint8_t addr, uint8_t cmd, uint8_t *data, uint32_t len,
                   uint8_t *outData, uint8_t hasAddr, uint8_t hasCRC) {
  uint8_t staff[2] = {0x00, 0x00};
  uint8_t tempData[255];
  uint32_t newLen;
  uint32_t txLen = 0;

  if (len > 255)
    return -1;

  newLen = changeDataToWAKE(len, data, tempData);

  if (newLen > 255)
    return -1;

  /*Start*/
  outData[txLen++] = WAKE_FEND;

  /*Address*/
  if (hasAddr > 0) {
    staffing((addr | 0x80), (uint8_t *)staff);
    outData[txLen++] = staff[0];
    if (staff[1] != 0x00)
      outData[txLen++] = staff[1];
  }

  /*CMD type*/
  outData[txLen++] = (cmd & 0x7F);

  /*Length*/
  staffing(newLen, (uint8_t *)staff);
  outData[txLen++] = staff[0];
  if (staff[1] != 0x00)
    outData[txLen++] = staff[1];

  /*Data*/
  for (uint32_t i = 0; i < newLen; i++)
    outData[txLen++] = tempData[i];

  /*CRC8*/
  if (hasCRC > 0) {
    staffing(calcCRC8(outData, txLen), staff);
    outData[txLen++] = staff[0];
    if (staff[1] != 0x00)
      outData[txLen++] = staff[1];
  }

  return txLen;
}

uint32_t changeDataToWAKE(uint32_t len, uint8_t *in, uint8_t *out) {
  uint8_t staff[2] = {0x00, 0x00};
  uint32_t newLen = 0;

  for (uint32_t i = 0; i < len; i++, newLen++) {
    if (newLen > 255)
      return 256;

    staffing(in[i], (uint8_t *)staff);
    out[newLen] = staff[0];
    if (staff[1] != 0x00)
      out[++newLen] = staff[1];
  }

  return newLen;
}

uint8_t calcCRC8(const uint8_t *data, uint32_t len) {
  uint8_t retVal = WAKE_CRC8_INIT;

  for (uint32_t i = 0; i < len; ++i) {
    retVal ^= data[i];
    for (uint8_t bit = 8; bit > 0; --bit) {
      retVal = (retVal & 0x80) ? ((retVal << 1) ^ WAKE_CRC8_POLYNOMINAL)
                               : (retVal << 1);
    }
  }

  return retVal;
}
