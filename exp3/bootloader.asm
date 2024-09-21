; MC504 - Experimento 3
; 
; Feito por
; - Lucca Miranda Nunes 230554
; - Yvens Ian Prado Porto 184031

BITS 16                         ; define que são 16 bits 
ORG 0x7C00                      ; define o endereço de origem do código (onde a BIOS carrega o bootloader)

start:                          
    mov si, mensagem            ; coloca a mensagem no registrador SI
    jmp print                   ; pula pro laço de impressão
print:
    lodsb                       ; carrega o byte apontado por SI no reg. AL e incrementa SI
    or al, al                   ; coloca o valor de AL na flag do processador   
    jz done                     ; se o valor na flag (AL) for 0, acaba a impressão
    mov ah, 0x0E                ; coloca o código de função de impressão (OxOE) em AH 
    int 0x10                    ; chama a interrupção de impressão da BIOS
    jmp print                   ; recomeça o loop para o proximo caractere
done:
    jmp done                    ; entra em loop infinito

mensagem db 'Hello, Boot!', 0   ; define a mensagem a ser impressa

TIMES 510-($-$$) db 0           ; completa o espaço restante com zeros
DW 0xAA55                       ; realiza a assinatura de bootloader para reconhecimento da BIOS