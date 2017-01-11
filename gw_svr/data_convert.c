#include <stdio.h>
#include <string.h>
#include "data_convert.h"

int strToHex(const char *ch, char *hex);
int hexToStr(const char *hex, char *ch);
int hexCharToValue(const char ch);
char valueToHexCh(const int value);
int hexChartoByte(const char *hex,char *byte);
unsigned char ChartoAscii(const unsigned char cha);

int strToHex(const char *ch, char *hex)
{
  int high,low;
  int tmp = 0;
  if(ch == NULL || hex == NULL){
    return -1;
  }

  if(strlen(ch) == 0){
    return -2;
  }

  while(*ch){
    tmp = (int)*ch;
    high = tmp >> 4;
    low = tmp & 15;
    *hex++ = valueToHexCh(high); //先写高字节
    *hex++ = valueToHexCh(low); //其次写低字节
    ch++;
  }
  *hex = '\0';
  return 0;
}

int hexToStr(const char *hex, char *ch)
{
  int high,low;
  int tmp = 0;
  if(hex == NULL || ch == NULL){
    return -1;
  }

  if(strlen(hex) %2 == 1){
    return -2;
  }

  while(*hex){
    high = hexCharToValue(*hex);
    if(high < 0){
      *ch = '\0';
      return -3;
    }
    hex++; //指针移动到下一个字符上
    low = hexCharToValue(*hex);
    if(low < 0){
      *ch = '\0';
      return -3;
    }
    tmp = (high << 4) + low;
    *ch++ = (char)tmp;
    hex++;
  }
  *ch = '\0';
  return 0;
}

int hexCharToValue(const char ch){
  int result = 0;
  //获取16进制的高字节位数据
  if(ch >= '0' && ch <= '9'){
    result = (int)(ch - '0');
  }
  else if(ch >= 'a' && ch <= 'z'){
    result = (int)(ch - 'a') + 10;
  }
  else if(ch >= 'A' && ch <= 'Z'){
    result = (int)(ch - 'A') + 10;
  }
  else{
    result = -1;
  }
  return result;
}

char valueToHexCh(const int value)
{
  char result = '\0';
  if(value >= 0 && value <= 9){
    result = (char)(value + 48); //48为ascii编码的‘0’字符编码值
  }
  else if(value >= 10 && value <= 15){
    result = (char)(value - 10 + 65); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值
  }
  else{
    ;
  }

  return result;
}

int hexChartoByte(const char *hex, char *byte)
{
    int i,n = 0;
    for(i = 0; hex[i]; i += 2)
    {
        if(hex[i] >= 'A' && hex[i] <= 'F')
            byte[n] = hex[i] - 'A' + 10;
        else byte[n] = hex[i] - '0';
        if(hex[i + 1] >= 'A' && hex[i + 1] <= 'F')
            byte[n] = (byte[n] << 4) | (hex[i + 1] - 'A' + 10);
        else byte[n] = (byte[n] << 4) | (hex[i + 1] - '0');
        ++n;
    }
        return n;
}

unsigned char ChartoAscii(const unsigned char cha)
{
    unsigned char ascii;
    if ((cha >= 0x0A) && (cha <= 0x0F))
    {
        ascii = cha + 'A' - 10;
    }
    else
    {
        ascii = cha + '0';
    }
    return ascii;
}

int ObjToHex(char *hex, const void *obj, int len)
{
    int i=0;
    unsigned char high,low;
    int tmp = 0;

    const char *o = (const char *)obj;
    if(obj == NULL || hex == NULL){
        return -1;
    }

    if(len <= 0)
        return -2;

    for(; i<len; i++)
    {
        tmp = (unsigned char)o[i];
        high = tmp >> 4;
        low = tmp & 15;
        *hex++ = valueToHexCh(high); //先写高字节
        *hex++ = valueToHexCh(low); //其次写低字节
    }
    *hex = '\0';

    return 0;
}

int HexToObj(const char *hex, void *obj, int objlen)
{
    int hexlen = strlen(hex);
    if(hexlen != objlen*2)
        return -1;

    return hexToStr(hex, (char*)obj);
}
