# 소켓과 클라이언트 API

### AF_INET

- IPv4 프로토콜을 위한 정의

### AF_INET6

- IPv6 프로토콜을 위한 정의

---

---

## 통신모델

### 서버/ 클라이언트 (Server/Client) 모델

- TCP/IP 기반의 통신은 서버와 클라이언트의 관계로 `통신 채널`을 형성 후 수행됨
- 전송된 메시지의 순서는 균일 (바뀌지 않음)
- 운영체제에서 TCP/IP 서버 또는 클라이언트 프로세스와의 `인터페이스는 소켓(Socket)으로 제공`

> 서버 (Server)

- 서버의 기능을 수행하는 `프로그램`
- 클라이언트의 연결 오청을 기다림
- 연결요청에 대한 수락
- 클라이언트로부터 요청된 정보 및 서비스를 제공

> 클라이언트 (Client)

- 클라이언트 프로그램
- 서버에 연결을 요청
- 연결 후 정보 및 서비스를 요청

---

## TCP/IP 기반의 소켓 클라이언트 프로그래밍 절차

### 소켓 (Socket)

- 네트워크를 기반으로 한 두 프로세스간의 `통신(IPC)을 위한 수단`
- 운영체제가 제공하는 응용프로그램용 인터페이스
- 운영체제에서 소켓 식별을 위한 필용 요소
  - 프로토콜
  - 소스 IP주소
  - 소스 포트 번호
  - 목적지 IP주소
  - 목적지 포트 번호
- 응용프로그램은 생성된 소켓을 파일기술자(File Description)와 동인한 접근방식으로 사용

### 클라이언트 프로그래밍 절차

1. 소켓 생성
   - OS를 통해 TCP/IP 자원 사용을 위한 소켓 생성을 요청 (함수: socket())
2. 접속 요청
   - 소켓의 파일기술자를 이용하여 TCP/IP 기반으로 서버에 접속을 요청 (함수: connect())
3. 데이터 송수신
   - 서버에 정보 및 서비스를 요청하는 메시지 송신 및 관련 횐신을 위한 데이터 수신
   - 함수: write, read, send, receive
4. 소켓 종료
   - 연결된 젒고을 해제하고 사용중인 소켓을 OS에게 환원 (함수: close())

### socket()

- OS를 통해 소켓 인터페이스를 생성
- 소켓 프로그래밍에서 통신 창구 역할을 수행
- 통신을 위한 end-point 생성
- 반환값
  - 성공: 소켓 기술자 (Socket Description)
  - 실패: -1

```
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
// type
- tcp - SOCK_STREAM
- udp - SOCK_DGRAM
- ip  - SOCK_RAW
```

- /etc/protocols
- 리눅스의 경우 이 경로의 파일에 사용가능한 프로토콜이 명시 되어있다.

### connect()

- TCP 기반의 서버에 접속을 요청하는 기능을 수행
- 서버의 IP주소와 포트번호가 포함되어 있는 소켓 구조체를 인자로 사용 (Big-Endian 형태)
- 반환값
  - 성공: 0
  - 실패: -1

```
...

int connect(int sockfd, const struct sockaddr *addr, soklen_t addrlen);

struct osockaddr { // sockaddr과 같음
    unsigned short int sa_family;
    unsigned char sa_data[14];
}
```

### close()

- 생성된 소켓을 종료
- TCP에서는 연결된 소켓을 끊는 절차를 수행하고 생성된 소켓을 종료
- UDP에서는 생성된 소켓을 종료
- 반환값
  - 성공: 0
  - 실패: -1

```
...

int close(int fd); // 소켓기술자 번호
```
