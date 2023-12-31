#include "test.h"
#include "WAKE.h"
#include <stdio.h>

int32_t testOutputMsg(void) {
  int32_t retVal = 0;
  uint8_t array[ARRAY_LENGTH];

  printf("##################\n#Output gen "
         "TESTS#\n##################\n");
  /*Without Addr, Without CRC, Zero length*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = NNZtest(array);

  /*Without Addr, With CRC, Zero length*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = NYZtest(array);

  /*With Addr, With CRC, Zero length*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = YYZtest(array);

  /*With Addr, Without CRC, Zero length*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = YNZtest(array);

  /*With Addr, With CRC, Ten symbols*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = YYTtest(array);

  /*With Addr, With CRC, Fifty symbols*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = YYFtest(array);

  /*With Addr, With CRC, One hundred twenty seven symbols*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = YYHtest(array);

  /*Without Addr, With CRC, One hundred twenty seven symbols*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = NYHtest(array);

  /*With Addr, Without CRC, One hundred twenty seven symbols*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = YNHtest(array);

  /*Without Addr, Without CRC, One hundred twenty seven symbols*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = NNHtest(array);

  /*Overflow test*/
  memset(array, 0x00, ARRAY_LENGTH);
  retVal = Overflow_test(array);

  return retVal;
}

int32_t testInputMsg(void) {
  int32_t retVal = 0;

  printf("#################\n#Input gen "
         "TESTS#\n#################\n");
  /*Without Addr, Without CRC, Zero length*/
  retVal = NNZtestI();
  if (retVal == 0)
    printf("NNZtestI: PASS\n");
  else
    printf("NNZtestI: FAILED with code %d\n", retVal);

  /*Without Addr, With CRC, Zero length*/
  retVal = NYZtestI();
  if (retVal == 0)
    printf("NYZtestI: PASS\n");
  else
    printf("NYZtestI: FAILED with code %d\n", retVal);

  /*With Addr, Without CRC, Zero length*/
  retVal = YNZtestI();
  if (retVal == 0)
    printf("YNZtestI: PASS\n");
  else
    printf("YNZtestI: FAILED with code %d\n", retVal);

  /*With Addr, With CRC, Zero length*/
  retVal = YYZtestI();
  if (retVal == 0)
    printf("YYZtestI: PASS\n");
  else
    printf("YYZtestI: FAILED with code %d\n", retVal);

  /*With Addr, With CRC, Ten symbols*/
  retVal = YYTtestI();
  if (retVal == 0)
    printf("YYTtestI: PASS\n");
  else
    printf("YYTtestI: FAILED with code %d\n", retVal);

  /*With Addr, With CRC, Fifty symbols*/
  retVal = YYFtestI();
  if (retVal == 0)
    printf("YYFtestI: PASS\n");
  else
    printf("YYFtestI: FAILED with code %d\n", retVal);

  /*With Addr, With CRC, One hundred twenty seven symbols*/
  retVal = YYHtestI();
  if (retVal == 0)
    printf("YYHtestI: PASS\n");
  else
    printf("YYHtestI: FAILED with code %d\n", retVal);

  /*Without Addr, With CRC, One hundred twenty seven symbols*/
  retVal = NYHtestI();
  if (retVal == 0)
    printf("NYHtestI: PASS\n");
  else
    printf("NYHtestI: FAILED with code %d\n", retVal);

  /*With Addr, Without CRC, One hundred twenty seven symbols*/
  retVal = YNHtestI();
  if (retVal == 0)
    printf("YNHtestI: PASS\n");
  else
    printf("YNHtestI: FAILED with code %d\n", retVal);

  /*Without Addr, Without CRC, One hundred twenty seven symbols*/
  retVal = NNHtestI();
  if (retVal == 0)
    printf("NNHtestI: PASS\n");
  else
    printf("NNHtestI: FAILED with code %d\n", retVal);

  /*Stiffing parse test*/
  retVal = StiffingParseTest();
  if (retVal == 0)
    printf("Stiffing parse test: PASS\n");
  else
    printf("Stiffing parse test: FAILED with code %d\n", retVal);

  return retVal;
}

/*N(no addres)N(no CRC)Z(Zero length)test*/
int32_t NNZtest(uint8_t *output) {
  uint8_t tempBuf[ZERO_LENGTH];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {0xC0, 0x01, 0x00};

  outputLen = createMsg(0x00, 0x01, tempBuf, ZERO_LENGTH, output, 0, 0);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("NNZtest: FAILED!\n");
      return -1;
    }
  }

  printf("NNZtest: PASS\n");
  return 0;
}

/*N(no addres)Y(CRC)Z(Zero length)test*/
int32_t NYZtest(uint8_t *output) {
  uint8_t tempBuf[ZERO_LENGTH];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {0xC0, 0x01, 0x00, 0xA7};

  outputLen = createMsg(0x00, 0x01, tempBuf, ZERO_LENGTH, output, 0, 1);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("NYZtest: FAILED!\n");
      return -1;
    }
  }

  printf("NYZtest: PASS\n");
  return 0;
}

/*Y(addres)Y(CRC)Z(Zero length)test*/
int32_t YYZtest(uint8_t *output) {
  uint8_t tempBuf[ZERO_LENGTH];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {0xC0, 0xE9, 0x01, 0x00, 0x93};

  outputLen = createMsg(0x69, 0x01, tempBuf, ZERO_LENGTH, output, 1, 1);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("YYZtest: FAILED!\n");
      return -1;
    }
  }

  printf("YYZtest: PASS\n");
  return 0;
}

/*Y(addres)N(no CRC)Z(Zero length)test*/
int32_t YNZtest(uint8_t *output) {
  uint8_t tempBuf[ZERO_LENGTH];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {0xC0, 0xE9, 0x01, 0x00};

  outputLen = createMsg(0x69, 0x01, tempBuf, ZERO_LENGTH, output, 1, 0);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("YNZtest: FAILED!\n");
      return -1;
    }
  }

  printf("YNZtest: PASS\n");
  return 0;
}

/*Y(addres)Y(CRC)T(Ten symbols)test*/
int32_t YYTtest(uint8_t *output) {
  uint8_t tempBuf[TEN_LENGTH] = {0x00, 0x01, 0x02, 0x04, 0x08,
                                 0x10, 0x20, 0x40, 0x80, 0xFF};
  int32_t outputLen = 0;
  uint8_t checkStr[] = {0xC0, 0xE9, 0x01, 0x0A, 0x00, 0x01, 0x02, 0x04,
                        0x08, 0x10, 0x20, 0x40, 0x80, 0xFF, 0xE8};

  outputLen = createMsg(0x69, 0x01, tempBuf, TEN_LENGTH, output, 1, 1);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("YYTtest: FAILED!\n");
      return -1;
    }
  }

  printf("YYTtest: PASS\n");
  return 0;
}

/*Y(addres)Y(CRC)F(Fifty symbols)test*/
int32_t YYFtest(uint8_t *output) {
  uint8_t tempBuf[FIFTY_LENGTH];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {
      0xC0, 0xE9, 0x01, 0x32, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
      0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
      0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
      0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
      0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0xB7};

  for (uint32_t i = 0; i < FIFTY_LENGTH; i++) {
    tempBuf[i] = i;
  }

  outputLen = createMsg(0x69, 0x01, tempBuf, FIFTY_LENGTH, output, 1, 1);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("YYFtest: FAILED!\n");
      return -1;
    }
  }

  printf("YYFtest: PASS\n");
  return 0;
}

/*Y(addres)Y(CRC)H(Hundred+ symbols)test*/
int32_t YYHtest(uint8_t *output) {
  uint8_t tempBuf[HUNDRED_LENGHT];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {
      0xC0, 0xE9, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13,
      0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
      0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
      0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
      0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,
      0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
      0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
      0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
      0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73,
      0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x3A};

  for (uint32_t i = 0; i < HUNDRED_LENGHT; i++) {
    tempBuf[i] = i;
  }

  outputLen = createMsg(0x69, 0x01, tempBuf, HUNDRED_LENGHT, output, 1, 1);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("YYHtest: FAILED!\n");
      return -1;
    }
  }

  printf("YYHtest: PASS\n");
  return 0;
}

/*N(No addres)Y(CRC)H(Hundred+ symbols)test*/
int32_t NYHtest(uint8_t *output) {
  uint8_t tempBuf[HUNDRED_LENGHT];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {
      0xC0, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
      0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
      0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
      0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C,
      0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
      0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44,
      0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
      0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C,
      0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
      0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
      0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x0E};

  for (uint32_t i = 0; i < HUNDRED_LENGHT; i++) {
    tempBuf[i] = i;
  }

  outputLen = createMsg(0x69, 0x01, tempBuf, HUNDRED_LENGHT, output, 0, 1);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("NYHtest: FAILED!\n");
      return -1;
    }
  }

  printf("NYHtest: PASS\n");
  return 0;
}

/*Y(addres)N(No CRC)H(Hundred+ symbols)test*/
int32_t YNHtest(uint8_t *output) {
  uint8_t tempBuf[HUNDRED_LENGHT];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {
      0xC0, 0xE9, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13,
      0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
      0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
      0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
      0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,
      0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
      0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
      0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
      0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73,
      0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  for (uint32_t i = 0; i < HUNDRED_LENGHT; i++) {
    tempBuf[i] = i;
  }

  outputLen = createMsg(0x69, 0x01, tempBuf, HUNDRED_LENGHT, output, 1, 0);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("YNHtest: FAILED!\n");
      return -1;
    }
  }

  printf("YNHtest: PASS\n");
  return 0;
}

/*N(No addres)N(No CRC)H(Hundred+ symbols)test*/
int32_t NNHtest(uint8_t *output) {
  uint8_t tempBuf[HUNDRED_LENGHT];
  int32_t outputLen = 0;
  uint8_t checkStr[] = {
      0xC0, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
      0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
      0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
      0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C,
      0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
      0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44,
      0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
      0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C,
      0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
      0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
      0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  for (uint32_t i = 0; i < HUNDRED_LENGHT; i++) {
    tempBuf[i] = i;
  }

  outputLen = createMsg(0x69, 0x01, tempBuf, HUNDRED_LENGHT, output, 0, 0);

  for (uint32_t i = 0; i < outputLen; i++) {
    if (output[i] != checkStr[i]) {
      printf("NNHtest: FAILED!\n");
      return -1;
    }
  }

  printf("NNHtest: PASS\n");
  return 0;
}

/*Overflow test*/
int32_t Overflow_test(uint8_t *output) {
  uint8_t tempBuf[OVERFLOW_LENGHT];
  int32_t outputLen = 0;

  for (uint32_t i = 0; i < OVERFLOW_LENGHT; i++) {
    tempBuf[i] = i;
  }

  outputLen = createMsg(0x69, 0x01, tempBuf, OVERFLOW_LENGHT, output, 1, 1);

  if (outputLen != -1)
    printf("Overflow test: FAILED\n");
  else
    printf("Overflow test: PASS\n");
  return 0;
}

/*N(No addres)N(No CRC)Z(Zero length)*/
int32_t NNZtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {WAKE_FEND, 0x02, 0x00};
  uint8_t checkStr[] = {};
  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 3, &ret);

  if (ret.address != 0x00)
    retVal = -1;

  if (ret.cmd != 0x02)
    retVal = -2;

  if (ret.matchCRC != 0x02)
    retVal = -3;

  if (ret.len != 0x00)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*N(No addres)Y(CRC)Z(Zero length)*/
int32_t NYZtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {WAKE_FEND, 0x02, 0x00, 0x8A};
  uint8_t checkStr[] = {};
  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 4, &ret);

  if (ret.address != 0x00)
    retVal = -1;

  if (ret.cmd != 0x02)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x00)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)N(No CRC)Z(Zero length)*/
int32_t YNZtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {WAKE_FEND, 0xE9, 0x02, 0x00};
  uint8_t checkStr[] = {};
  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 4, &ret);

  if (ret.address != 0x69)
    retVal = -1;

  if (ret.cmd != 0x02)
    retVal = -2;

  if (ret.matchCRC != 0x02)
    retVal = -3;

  if (ret.len != 0x00)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)Y(CRC)Z(Zero length)*/
int32_t YYZtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {WAKE_FEND, 0xE9, 0x02, 0x00, 0xBE};
  uint8_t checkStr[] = {};
  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 5, &ret);

  if (ret.address != 0x69)
    retVal = -1;

  if (ret.cmd != 0x02)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x00)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)Y(CRC)T(Ten symbols)*/
int32_t YYTtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {WAKE_FEND, 0xE9, 0x01, 0x0A, 0x00, 0x01, 0x02, 0x04,
                        0x08,      0x10, 0x20, 0x40, 0x80, 0xFF, 0xE8};
  uint8_t checkStr[] = {0x00, 0x01, 0x02, 0x04, 0x08,
                        0x10, 0x20, 0x40, 0x80, 0xFF};
  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 15, &ret);

  if (ret.address != 0x69)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x0A)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)Y(CRC)F(Fifty symbols)*/
int32_t YYFtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {
      WAKE_FEND, 0xE9, 0x01, 0x32, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
      0x07,      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
      0x12,      0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
      0x1D,      0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
      0x28,      0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0xB7};

  uint8_t checkStr[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
                        0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
                        0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
                        0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C,
                        0x2D, 0x2E, 0x2F, 0x30, 0x31};

  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 55, &ret);

  if (ret.address != 0x69)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x32)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)Y(CRC)H(Hundred symbols)*/
int32_t YYHtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {
      WAKE_FEND, 0xE9, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
      0x07,      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
      0x12,      0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
      0x1D,      0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
      0x28,      0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
      0x33,      0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
      0x3E,      0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
      0x49,      0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
      0x54,      0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E,
      0x5F,      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
      0x6A,      0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
      0x75,      0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x3A};

  uint8_t checkStr[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
      0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
      0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
      0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
      0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
      0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
      0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 132, &ret);

  if (ret.address != 0x69)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x7F)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*N(No Addres)Y(CRC)H(Hundred symbols)*/
int32_t NYHtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {
      WAKE_FEND, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08,      0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12,
      0x13,      0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
      0x1E,      0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
      0x29,      0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
      0x34,      0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
      0x3F,      0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
      0x4A,      0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
      0x55,      0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60,      0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
      0x6B,      0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
      0x76,      0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x0E};

  uint8_t checkStr[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
      0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
      0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
      0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
      0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
      0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
      0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 131, &ret);

  if (ret.address != 0x00)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x7F)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)N(No CRC)H(Hundred symbols)*/
int32_t YNHtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {
      WAKE_FEND, 0xE9, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
      0x07,      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
      0x12,      0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
      0x1D,      0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
      0x28,      0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
      0x33,      0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
      0x3E,      0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
      0x49,      0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
      0x54,      0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E,
      0x5F,      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
      0x6A,      0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
      0x75,      0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t checkStr[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
      0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
      0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
      0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
      0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
      0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
      0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 131, &ret);

  if (ret.address != 0x69)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x02)
    retVal = -3;

  if (ret.len != 0x7F)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*N(No addres)N(No CRC)H(Hundred symbols)*/
int32_t NNHtestI(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {
      WAKE_FEND, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08,      0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12,
      0x13,      0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
      0x1E,      0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
      0x29,      0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
      0x34,      0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E,
      0x3F,      0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
      0x4A,      0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
      0x55,      0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60,      0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
      0x6B,      0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
      0x76,      0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t checkStr[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
      0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
      0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
      0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53,
      0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
      0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
      0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 130, &ret);

  if (ret.address != 0x00)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x02)
    retVal = -3;

  if (ret.len != 0x7F)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}

/*Y(Addres)Y(CRC)H(Hundred symbols)*/
int32_t StiffingParseTest(void) {
  int32_t retVal = 0;
  uint8_t inputBuf[] = {
      WAKE_FEND, WAKE_FESC,  WAKE_TFEND, 0x01, 0x7F, 0x00, 0x01, 0x02, 0x03,
      0x04,      0x05,       0x06,       0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C,
      0x0D,      0x0E,       0x0F,       0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
      0x16,      0x17,       0x18,       0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
      0x1F,      0x20,       0x21,       0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
      0x28,      0x29,       0x2A,       0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
      0x31,      0x32,       0x33,       0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
      0x3A,      0x3B,       0x3C,       0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42,
      WAKE_FESC, WAKE_TFESC, 0x45,       0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B,
      0x4C,      0x4D,       0x4E,       0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
      0x55,      0x56,       0x57,       0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
      0x5E,      0x5F,       0x60,       0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
      0x67,      0x68,       0x69,       0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
      0x70,      0x71,       0x72,       0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
      0x79,      0x7A,       0x7B,       0x7C, 0x7D, 0x7E, 0x07};

  uint8_t checkStr[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23,
      0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
      0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0xDB, 0x45, 0x46, 0x47, 0x48,
      0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
      0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,
      0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C,
      0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
      0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E};

  uint8_t outputDataBuf[255];
  parsedWAKEString ret = {0x00, 0x00, 0x00, 0x00, outputDataBuf};

  decodeInput((uint8_t *)inputBuf, 133, &ret);

  if (ret.address != 0x40)
    retVal = -1;

  if (ret.cmd != 0x01)
    retVal = -2;

  if (ret.matchCRC != 0x01)
    retVal = -3;

  if (ret.len != 0x7E)
    retVal = -4;

  for (uint32_t i = 0; i < ret.len; i++) {
    if (ret.data[i] != checkStr[i])
      retVal = -5;
  }

  return retVal;
}
