# FTP 프로그래밍 작성 실습

### 라인 피드 (Line Feed)

- 문자열의 표현방식에서 표시 위치를 해당 줄의 다음 행으로 이동시키기 위한 특수문자 (\n)

### 캐리지 리턴 (Carriage Return)

- 문자열의 표현방식에서 표시 위치를 해당 줄의 맨 앞으로 이동시키기 위한 특수 문자(\r)

---

---

## 클라이언트 작성

- telnet 명령을 통해 FTP 서버에 접속 (PI(Protocol Interpreter) 채널용)
- RFC 959에서 언급된 또는 1차시에서 설명된 접속 절차 관련 요청 메시지를 타이핑 후 전달
- 데이터 전송 채널을 위한 2개의 터미널 접속이 필요

- DTP용 채널에 접속
- IP 와 Port 알아내는 방법
  - PI채널에 PASV 명령 후, 응답메시지 227에서 ,(쉼표)를 구분 문자로 네 개의 영역이 IP 주소가 됨
  - 뒤의 두 개의 영역이 port 번호가 됨
    - (앞숫자 \* 256) + 뒷숫자

### 매크로 정의 및 서버 접속용 구조체 정의

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#incldue <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <poll.h>
#include <unistd.h>

#define MAX_FDS = 3; // key board, PI & DTP socket

typeof struct {
    char IpAddr[16];
    uint16_t port;
    char UserName[256];
    char UserPass[256];
    char DtpIpAddr[16];
    uint16_t DtpPort;
} ConnectInfo_t;

enum TransferType {
    NONE = 0;  // Text Download
    PUT  = 1;  // File Upload
    GET  = 2;  // File Download
}
```

- 글로벌 변수 선언 및 함수 프로토타입 정의

```

// 함수 프로토 타입
int init_arguments(ConnectInfo_t *conn, int argc, char **argv);
int ConnectToServer(char *ipAddr, uint16_t port);
int PiReceiverProcess(int sockfd, ConnectInfo_t*);
int DtsReceiverProcess(int sockfd);
int DtsSenderProcess(int sockfd);
int kbdProcess(int sockfd, ConnectInfo_t);

enum TransferType g_TransferType = NONE; // DTP 채널 접근 타입
int g_SocketDtpFd = -1; // DTP 채널용 소켓
char g+Pathname[BUFSIZ]; // 접근할 파일명 (데이터 송수신)
```
