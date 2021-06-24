# 객체의 동적 생성 및 반환, this 포인터의 이해, string 클래스의 사용

### this 포인터

- 객체 자신에 대한 포인터로서 클래스의 멤버 함수 내에서만 사용

### string 클래스

- C++ 표준 라이브러리에서 제공하는 클래스
- 문자열을 객체로 다루는 클래스

---

---

## 객체의 동적 생성 및 반환

```
클래스이름 *포인터변수 = new 클래스이름;
클래스이름 *포인터변수 = new 클래스이름(생성자매개변수리스트);
```

### 객체 배열의 동적 생성 및 반환

```
클래스이름 *포인터변수 = new 클래스이름[배열 크기];
delete [] 포인터변수;
```

```
pArray[0].setRadius(10);
pArray[1].setRadius(20);

...
```

- 동적으로 생성된 배열도 `보통 배열처럼 사용`

```
pArray -> setRadius(10);
(pArray + 1) -> setRadius(20);

...
```

- `포인터로 배열 접근`

```
delete [] pArray;
```

- 배열 소멸
- 생성의 역순으로 소멸됨

### 동적 메모리 할당과 메모리 누수

```
char n = 'a';
char *p = new char[1024];
p = &n;
```

- p가 n을 가르키면 할당 받은 1024 바이트의 메모리 누수 발생

- 프로그램이 종료되면 운영체제는 누수 메모리를 모두 힙에 반환

---

## this 포인터 이해, string 클래스 사용

### this 포인터

- 포인터, 객체 자신 포인터
- 클래스의 멤버 함수 내에서만 사용
- 개발자가 선언하는 변수가 아니고, 컴파일러가 선언한 변수
  - 컴파일러에 의해 `묵시적으로 삽입`

```
class Circle {
    int radius;
public:
    Circle() {this -> radius = 1;}
    Circle(int radius) {this -> radius = radius;}
    void setRadius(int radius) {this -> radius = radius;}
    ...
};
```

### this가 필요한 경우

- 매개변수의 이름과 멤버 변수의 이름이 같은 경우
- 멤버 함수가 객체 자신의 주소를 리턴할 때

### this의 제약 사항

- 멤버 함수가 아닌 함수에서 this 사용 불가
  - 객체와의 관련성이 없기 때문
- static 멤버 함수에서 this 사용 불가
  - 객체가 생기기 전에 static 함수 호출이 있을 수 있기 때문에

### string 클래스를 이용한 문자열

- string 클래스
  - C++ 표준 라이브러리, \<string\> 헤더 파일에 선언
  - `가변 크기의 문자열`
  - 문자열, 스트링, 문자열 객체, string 객체 등으로 혼용
  - new/delete를 이용하여 문자열을 동적 생성/반환 가능

```
동적 생성/ 반환

string *p = new string("C++");
cout << *p // C++ 출력
p ->append("Great!");
cout << *p // C++ Great! 출력

delete p;
```
