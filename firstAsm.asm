.386
.MODEL FLAT
;�Լ� ���  ����(ExitProcess �Լ��̸� �̸� ��ȯ���� DWORD)
ExitProcess PROTO NEAR32 stdcall, dxExitCode:DWORD
;������� ��Ŭ���
INCLUDE io.h
cr EQU 0dh         ;0dh => 0x0d (h �� 16������ ��Ÿ����.)#define ȿ��
Lf EQU 0ah         ; EQU�� (=) �� ����
.STACK 4096        ;���ÿ����� 4096��ŭ Ȯ��(����� �޸� ���� Ȯ��)
.DATA          ;���� ���� ����
number1  DWORD ?       ;4����Ʈ�� ���� ����
number2  DWORD ?
prompt1   BYTE "Enter first number: ",0  ;���ڸ� ����Ʈ ������ �Ҵ��ϰ� �������� 0�� �ִ´�. 0�� ���ڿ��� ���� �ʰ� (,0) �� ���
prompt2  BYTE "Enter second number: ",0
string     BYTE 40 DUP (?)                ;BYTE ������ 40���� DUP(�Ҵ�) �Ѵ�. (?) �� �ʱ�ȭ ���� �ʴ´ٴ� ��
label1    BYTE cr, Lf, "The Sum is "  ;cr Lf �� ������ ���� �� ���� 16������ ���(\n\r)ȿ��
sum       BYTE 11 DUP (?)
             BYTE cr, Lf, 0                          ;������ ���� �޸𸮸� �Ҵ�(sum�ڿ� �̾ cr��Lf �׸��� 0�� ���Եȴ�.
.CODE                                      ;�ڵ念���� ����
_start:                                       ;start�Լ� (���� ������ �ǹ�)
   output prompt1                        ;output �� ��ũ���Լ��� ȭ�鿡 ����� �ϴ� ��ũ�δ�.
   input string,40                         ;input�� �Է��� �޴� ��ũ�δ�. 40����Ʈ ��ŭ
   atod string                              ;atod�� �ƽ�Ű �ڵ带 10������ ��ȯ �ϴ� ��ũ�δ�.(DWORD������������ ��������eax�� �־��ش�.)
   mov  number1,eax                    ;eax�� ������ number1�� �־��ش�. mov�� �������ִ� ������ �Ѵ�.
   
   output prompt2
   input string,40
   atod string                              ;������ ����� ���� �������� ���ο� ���� eax�� ����ȴ�.
   mov  number2,eax
   
   mov  eax,number1     
   add  eax,number2                    ;�ڿ����� �տ� ���� ���� �տ� ������ �־��ش�. (a = a+ b �� ����.)
   dtoa sum,eax                          ;eax�� �ִ� ���ڸ��ƽ�Ű �ڵ�� �ٲ��ش�.(sum�� �ƽ�Ű�� �ٲ� ���� ����ش�.)
   output label1                           ;label1 BYTE cr, Lf, "The Sum is " ���� ���� �Ǿ� �ִ� ���� �ι��ڰ� ���� 
                                                ;������ �ִ� sum�κ��� ���� ���������� ��� ����Ѵ�.
   INVOKE ExitProcess,0              ;INVOKE�� �Լ��� ȣ���϶�� ��ɾ� �Լ����� ExitProcess�� ���ڴ� 0�̴�.
   
PUBLIC _start                             ;PUBLIC �� ����ؼ� �ܺη� ������ ������ ����Ѵ�.
END                                          ;���α׷� ���Ḧ �˸��� �κ�
[��ó] ������� ���� ���� �ڵ�|�ۼ��� ���Ǵ���