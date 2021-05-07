#ifndef __PROJECT_H__
#define __PROJECT_H__

#ifdef printf
#undef printf
#endif
int panic(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
#define printf printf_

#endif
