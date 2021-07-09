# Echo 프로그램 실습

### telnet

- 텍스트 기반의 클라이언트 터미널로 키보드의 입력을 받아 서버에 전달하고, 서버의 출력 결과를 터미널을 통해 출력하는 기능을 수행하는 프로그램

---

---

## 프로그램 설계

### 서버

- TCP 기반의 서버
- 포트번호를 명령의 인자로 받음
- 클라이언트의 접속을 허가
- 클라이언트로부터 메시지를 수신
- 수신한 메시지를 회신
- 수신메시지가 'EXIT'로 시작한다면, 프로그램 종료

### 클라이언트

- TCP 기반의 클라이언트
- 접속할 서버의 IP와 포트번호를 명령의 인자로 받음
- 키보드 입력
- 서버에 접속을 요청
- 키보드 입력 메시지를 서버에 송신
- 서버부터 메시지를 수신
- 수신받은 메시지를 화면에 출력
- 접속 종료

---

## 서버 만들기

- 헤더 선언

```
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 소켓용 헤더
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
```

- 서버용 변수선언 및 포트번호 설정

```
int
main(int argc, char* argv[]) {
    int serverFd; // ServerFD;
    int clientFd; // ClientFD;
    unsigned short port;

    struct sockaddr_in sAddr; // Server Address
    struct sockaddr_in cAddr; // Client Address
    socklen_t cAddr_len;

    char buffer[BUFSIZ];
    int buffer_len;

    char *pClientAddr = NULL;
    uint16_t clientPort = -1;

    if(argc != 2) { // 명령 인자 점검
        pringf("Usage: cmd <port>\n");
        return -1;
    }

    port = atoi(argv[1]); // 포트번호 설정
```

- 서버 설정 및 동작 처리

```
    serverFd = socket(PF_INET, SOCK_STREAM, 0); // TCP용 소켓 생성
    if(serverFd < 0) {
        perror("Socket Creation Failure. ");
        return -1;
    }

    // 주소 구조체 설정
    bzero(&sAddr, sizeof(struct sockaddr_in));
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sAddr.sin_port = htons(port);

    // 소켓을 주소와 포트에 연결
    if ( bind(serverFd, (struct sockaddr *)&sAddr), sizeof(sAddr)) < 0 ) {
        perror("Binding is Failed");
        return -1;
    }

    printf("Binding is Ok (Port: %d)", port);

    // 클라이언트 대기큐 생성
    if (listen(serverFd, 1)) {
        perror("Lisening is failed);
        return -1;
    }
    printf("listening OK...\n");
```

### 코드 작성

- 접속 허가
- 데이터 수신
- 데이터 송신
- 프로그램 종료

```
    do {
        // 접속 요청 허가
        clientFd = accept(serverFd, (struct sockaddr *)&cAddr, &cAddr_len);
        if( clientFd > 2) {
            printf("Connection Success FD: %d", clientFd);

            // client IP, Port 확인
            pClientAddr = inet_ntoa(cAddr.sin_addr);
            clientPort = ntohs(cAddr.sin_port);

            printf("Client Info: IP: %s, Port: %d", pClientAddr, clientPort);

            // 수신
            buffer_len = recv(clientFd, buffer, BUFSIZ, 0);
            printf("RECV: %s\n", buffer);
            // 송신
            send(clientFd, buffer, buffer_len, 0);
            // 종료 알림
            shutdown(clientFd, SHUT_RDWR);
            // 클라이언트 소켓 종료
            close(clientFd);
            clientFd = -1;

            // EXIT 가 있을때 반복문 탈출
            if (strncmp(buffer, "EXIT", 4) == 0) {
                printf("Exiting\n");
                break;
            }

        } else {
            printf("Connection has been failed\n");
            break;
        }


    } while(1);

    // 서버 소켓 종료
    close(serverFd);

    return 0;
}
```

---

## 클라이언트 만들기

### 코드 작성

- 공통 헤더부분 생략
- 변수 초기화 부분

```
int
main(int argc, char* argv[]) {
    int sockFd;
    struct sockaddr_in sAddr;

    char buffer[BUFSIZ];
    int buffer_len;

    if(argc != 3) {
        printf("Usage: cmd <IP Adress> <Port> \n");
        return -1;
    }
```

- 키보드 입력 및 소켓 생성 부분

```
    // 키보드 입력
    printf("Input Message : \n");
    buffer_len = read(0, buffer, BUFSIZ);

    // TCP용 소켓 생성
    sockFd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        perror("Socket Creation Failure");
        return -1;
    }
```

- 메시지 송/수신 및 종료

```
    // 주소 구조체 설정
    memset(&sAddr, 0, sizeof(struct sockaddr_in));
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = inet_addr(argv[1]);
    sAddr.sin_port = htons(atoi(argv[2]));

    // 접속 요청
    if ( connect(sockFd, (struct sockaddr *)&sAddr, sizeof(sAddr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("Connection Success \n");

    // 송신
    send(sockFd, buffer, buffer_len, 0);
    // 수신
    buffer_len = recv(sockFd, buffer, BUFSIZ, 0);
    printf("RECV: %s\n", buffer);

    // 소켓 종료
    printf("Connection Closing\n");
    shutdown(sockFd, SHUT_RDWR);
    close(sockFd);

    return 0;
}
```
