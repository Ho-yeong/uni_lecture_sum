# 네트워크용 API 실습

### memcpy()

- 지정한 위치의 데이터를 복사하는 역할을 수행하는 함수

### malloc()

- 동적으로 메모리를 할당

### free()

- 동적으로 할당된 메모리 공간을 운영체제에게 환원

---

---

## 파일 접근 (읽기/ 쓰기) 실습

---

## 표준바이트 순서 변환

### 호스트 - 네크워크 간 변환

```
#include <stdio.h>
#include <sys/types.h>
#incldue <arpa/inet.h>

void showBytes(char *d, int size)
{
    for(int = 0; i < size; i++) {
        printf("[0x%2X] ", d[i]&0xFF);
    }

    printf("\n")
}
```

---

## 주소 변환

### 함수: inet_addr()

```
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{
    in_addr_t addr;
    char ip_addr[16] = {"1.2.3.4"};
    char *p = (char*)&addr;

    // Big-Endian based 32bit Integer
    addr = inet_addr(ip_addr);

    printf("Inet addr is 0x%x\n", addr);
    printf("\t[0]=0x%02x\n, p[0]);
    printf("\t[0]=0x%02x\n, p[1]);
    printf("\t[0]=0x%02x\n, p[2]);
    printf("\t[0]=0x%02x\n, p[3]);

    return 0;
}
```

### 함수: inet_network()

- 호스트에서 인식할 수 있는 데이터타입

```
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{
    in_addr_t addr;
    char ip_addr[16] = {"1.2.3.4"};
    char *p = (char*)&addr;

    // 32bit Integer(Host based Endian)
    addr = inet_network(ip_addr);

    printf("Inet addr is 0x%x\n", addr);
    printf("\t[0]=0x%02x\n, p[0]);
    printf("\t[0]=0x%02x\n, p[1]);
    printf("\t[0]=0x%02x\n, p[2]);
    printf("\t[0]=0x%02x\n, p[3]);

    return 0;
}
```
