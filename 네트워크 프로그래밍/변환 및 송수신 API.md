# 변환 및 송수신 APIs

### inet_aton

- aton은 Address To Network의 줄임말로 도트형(dotted)의 문자열주소를 네트워크 주소(4바이트, Big-Endian)로 변경

### inet_ntoa

- ntoa는 Network To Address의 줄임말로 네트워크주소를 도트형의 문자열 주소로 변경

---

---

## 주소 변환을 위한 API들

### 함수 inet_addr()

- 문자열 형태의 IP주소(IPv4)를 소켓 주소에서 사용될 수 있는 이진 값(32비트)으로 변환
- 출력 값은 Big-Endian 형태의 32비트 정수
- 입력이 "1.2.3.4"이면 출력은 0x01020304(Big-Endian)이 됨

```
#include <sys/sockect.h>
#include <netinet/in.h>
#include <arpa.inet.h>

in_addr_t inet_addr(const char *cp);
```

- 함수 원형
- 반환 값
  - 성공 시: 32비트의 정수 값
  - 실패 시: -1

### 함수: inet_network()

- inet_addr() 함수와 동일한 기능
- 문자열 형태의 IP주소(IPv4)를 이진 값(32비트)으로 변환
- 출력 값은 `호스트 시스템에서 인식하는 형태의 32비트 정수`
- 네트워크에서 사용될 수 있는 32비트 정수로 변환하기 위한 `별도의 처리(htonl()함수 호출)가 필요`
- 입력이 "1.2.3.4"이면 출력은 0x01020304(Little-Endian)이 됨
- 함수 원형은 동일

### 함수: inet_aton()

- inet_addr()과 동일한 기능을 수행하나 두번째 인자가 출력물이 됨

```
#include <sys/sockect.h>
#include <netinet/in.h>
#include <arpa.inet.h>

int inet_aton(const char *cp, struct in_addr *inp);
```

- 함수 원형
- 반환 값
  - 성공 시: 1
  - 실패 시: 0

### 함수: inet_ntoa()

- 네트워크 주소(IPv4)를 문자열 주소("w.x.y.z.") 형태로 변환
- 출력결과물의 위치는 정적메모리(static memory)가 됨
  - re-entrant 주의

```
#include <sys/sockect.h>
#include <netinet/in.h>
#include <arpa.inet.h>

char *inet_ntoa(struct in_addr in);
```

- 함수 원형
- 반환 값
  - 문자열 주소

### 함수: inet_pton()

- inet_aton의 역할과 비슷하나 IPv4외 IPv6를 지원
- pton에서 p는 `presentation`을 n은 `numetic`을 의미
- 첫 번째 인자에서 사용되는 값에 따라, IPv4와 IPv6를 구분하여 처리

- 지시자
  - IPv4
    - AF_INET
  - IPv6
    - AF_INET6

```
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);
```

- 반환 값

  - 성공 시: 1
  - 실패 시: 0

- 문자열의 최대 길이 정의 값
- IPv4
  - 16의 값으로 INET_ADDRSTRLEN으로 정의
- IPv6
  - 46의 값으로 INET6_ADDRSTRLEN으로 정의

---

## 데이터 송수신 APIs

### 함수: read()

- 파일 기술자를 통해 지정한 개수만큼 데이터를 읽음
- 파일 기술자가 소켓 타입이면 수신버퍼에서 데이터를 읽어들임

```
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

- 함수 원형

### 함수: write()

- 파일 기술자를 통해 지정한 개수만큼 데이터를 기록
- 파일 기술자가 소켓타입이면 `송신버퍼에 데이터를 기록`

```
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

- 함수 원형

### 함수: recv()

- 연결형 소켓을 통해 수신버퍼에 있는 데이터를 지정한 개수만큼 읽음
- read() 함수의 기능과 동일하나 `소켓에서만` 사용되며, 네번째 인자(flags)에 따라 운영 기능이 더 확장됨
- TCP기반의 통신소켓

```
#include <sys/types.h>
#include <sys/socket.h>

ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

- 함수 원형

- flag 기능 (네 번째 인자)
  | 이름 | 설명 |
  | --- | --- |
  | MSG_DONTWAIT | 수신 버퍼에 데이터가 없으면, 바로 빠져 나옴 |
  | MSG_OOB | 1바이트를 갖는 Out-Of-Bound 데이터를 수신 (Urgent Data)|
  | MSG_PEEK | 수신버퍼에서 데이터를 읽을 때, 수신 버퍼의 내용을 지우지 않음 |
  | MSG_WAITALL | 지정한 개수까지 수신버퍼에서 읽을때까지 대기 (Blocking) |

### 함수: send()

- 연결형 소켓을 통해 전달될 송신 버퍼에 데이터를 지정한 개수만큼 기록
- write() 함수의 기능과 동일하나 `소켓에서만` 사용되며, 네 번째 인자 (int flags)에 따라 운영기능이 더 확장 됨

```
#include <sys/types.h>
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

- 함수 원형

- flag 기능 (네 번째 인자)
  | 이름 | 설명 |
  | --- | --- |
  | MSG_DONTROUTE | 로컬 영역에 연골된 네트워크로만 전달 |
  | MSG_DONTWAIT | 송신 버퍼에 기록을 못하는 상태이더라도 대기하지 않음 (Blocking 안함) |
  | MSG_OOB | 1바이트를 갖는 Out-Of-Bound 데이터를 송신(Urgent Data) |
