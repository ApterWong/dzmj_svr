#ifndef DATA_CONVERT_H
#define DATA_CONVERT_H

/***  ***  ***  ***  ***  ***
 *  网上的整理过来的，感谢作者,
 */

#ifdef __cplusplus
extern "C" {
#endif

/***
 *  将一个二进制数据块装换成一个十六进制的字符串序列
 *  @hex：[out] 输出串，需传入非NULL指针
 *  @obj：[in] 任意二进制数据
 *  @len：[in] obj的长度
 *  return value: 0 success
*/
int ObjToHex(char *hex, const void *obj, int len);

int HexToObj(const char *hex, void *obj, int objlen);

#ifdef __cplusplus
}
#endif

#endif // DATA_CONVERT_H
