
# Google Test 설치 방법
1. 동적 라이브러리
 - libgtest.so

2. 정적 라이브러리
 - libgtest.a
 - 구글 테스트는 정적 라이브러리로 많이 사용합니다.
```
$ wget https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
$ tar xvf v1.13.0.tar.gz
$ rm v1.13.0.tar.gz
$ mv googletest-1.13.0/ googletest

# gtest-all.cc
$ g++ ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include/ -I ./googletest/googletest/ -c

# libgtest.a
$ ar rcv libgtest.a gtest-all.o

```