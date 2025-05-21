# TestShell 프로젝트 사용 안내

## 1. 실행 방법

### 1-1. 실행 파일 위치

본 프로젝트의 실행 파일들은 다음 경로에 위치하고 있습니다.

* **TestShell 실행 파일**: `(프로젝트 폴더)\TestShell\output\TestShell.exe`
* **SSD.exe 실행 파일**: `(프로젝트 폴더)\TestShell\output\SSD.exe`
* **shell\_scripts.txt 파일**: `(프로젝트 폴더)\TestShell\output\shell_scripts.txt`

### 1-2. 실행 결과 저장 위치

실행 후 결과 파일은 아래 경로에서 확인할 수 있습니다.

* **NAND 결과**: `(프로젝트 폴더)\TestShell\output\ssd_nand.txt`
* **SSD.exe read 결과**: `(프로젝트 폴더)\TestShell\output\ssd_output.txt`
* **SSD.exe command buffer**: `(프로젝트 폴더)\TestShell\output\buffer\`
* **TestShell Log 파일**: `(프로젝트 폴더)\TestShell\output\Log`

## 2. 빌드 모드

프로젝트를 빌드할 때는 \*Release 모드(x64)\*로 빌드해야 합니다. 
이 설정을 통해 빌드된 실행 파일들이 최적화된 상태로 동작하게 됩니다.

## 3. Unit Test 보장 사항

본 프로젝트의 unit test는 **커밋 a443adf**까지 정상 동작합니다. 이후 커밋에서는 리팩토링이 진행되었으나, 일부 unit test가 동작하지 않을 수 있음을 유의해 주세요.
(단, SSD.exe 프로그램은 unit Test 정상 동작합니다)

* **커밋**: a443adf0168971ddfd6b9b1dc95add323cb590c1 \[a443adf]

## 4. SSD.exe 코드 확인

TestShell에서 사용되는 **SSD.exe** 프로그램의 코드는 아래 GitHub 리포지토리에서 확인할 수 있습니다.

* GitHub 저장소: [https://github.com/JisuAhn13/SSD](https://github.com/JisuAhn13/SSD)
* Git 클론 URL: `https://github.com/JisuAhn13/SSD.git`
