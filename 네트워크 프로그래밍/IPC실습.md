# IPC 실습

### popen

- IPC관련 API중 하나로 popen을 통해 동작하는 프로세스의 표준출력(Stoud)이 파이프의 입력으로 전환됨

### msgsnd

- 메시지 큐(Message queue)를 위한 API로써, 등록된 키에 메시지를 추가(En-Queue) 시키는 기능을 수행

### msgrcv

- 메시지 큐(Messeage Queue)를 위한 API로써, 등록된 키에서 메시지를 추출(De-Queue)하는 기능을 수행

### shmat

- 공유메모리 첨부를 위한 API로써, 결과물은 가상의 주소공간이나 다른 프로세스간의 공유된 주소영역으로 할당됨

### shmdt

- 공유메모리 분리를 위한 API로써, 직전 연결된 공유메모리 주소를 시스템에서 분리하는 역할

---

---

## 시그널과 파이프 실습

### 시그널

- SIGUSR1 과 SIGUSR2 신호에 대한 신호를 처리하는 프로그램 작성
- SIGUSR2를 입력 받으면 프로그램을 종료
- kill 명령을 통해 작성한 프로세스에 SIGUSR1과 SIGUSR2 신호를 전달

```
#include<stdio.h>
#include<signal.h>
#include<unistd.h> // UNIX 기반 C언어 코드 작성시 필히 추가

void sigusr1_handler(int sig);
void sigusr2_handler(int sig);

static int bExit = 0;
```

```
int
main(void) {
    printf("PID: %d\n". getpid() );
    signal(SIGUSR1, sigusr1_handler); // 시그널 핸들러 등록
    signal(SIGUSR2, sigusr2_handler);

    while(1) {
        sleep(1);

        if(bExit)
            break;
    }

    return 0;
}
```

```
void
sigusr1_handler(int sig) // SIGUSR1 함수 처리
{
    printf("SIGUSR1 received!!(sig-%d)\n", sig);

    return;
}

void
sigusr2_handler(int sig) // SIGUSR2 함수 처리
{
        printf("SIGUSR2 received!!(sig-%d)\n", sig);
        printf("Now this program will be finished. \n");

        bExit = 1;

        return;
}
```

### 파이프 (popen)

- 실행한 명령 프로세스의 출력결과를 파이프로 읽기

```
#incldue <stdio.h>
#include <unistd.h>

int
main()
{
    FILE *fp = NULL;
    char buffer[BUFSIZ];

    // Open PIPE in Read Mode.
    fp = popen("\bin\ls -l \etc", "r");
    if (fp == NULL)
    {
        printf("popen error!\n")
        return 0;
    }

    //Read line by line.
    while( fgets(buffer, BUFSIZ, fp))
    {
        printf("#: %s", buffer)
    }

    // Close PIPE
    pclose(fp);

    return 0;
}
```

### FIFO

- 파이프 파일에 각각 읽고 쓰는 두 개의 프로세스를 작성

```
#incldue <stdio.h>
#incldue <unidio.h>
#incldue <sys/typer.h>
#incldue <sys/stat.h>
#incldue <fcntl.h>

int
main(void)
{
    int fd;
    char ch;

    unlink("./fifo") // 파이프 파일 생성
    mkfifo("./fifo", 0600);

    // 파이프 파일에 A ~ Z 기록
    fd = open("./fifo", O_WRONLY);

    for (ch="A";ch<="Z";ch++){
        write(fd, &ch, i);
        sleep(1);
    }

    close(fd);

    return 0;
}
```

```
#incldue <stdio.h>
#incldue <unidio.h>
#incldue <sys/typer.h>
#incldue <sys/stat.h>
#incldue <fcntl.h>

int
main(void)
{
    int fd;
    char ch;

    fd=open("./fifo", O_RDONLY);

    // 파이프 파일 읽기
    while(1) {
        read(fd, &ch, 1);
        printf("%c", ch);
        fflush(stdout);
        if (ch == "Z")
            break;
    }

    close(fd);

    return 0;
}
```

---

## 메시지 큐 실습

### 메시지 구조 정의

```
// MsgQueue.h 파일
#incldue<unistd.h>

typedef struct msgbuf_st
{
    long mtype; // 필수의 넣어야 하는 4바이트

    // 메시지 내용
    char mtext[BUFSIZ];
} msgbuf_t;
```

- 총 100개의 메시지를 시스템에 추가

```
#incldue <unistd.h>
#incldue <stdio.h>
#include<sys/types.h>
#incldue <sys/ipc.h>
#incldue <sys/msg.h>
#incldue <string/h>

#incldue "MsgQueue.h" // 메시지 구조 정의 헤더

int
main(void)
{
    int index = 0;
    int msg_id = 0;
    msgbuf_t msgbuf;

    // Key: 0x04 // 16진수
    msg_id = msgget((key_t)0x04, IPC_CREAT|0666);

    printf("Message ID: %d\n", msg_id);

    for(;index <100; index++) {
        // 메시지 작성
        msgbuf.mtype = 1;
        memset(msgbuf.mtype, 0, BUFSIZ);
        sprintf(msgbuf.mtext, "[%d]Hello World", index);

        // 메시지큐에 송신
        msgsnd(msg_id, (void *)&msgbuf, strlen(msgbuf.mtext), 0);

        sleep(1);
    }

    return 0;
}
```

### 메시지 큐에서 읽기

- 무한루프 방식으로 메시지 큐에서 읽기 기능을 수행
- 메시지가 없을 떄에는 loop 값을 증가하여, 직전 메시지 수신까지 몇차례 시도를 했는지를 파악

```
...
// 메시지 구조 정의 헤더
#include "MsgQueue.h"

int
main(void)
{
    int msg_id = 0;
    int loop = 0;
    msgbuf_t msgbuf;

    msg_id = msgget((key_t)0x04, IPC_CREAT|0666);

    printf("Message ID: %d\n", msg_id);

    while(1) {
        msgbuf.mtype = 0; // 메시지큐의 가장 첫번째 기록된 메시지
        memset(msgbuf.mtext, 0, BUFSIZ);

        if(msgrcv(msg_id, (void *)&msgbuf, BUFSIZ, 0, IPC_NOWAIT)<0)
        {
            // 메시지 수신, 없으면 loop 값 증가
            loop++;
            continue;
        }

        printf("loop: %d\n", loop);
        printf("mtype: %d\n", msgbuf.mtype);
        printf("mtext: %s\n", msgbuf.mtext);

        loop = 0;
    }

    return 0;
}
```

### 메시지 큐 상태 파악 및 제거

- `ipcs` 명령을 통해 메시지 상태 파악
- `ipcrm` 명령을 통한 메시지 큐 제거

---

## 공유 메모리 실습

```
#incldue <unistd.h>
#incldue <stdio.h>
#include<sys/types.h>
#incldue <sys/ipc.h>
#incldue <sys/shm.h>
#incldue <string/h>
```

- 공통적으로 사용되는 헤더

### 쓰기 프로그램 작성

```
int
main(void)
{
    int loop = 0;
    int shmid = 0;
    void *shmaddr;

    shmid = shmget((key_t)0x0a, 1024, IPC_CREAT|0666);
    if (shmid == -1)
    {
        perror("Getting Shared Memory failed!\n")
        return -1;
    }

    // (void *)0 == 0

    shmaddr = shmat(shmid, (void *)0, 0)
    if (shmaddr == (void *)-1){
        perror("Attaching failed!!\n")
        return -1;
    }

    for (loop=0l loop <100; loop++) {
        // 데이터 기록
        memset(shmaddr, 0, 1024);
        sprintf((char *)shmaddr, "%d Hello World", loop);
        sleep(1;)
    }

    // 공유 메모리 분리
    shmdt(shmaddr);

    return 0;
}
``
```

### 읽기 프로그램

````
int
main(void)
{
    int loop = 0;
    int shmid = 0;
    void *shmaddr;

    shmid = shmget((key_t)0x0a, 1024, IPC_CREAT|0666);
    if (shmid == -1)
    {
        perror("Getting Shared Memory failed!\n")
        return -1;
    }

    // (void *)0 == 0

    shmaddr = shmat(shmid, (void *)0, 0)
    if (shmaddr == (void *)-1){
        perror("Attaching failed!!\n")
        return -1;
    }

    while(1)
    {
        // 데이터 읽기
        printf("Data: %s\n", shmaddr);
        sleep(2);
    }

    shmdt(shmaddr);

    return 0;
}
```
````
