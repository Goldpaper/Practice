.386
.MODEL FLAT
;함수 사용  선언(ExitProcess 함수이름 이며 반환형은 DWORD)
ExitProcess PROTO NEAR32 stdcall, dxExitCode:DWORD
;헤더파일 인클루드
INCLUDE io.h
cr EQU 0dh         ;0dh => 0x0d (h 는 16진수를 나타낸다.)#define 효과
Lf EQU 0ah         ; EQU는 (=) 과 같다
.STACK 4096        ;스택영역을 4096만큼 확보(사용할 메모리 공간 확보)
.DATA          ;변수 영역 시작
number1  DWORD ?       ;4바이트로 변수 선언
number2  DWORD ?
prompt1   BYTE "Enter first number: ",0  ;문자를 바이트 단위로 할당하고 마지막에 0을 넣는다. 0은 문자열로 넣지 않고 (,0) 을 사용
prompt2  BYTE "Enter second number: ",0
string     BYTE 40 DUP (?)                ;BYTE 단위를 40개를 DUP(할당) 한다. (?) 는 초기화 하지 않는다는 말
label1    BYTE cr, Lf, "The Sum is "  ;cr Lf 는 위에서 정의 한 값인 16진수를 사용(\n\r)효과
sum       BYTE 11 DUP (?)
             BYTE cr, Lf, 0                          ;변수명 없이 메모리만 할당(sum뒤에 이어서 cr과Lf 그리고 0이 오게된다.
.CODE                                      ;코드영역의 시작
_start:                                       ;start함수 (시작 지점을 의미)
   output prompt1                        ;output 은 메크로함수로 화면에 출력을 하는 메크로다.
   input string,40                         ;input은 입력을 받는 메크로다. 40바이트 만큼
   atod string                              ;atod는 아스키 코드를 10진수로 변환 하는 메크로다.(DWORD형으로저장후 레지스터eax에 넣어준다.)
   mov  number1,eax                    ;eax의 내용을 number1에 넣어준다. mov는 복사해주는 역할을 한다.
   
   output prompt2
   input string,40
   atod string                              ;위에서 연산된 값은 지워지고 새로운 값이 eax에 저장된다.
   mov  number2,eax
   
   mov  eax,number1     
   add  eax,number2                    ;뒤에값을 앞에 값과 더해 앞에 공간에 넣어준다. (a = a+ b 와 같다.)
   dtoa sum,eax                          ;eax에 있는 숫자를아스키 코드로 바꿔준다.(sum에 아스키로 바꾼 값을 담아준다.)
   output label1                           ;label1 BYTE cr, Lf, "The Sum is " 으로 정의 되어 있는 곳에 널문자가 없어 
                                                ;다음에 있는 sum부분의 널을 만날때까지 계속 출력한다.
   INVOKE ExitProcess,0              ;INVOKE는 함수를 호출하라는 명령어 함수명은 ExitProcess며 인자는 0이다.
   
PUBLIC _start                             ;PUBLIC 을 사용해서 외부로 부터의 접근을 허용한다.
END                                          ;프로그램 종료를 알리는 부분
[출처] 어셈블리어 기초 예제 코드|작성자 자의누리