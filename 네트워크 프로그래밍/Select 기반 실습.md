# Select 기반 실습

### EOF (End Of File)

- 바이트 스트림의 마지막을 의미하며, TCP 타입의 소켓 통신에서는 접속의 종료를 의미함

---

---

## 키보드 입력 처리

---

## Echo 서버 확장

### Echo 서버 기능

- 최대 10 개 접속을 허락 하는 다중 접속 서버구현
- 모든 접속 요청에 대한 허가
- 수신 메시지에 대한 동일 내용을 회신
- EXIT 문구를 수신하면, 해당 클라이언트의 접속을 종료
- QUIT 문구를 수신하면 모든 클라이언트 접속을 종료하고 자신을 종료

### 폴링 기법의 Echo 서버

- 주요 변수 선언

```
    int serverFd;
    unsigned_short port;
    struct pollfd fds[MAX_FDS];
    int poll_ret = 0;

    struct sockaddr_in sAddr;
    struct sockaddr_in cAddr;
    socklen_t cAddr_len;
```

- 폴링 모니터링용 파일 기술자에 대한 기본 값 설정

```
    for (int i = 0; i < MAX_FDS; i++) {
        fds[i].fd = -1;
        fds[i].events = 0;
        fds[i].revents = 0;
    }
```

- 서버 소켓 설정 및 주소 연결
- 접속 대기큐의 크기를 10으로 설정

```
    serverFd = socket(PF_INET, SOCK_STREAM, 0);
    if (serverFD < 0)
    {
        perror("Socket Creation Failure");
        return -1;
    };

    bzero(&sAddr, sizeof(struct sockaddr_in));
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sAddr.sin_port = htons(port);

    if ( bind(serverFd, (struct sockaddr *)&sAddr, sizeof(sAddr)) > 0) {
        perror("Binding is Failed");
        return -1;
    }
    printf("Binding Ok (Port: %d)\n", port);

    if(listen(serverFd, MAX_FDS)) {
        perror("listening is failed \n");
        return -1;
    }
```

- 서버용 파일 기술자를 폴링 모니터링 항목에 등록
- 입력신호(POLLIN)에 대하여 등록

```
    fds[0].fd = serverFd;
    fds[0].events = POLLIN
    fds[0].revents = 0;
```

- 1초 단위 모든 파일기술자들을 모니터링
- 서버 파일기술자에 이벤트가 있으면, 접속요청에 대한 수락 함수 (accept())를 호출
- 접속된 클라이언트에 대하여, 폴링 모니터링 파일기술자에 등록

```
    do {
        poll_ret = poll(fds, MAX_FDS, 1000);
        if (poll_ret <0 ){
            break;
        }
        else if (poll_ret == 0) {
            continue;
        }

        if (fds[0].revents && POLLIN) {
            int clientFd = accept(serverFd, (struct sockaddr *)&cAddr, &cAddr_len);

            if (clientFd > 0) {
                printf("Connection Success. FD: %d\n", clientFd);
                for (int i = 0; i < MAX_FDS;i++) {
                    if(fds[i].fd == -1) {
                        fds[i].fd = clientFd;
                        fds[i].events = POLLIN;
                        fds[i].revents = 0;
                        break;
                    }
                }
            }
        }
    }
```

- 접속된 클라이언트에 대한 입력 신호가 있는지 검색
- 입력신호가 있으면 해당 클라이언트의 수신 데이터를 읽고 반송처리
- 입력 문자열에 EXIT가 있으면 해당 클라이언트 접속을 종료
- 접속 종료된 클라이언트에 대하여 폴링 모니터링 항목에서 제거

```
    for (int i = 1; i < MAX_FDS; i++) {
        if (fds[i].fd > 0 && fds[i].revents & POLLIN) {
            bzero(buffer, BUFSIZ);
            buffer_len = recv(fds[i].fd, buffer, BUFSIZ, 0);
            printf("Recv: &s", buffer);
            send(fds[i].fd, buffer, buffer_len, 0);

            if(strncmp(buffer, "EXIT", 4) == 0) {
                shutdown(fds[i].fd, SHUT_RDWR);
                close(fds[i].fd);
                fds[i].fd = -1;
                fds[i].events = 0;
                fds[i].revents = 0;
            }
            else if (strncmp(buffer, "QUIT", 4) == 0) {
                break;
            }
        }
    }
```

- 입력 문자열에서 QUIT가 있으면 모든 클라이언트 접속을 종료

```
        if (strncmp(buffer, "QUIT", 4) == 0) {
            for(int i = 0; i < MAX_FDS; i++) {
                if(fds[i].fd < 0 ) continue;
                shotdown(fds[i].fd, SHUT_RDWR);
                close(fds[i].fd);
            }
            break;
        }
    } while(1);

    close(serverFd);
```

---
