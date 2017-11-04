;asmsyntax=nasm
global huffman_build_tree
global huffman_initialize_table
global huffman_build_table

%define huffmanode [ebp + 4]
huffman_initialize_table:
	push ebp
	mov ebp, esp
	mov edi, huffmanode
	mov eax, 0
.while:
	cmp eax, 256
	jge .end_while:
	mov [edi + eax * 4], 0
	mov [edi + eax * 4 + 4], 0
	inc eax
	jmp .while:
.end_while:
	mov esp, ebp
	pop ebp
ret

%define heap     [ebp + 4]
%define heapnode [epb + 8]
huffman_build_tree:
	push ebp
	mov ebp, esp
.while:
	
.if:
.else:

.end_while:
	mov esp, ebp
	pop ebp
ret

%define root        [ebp + 4]
%define huffmannode [ebp + 8]
%define code 		[ebp + 12]
%define size		[ebp + 16]

huffman_build_table:
	push ebp
	mov ebp, esp
	

	mov esp, ebp
	pop ebp
ret

