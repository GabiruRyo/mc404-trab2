/*  Nome: Gabriel cuzao Ryo Hioki	RA: 172434
 *  Disciplina: MC404			Professor: Edson Borin
 *  Codigo para controle basico de ronda de um robo.
 *
 *  Descricao: Este codigo le os valores de sonares para rondar um mapa.
 * O metodo utilizado em seu algoritmo eh fazer o robo andar em quadrados
 * e ir aumentando o tamanho dos quadrados a cada volta. Se encontrar algum
 * obstaculo a frente, ele vira a direita e continua o seu curso.
 *  Arquivo: ronda.c
*/

#include "api_robot2.h"

#define LIMIAR 1200			// Limiar da distancia.
#define CURVA_QUADRADO 50	// Potencia do motor para virar aproximadamente 90 graus.
#define CURVA_LEVE 12		// Potencia do motor para virar aos poucos.
#define RETA 24				// Potencia do motor para sequir reto.

motor_cfg_t motor[2];				// Estrutura para os motores.
unsigned short sonar3, sonar4;		// Variaveis auxiliares para a leitura dos sonares.
unsigned char flag;					// Flag para auxiliar os callbacks.

void vira_inicio() {

	// Verifica se esta de frente a uma parede. Caso esteja, vira ate nao ficar mais.
	sonar3 = read_sonar(3);
	sonar4 = read_sonar(4);

	if((sonar3 > LIMIAR) && (sonar4 > LIMIAR))
		return;

	motor[1].speed = 12;
	set_motors_speed(motor, (motor + 1));

	// Laço que faz o virar a direita enquanto ele detecta que os sensores da frente
	// estao emitindo um numero menor que o LIMIAR.
	while(1) {
		sonar3 = read_sonar(3);
		sonar4 = read_sonar(4);
		// Quando ele virar e não estiver de frente a parede ele para.
		if((sonar3 > LIMIAR) && (sonar4 > LIMIAR)) {
			motor[0].speed = 0;
			motor[1].speed = 0;
			set_motors_speed(motor, (motor + 1));
			break;
		}
	}
}

void espiral() {
	int i, j, loop, timer;
	
	timer = 1000;
	loop = 1;
	for(i = 0; i < 50; i++) {
		// Quando der uma volta completa, ele aumenta o tamanho do quadrado.
		timer = timer + 500;
		for(j = 0; j < 4; j++) {
			register_proximity_callback()
			// Coloca o mesmo valor nos dois motores para ele andar reto.
			motor[0].speed = RETA;
			motor[1].speed = RETA;
			set_motors_speed(motor, (motor + 1));
			
			flag_alarme = 0;
			set_time(0);
			add_alarm(despertador, timer);
			while(loop) {
				if(flag_alarme)
					loop = 0;
			}
			motor[0].speed = 0;
			motor[1].speed = CURVA_QUADRADO;
			set_motors_speed(motor, (motor + 1));
		}
	}
}

void despertador() {
	flag = 1;
}

int main () {
	// Inicializa o id e a velocidade dos motores.
	motor[0].id = 0;
	motor[0].speed = 0;
	motor[1].id = 1;
	motor[1].speed = 0;

	vira_inicio();
	espiral();

	return 0;
}
