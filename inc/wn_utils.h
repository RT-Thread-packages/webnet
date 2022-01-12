/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-02     Bernard      the first version
 */

#ifndef __WN_UTILS_H__
#define __WN_UTILS_H__

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int str_begin_with(const char *s, const char *t);
int str_end_with(const char* s, const char* t);
int str_path_with(const char *s, const char *t);
char *str_decode_path(char *path);
char *str_base64_encode(const char* src);
char* str_normalize_path(char* fullpath);
char * urlencode(const char *str, int len, int *new_length);
int urldecode(char *str, int len);

#ifdef  __cplusplus
    }
#endif

#endif /* __WN_UTILS_H__ */

