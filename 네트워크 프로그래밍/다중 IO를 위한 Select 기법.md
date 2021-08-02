# 다중 I/O를 위한 Select 기법

### select() 함수

- 여러 개의 파일 기술자들을 주어진 시간동안 모니터링

---

---

## Select() 기법 소개

### 기본 개념

- poll() 함수 동작과 유사
- 단, 입력, 출력, 예외(오류)를 위한 각각의 파일 기술자들을 분리하여 별개의 인자로 전달 (총 5개 인자)
- poll() 함수가 아닌 select() 함수 호출 및 관련 API들을 통해 멀티플렉싱 기법을 구현

### 기능 구현 절차

1. 검사할 파일 기술자들을 fd_set 구조체 변수에 등록
2. 모니터링 할 타임아웃 값을 설정 (timeval 구조체)
3. select() 함수 호출
4. 발생된 이벤트를 확인 및 관련 이벤트 처리

---

## 관련 APIs

```
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#incldue <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct tiemval *timeout);
void FD_CLR(int fd, fd_set *set);
int FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
```

- 함수: select()

  - 여러 개의 파일 기술자들을 주어진 시간동안 모니터링
  - 동록된 파일 기술자에 입력, 쓰기, 예외의 상태발생 시, 해당 파일 기술자변수에 관련 사항을 명기
  - 명기된 파일 기술자등록 변수의 상태 값을 통해, 각 입/출력의 준비 상태를 알 수 있음
  - 파일 기술자의 최대크기가 1024보다 클 수 없음

- 인자

  - int nfds
    - 모니터링할 파일 기술자의 최대 값
  - fd_set \*readfds
    - 입력 준비상태 모니터링 변수
  - fd_set \*writefds
    - 출력 준비상태 모니터링 변수
  - fd_set \*exceptfds
    - 예외 준비상태 모니터링 변수
  - struct timeval \*timeout
    - 타임아웃 설정 변수

- 결과 값
  - 성공 시
    - 0 (타임아웃 시)
    - \> 0 (준비 개수)
  - 실패 시
    - -1

### 구조체: struct timeval

```
struct timeval {
    long tv_sec;
    long tv_usec;
}
```

- NULL
  - 한 개라도 준비상태가 될때까지 무기한 대기
- 0
  - 대기시간 없음 (폴링에 유용)
- \> 0
  - 정해진 시간동안 대기

### 타입 fd_set

- 1024(FD_SETSIZE)개의 파일 기술자를 기록할 수 있는 배열
- 파일 기술자의 번호를 각 배열의 위치(index)로 하여, 해당 위치에서의 변화된 값을 감지

### 함수 FD_ZERO

- fd_set 타입의 변수(배열구조) set의 모든 내용을 0으로 초기화

### 함수 FD_ISSET

- fd_set 타입의 변수(배열구조) set에서 파일 기술자 fd에 해당되는 곳에 신호가 있는지 검사

- 결과 값
  - Non-zero
    - 준비 상태
  - 0
    - 파일 기술자가 준비상태가 아님

### 함수 FD_SET

- 모니터링 할 파일 기술자를 변수 set에 할당
- 결과 값
  - Non-zero
    - 준비 상태
  - 0
    - 파일 기술자가 준비상태가 아님

### 함수 FD_CLR

- 변수 set에서 파일 기술자(fd)를 모니터링 대상에서 제외
- 결과 값
  - Non-zero
    - 준비 상태
  - 0
    - 파일 기술자가 준비상태가 아님

### 블록킹 코드 예

- 키보드가 입력을 받는 프로그램
- "EXIT"문가가 입력되면 프로그램을 종료
- 반복적인 read() 함수 호출에 따른 대기상태가 발생됨

- 해결 코드
  - select() 함수를 통해 키보드입력의 상태를 모니터링
  - 모니터링 후 준비상태일 때에만 read() 함수를 호출함으로써 블록킹 현상을 해결
