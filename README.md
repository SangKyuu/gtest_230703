
# Google Test 설치 방법
1. 동적 라이브러리
 - libgtest.so

2. 정적 라이브러리
 - libgtest.a
 - 구글 테스트는 정적 라이브러리로 많이 사용합니다.

## Google Test
```
$ wget https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
$ tar xvf v1.13.0.tar.gz
$ rm v1.13.0.tar.gz
$ mv googletest-1.13.0/ googletest

# gtest-all.cc
$ g++ ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include/ -I ./googletest/googletest/ -c

# gtest_main.cc
$ g++ ./googletest/googletest/src/gtest_main.cc -I ./googletest/googletest/include -c

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gtest_main.o

```
## GoogleTest + GoogleMock
> GoogleMock은 GoogleTest에 의존성이 있습니다.
```
# gtest-all.cc
$ g++ -c ./googletest/googletest/src/gtest-all.cc -I ./googletest/googletest/include/ -I ./googletest/googletest/

# gmock-all.cc
$ g++ -c ./googletest/googlemock/src/gmock-all.cc \
-I ./googletest/googlemock/include \
-I ./googletest/googlemock/ \
-I ./googletest/googletest/include

# gmock_main.cc
$ g++ -c ./googletest/googlemock/src/gmock_main.cc \
-I ./googletest/googlemock/include \
-I ./googletest/googletest/include

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gmock-all.o gmock_main.o

```
