#ifndef CALC_H
#define CALC_H

#include <stdio.h>

int Add(int a, int b);
int Sub(int a, int b);

// 인라인 함수는 헤더를 통해서 구현이 제공되어야 합니다.
static inline void foo()
{
    printf("hello, foo\n");
}

#endif
