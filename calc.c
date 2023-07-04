#include "calc.h"
#include <stdio.h>

// C언어의 함수
int Add(int a, int b)
{
    foo();
    return a + b;
}
int Sub(int a, int b) { return a - b; }

// 내부의 static 함수가 extern 함수에 의해서
// 자연스럽게 호출될 수 있어야 합니다.
