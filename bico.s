@ Parte BiCo do Trabalho 2
@ Nome: Gabriel Ryo Hioki	RA: 172434
@ Disciplina: MC404 		Professor: Edson Borin
@ COMENTAR COMENTAR

.global read_sonar
.global read_sonars
.global register_proximity_callback
.global set_motor_speed
.global set_motors_speed
.global get_time
.global set_time
.global set_alarm

.text
_start:

@ Implementa a rotina de read_sonar.
read_sonar:
	push {r7, lr}

	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	mov r7, #16
	svc 0x0

	pop {r7, pc}

@ Implementa a rotina de read_sonars.
read_sonars:
	push {r4-r8, lr}

	mov r4, r0
	add r5, r1, #1
	mov r6, r2
	mov r8, #0

@ Laco para ler todos os sonares desejados e armazenar o valor deles em um vetor.
read_sonars_loop:
	mov r0, r4

	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	mov r7, #16
	svc 0x0

	str r0, [r6, r8]

	add r8, r8, #4
	add r4, r4, #1
	cmp r4, r5
	blo read_sonars_loop

	pop {r4-r8, pc}

@ Implementa a rotina de register_proximity_callback.
register_proximity_callback:
	push {r7, lr}

	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	mov r7, #17
	svc 0x0

	pop {r7, pc}

@ Implementa a rotina de set_motor_speed.
set_motor_speed:
	push {r7, lr}

	@ Como o parametro eh um apontadore do tipo motor_cfg_t, para pegar
	@os valores do id e da velocidade, que estao definidos como tipo char,
	@deve-se recuperar da memoria os dois bytes correspondetes a eles( o
	@primeiro e o segundo a partir do endereco do apontador) e colocar em
	@r0 e r1 para serem utilizados na funcao.
	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	ldrb r1, [r0, #1]
	ldrb r0, [r0]
	mov r7, #18
	svc 0x0

	pop {r7, pc}

@ Implementa a rotina de set_motors_speed.
set_motors_speed:
	push {r7, lr}

	@ Pega o segundo byte dos enderecos de motores passados como parametros
	@para pegar apenas a velocidade de cada motor e coloca a velocidade do
	@motor 0 em r0 e do motor 1 em r1.
	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	ldrb r0, [r0, #1]
	ldrb r1, [r1, #1]
	mov r7, #19
	svc 0x0

	pop {r7, pc}

@ Implementa a rotina de get_time.
get_time:
	push {r7, lr}

	@ Passa o endereco como parametro em r0. Dessa maneira pode-se colocar
	@o valor desejado na memoria.
	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	mov r7, #20
	svc 0x0

	pop {r7, pc}

@ Implementa a rotina de set_time.
set_time:
	push {r7, lr}

	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	mov r7, #21
	svc 0x0

	pop {r7, pc}

@ Implementa a rotina de set_alarm.
add_alarm:
	push {r7, lr}

	@ Coloca o valor correspondente a chamada em r7 e realiza a syscall.
	mov r7, #22
	svc 0x0

	pop {r7, pc}
