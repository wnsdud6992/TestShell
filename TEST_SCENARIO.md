| **실행 명령어**                                     | **설명**                                                            |
| ---------------------------------------------- | ----------------------------------------------------------------- |
| **0. Main 실행 법 확인**                            |                                                                   |
| `help`                                         | 명령어 확인                                                            |
| **1. SSD.exe의 기본 동작 확인**                       |                                                                   |
| `write 1 0x12345678`                           | 데이터 저장 확인                                                         |
| `read 1`                                       | fast read 동작 확인 (ssd\_output.txt)                                 |
| `flush`                                        | flush 동작 확인                                                       |
| `read 1`                                       | normal read 동작 확인                                                 |
| `write 2 0x12354678`                           | 데이터 저장                                                            |
| `write 3 0x12354678`                           | 데이터 저장                                                            |
| `write 4 0x12354678`                           | 데이터 저장                                                            |
| `write 5 0x12354678`                           | 데이터 저장                                                            |
| `write 6 0x12354678`                           | 자동 flush 동작 확인                                                    |
| `write 6 0xAAAA0006`                           | flush되는 시점 확인                                                     |
| **2. Erase 및 Merge 동작 확인**                     |                                                                   |
| `erase 1 5`                                    | 1번 LBA부터 5개 LBA 삭제 확인 (fast read)                                 |
| `read 1`                                       | 1번 삭제 확인 (fast read)                                              |
| `erase 1 3`                                    | 1 LBA, 3 SIZE 삭제, ignore 동작으로 cmd buffer에 생기지 않음                  |
| `erase 6 5`                                    | 6 LBA부터 5 SIZE 삭제, merge erase 동작으로 E 1 10으로 변경됨                  |
| `erase_range 1 20`                             | 1\~20 Range 삭제, ignore 동작으로 E 11 10만 생성됨                          |
| **3. Full Write & Read 동작 확인**                 |                                                                   |
| `fullwrite 0xABCDABCD`                         | 전체 LBA에 0xABCDABCD 값 기록 확인                                        |
| `read 99`                                      | 99번 LBA의 값 읽어오기                                                   |
| `fullread`                                     | 전체 LBA 값 읽어오기                                                     |
| **4. 테스트 명령어 실행**                              |                                                                   |
| `1_FullWriteAndReadCompare`                    | 5개 LBA 단위로 데이터를 쓰고, 읽어서 비교 (Full write)                           |
| `2_PartialLBAWrite`                            | 4번, 0번, 3번, 1번, 2번 LBA에 데이터 기록 후 0\~4번 LBA 비교 (30회 반복)            |
| `3_WriteReadAging`                             | 0번과 99번 LBA에 랜덤 값 기록 후 읽어서 비교 (200회 반복)                           |
| `4_EraseAndWriteAging`                         | 0~~2번 erase, 2번 Write, 2번 Overwrite, 2~~4번 (3개 단위) Erase (30회 진행) |
| **5. Logger 기능**                               |                                                                   |
| `C:\Users\User\Documents\TestShell\output\Log` | 로그 파일 위치                                                          |
| 로그 포맷                                          | \[날짜 시간] 클래스명.함수명()                                               |
| 로그 사이즈                                         | 10KB 단위로 기록됨                                                      |
| 로그 압축                                          | `latest.log` + `until_날짜_시간.log` --> `.zip`                       |
| **6. Runner 기능**                               |                                                                   |
| `TestShell shell_scripts.txt`                  | 스크립트 수행                                                           |
|                                                | 스크립트에 없는 명령어를 입력하면 에러 발생                                          |
| **7. 예외 처리 기능**                                |                                                                   |
| `abcd`                                         | INVAILD COMMAND                                                   |
| `read`                                         | read command argument error                                       |
| `read 100`                                     | address size error                                                |
| `erase 1 1 1`                                  | Erase command argument error                                      |
| `write 0 XXXX`                                 | \[Error] 숫자로 변환할 수 없는 문자열                                         |
