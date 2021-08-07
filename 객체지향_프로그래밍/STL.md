# STL

### 컨테이너

- 객체를 저장하는 객체로 컬렉션 혹은 자료구조

### 알고리즘

- 정렬, 삭제, 검색, 연산 등을 해결하는 일반화된 방법을 제공하는 함수

---

---

## C++ 표준 템플릿 라이브러리 (STL)의 컨테이너 와 알고리즘

```
STL (Standard Template Library)
```

- C++ 표준 라이브러리 중 하나
- 많은 제네릭 클래스와 제네릭 함수 포함
  - 개발자는 이들을 이용하여 쉽게 응용 프로그램 작성

### STL의 구성

- 컨테이너 - 템플릿 클래스
  - 데이터를 담아두는 자료 구조를 표현한 클래스
  - 리스트, 큐, 스택, 맵, 셋, 벡터
- iterator - 컨테이너 원소에 대한 포인터
  - 컨테이너의 원소들을 순회하면서 접근하기 위해 만들어진 컨테이너 원소에 대한 포인터
- 알고리즘 - 템플릿 함수
  - 컨테이너 원소에 대한 복사, 검색, 삭제, 정렬 등의 기능을 구현한 템플릿 함수
  - 컨네이너의 멤버 함수가 아님

| 컨테이너 클래스 | 설명                                               | 헤더 파일  |
| --------------- | -------------------------------------------------- | ---------- |
| vector          | 가변 크기의 배열을 일반화한 클래스                 | \<vertor\> |
| deque           | 앞뒤 모두 입력 가능한 큐 클래스                    | \<deque\>  |
| list            | 빠른 삽입/삭제 가능한 리스트 클래스                | \<list\>   |
| set             | 정렬된 순서로 값을 저장하는 집합 클래스, 값은 유일 | \<set\>    |
| map             | (key, value) 쌍을 저장하는 맵 클래스               | \<map\>    |
| stack           | 스택을 일반화한 클래스                             | \<stack\>  |
| queue           | 큐를 일반화한 클래스                               | \<qeueu\>  |

| iterator의 종류        | iterator에 ++ 연산 후 방향 | read/write |
| ---------------------- | -------------------------- | ---------- |
| iterator               | 다음 원소로 전진           | read/write |
| const_iterator         | 다음 원소로 전진           | read       |
| reverse_iterator       | 지난 원소로 후진           | read/write |
| const_reverse_iterator | 지난 원소로 후진           | read       |

- 알고리즘 함수들
  - copy, merge, random, rotate, equal, min, remove, sort ...

### 헤더 파일

- 해달 클래스가 선언된 헤더 파일을 include
- 이름 공간
  - STL이 선언된 이름 공간은 std

### vertor 컨테이너

- 가변 길이 배열을 구현한 제네릭 클래스
  - 개발자가 벡터의 길이에 대한 고민할 필요 없음
- 원소의 저장, 삭제, 검색 등 다양한 멤버 함수 지원
- 벡터에 저장된 원소는 인덱스로 접근 가능
  - 인덱스는 0부터 시작

| 멤버와 연산자 함수            | 설명                                                         |
| ----------------------------- | ------------------------------------------------------------ |
| push_back(element)            | 벡터의 마지막에 element 추가                                 |
| at(int index)                 | index 위치의 원소에 대한 참조 리턴                           |
| begin()                       | 벡터의 첫 번째 원소에 대한 참조 리턴                         |
| end()                         | 벡터의 끝(마지막 원소의 다음)을 가리키는 참조 리턴           |
| empty()                       | 벡터가 비어있으면 true 리턴                                  |
| erase(iterator it)            | 벡테에서 it가 가르키는 원소 삭제, 삭제 후 자동으로 벡터 조절 |
| insert (iterator it, element) | 벡터 내 it 위체에 element 삽입                               |
| size()                        | 벡터에 들어 있는 원소의 개수 리턴                            |
| operator[]()                  | 지정된 원소에 대한 참조 리턴                                 |
| operator=()                   | 이 벡터를 다른 벡터에 치환 (복사)                            |

---

## STL의 활용

### iterator 사용

- 반복자라고도 부름
- 컨터이너의 원소를 가리키는 포인터

- iterator 변수 선언
  - 구체적인 컨테이너를 지정하여 반복자 변수 생성

```
vertor<int>::iterator it;
it = v.begin();
```

### map 컨테이너

- ('키', '값')의 쌍을 원소로 저장하는 제네릭 컨테이너
  - 동일한 '키'를 가진 원소가 중복 저장되면 오류 발생
- '키'로 '값' 검색
- 많은 응요에서 필요함
- \#include \<map\> 필요

```
// 맵 생성
Map<string, string> dic;

// 원소 저장
dic.insert(make_pair("love", "사랑"));
dic["love"] = "사랑";

// 원소 검색
string kor = dic["love"];
string kor = dic.at("love");
```

### STL 알고리즘 사용하기

- 템플릿 함수
- 전역 함수
- iterator와 함께 작동

- sort() 함수 사례
  - 두 개의 매개 변수

```
vertor<int> v;

sort(v.begin(), v.begin() + 3); // v.begin()에서 v.begin() +2 까지 정렬
sort(v.begin() +2, v.begin() + 5); // 벡터의 3번째 원소에서 .. +4 까지 정렬
sort(v.begin(), v.end());
```

### auto

- 컴파일러에게 변수선언문에서 추론하여 타입을 자동 선언하도록 지시
- 장점
  - 복잡한 변수선언을 간단하게, 긴 타입 선언 시 오타 줄임

```
auto pi = 3.14; // double 타입으로 선언
auto n = 3; // int 타입

int n = 10;
int &ref = n;
auto ref2 = ref; // int& 참조변수로 자동 선언
```

- 함수의 리턴 타입으로 추론하여 변수 타입 선언

```
auto i = function();
```

- STL 템플릿에 활용
  - iterator 타입의 변수 it를 auto를 이용하여 간단히 선언

```
for (auto it = v.begin(); it != v.end(); it++) {
    ...
}
```

### 람다

- 람다 대수와 람다식
  - 람다 대수에서 람다식은 수학 함수를 단순하게 표현하는 기법

```
(x, y) -> x + y
```

- 익명의 함수 만드는 기능으로 C++11 부터 도입

- 람다식의 구성
  - 캡쳐 리스트
    - 람다식에서 사용하고자 하는 함수 바깥의 변수 목록
  - 매개변수 리스트
    - 보통 함수의 매개변수 리스트와 동일
  - 리턴 타입
  - 함수 바디
    - 람다식의 함수 코드

```
[](int x, int y) {cout << x+ y;};
[](int x, int y) -> int {return x + y;};

```

```
int main() {
    auto love = [](string a, string b) { cout <<  .... << endl;}; // 람다식 선언

    love("a", "b"); // 람다식 호출
    love("c", "d");
}
```

- 람다식의 형식은 컴파일러만 알기 때문에, 개발자가 람다식의 타입을 알수 없음 -> auto 사용

```
int main() {
    double pi = 3.14; // 지역 변수

    auto calc = [pi](int r) -> double {return pi * r * r;};
}
```
