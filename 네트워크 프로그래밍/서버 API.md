# 서버 API

### EOF

- End-Of-File 의 약자로 소켓기반에서 스트림의 마지막임을 알리는 특수한 메시지

---

---

## 서버용 프로그래밍 절차

1. 클라이언트의 connect() 함수와 서버의 `accept()`함수의 호출 과정에서 3단계 메세지 교환(3 way handshaking)이 수행되고,
   두 종단(End-Point)간에 접속이 이루어짐
2. 클라이언트는 최초 생성한 소켓 기술자를 통해 서버와의 데이터 송수신이 가능
3. 서버의 경우 accept() 함수의 반환값을 통해 클라이언트 접속쌍(Pair)을 위한 소켓 기술자가 됨

> socket() -> bind() -> listen() -> accept() -> recv() -> send() -> close()

- 3 way handshaking 경과 시간
  - 1.5 x RTT (Rount Trip Time)

### bind()

- 소켓 기술자와 연결될 주소를 할당(bind)
- 서버로 활용될 IP의 주소와 포트번호 그리고 프로토콜을 지정 (Big-Endian 형태)
- 반환값
  - 성공: 0
  - 실패: -1

```
...

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

### listen()

- 연결 요청 대기 상태
- 클라이언트로부터 연결에 대한 요청을 기다리는 대기큐를 생성
- 매개변수로 연결의 제한값을 받을 수 있음
- 반환값
  - 성공: 0
  - 실패: -1

```
...

int listen(int sockfd, int backlog);
// backlog - 접속 요청을 받아들일 수 있는 큐의 크기
```

### accept()

- 클라이언트로부터 요청된 연결을 수락하는 함수
- 반환값
  - 성공: 클라이언트를 위한 새로운 소켓 기술자
  - 실패: -1

```
...

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
// *addr = 비어있는 소켓 구조체 -> 접속한 클라이언트의 정보 기록
```

---

## 안정적인 접속종료 절차

### close() 함수의 기능

- 연결된 통신 링크를 완전히 종료
- 소켓이 사라져 더이상의 데이터를 송/수신이 불가한 상태로 진입
- 접속쌍 중 한 편이 메시지 송신 후 close()함수를 호출하면 다른 한 편의 응답 메시지를 받지 못하는 상황이 발생 (데이터 소실)

### 해결안

- close() 호출전 접속을 종료할 것임을 알리는 메시지 (EOF: End-Of-File)를 송신
- 종료 알림 메시지는 shutdown()함수 호출에 의해 송신가능
- 수신측에서는 EOF를 받으면 상대편이 종료할 것임을 알기에, 자신의 소켓을 종료

### shutdown() : 스트림 종료 함수

- 통신 연결중 주어진 인자의 값에 따라 일부를 종료
- 반환값
  - 성공: 0
  - 실패: -1

```
...

int shutdown(int sockfd, int how)

SHUT_RD : 수신종료
SHUT_WR : 송신종료
SHUT_RDWR : 송/수신 종료
```
