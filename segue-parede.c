/*  Nome: Gabriel cuzao Ryo Hioki	RA: 172434
 *  Disciplina: MC404			Professor: Edson Borin
 *  Codigo para controle basico de um robo para contornar um mapa.
 *
 *  Descricao: Este codigo le os valores de sonares para chegar ate uma
 * parede e seguir o caminho sempre mantendo a parede a sua esquerda.
 *  Arquivo: segue-parede.c
 */

#include "api_robot2.h"

#define LIMIAR_PERTO 500			// Limiar para um sonar especifico.
#define LIMIAR 1200					// Limiar da distancia.
#define LEVE 7					// Potencia do motor para virar aos poucos.
#define RAPIDO 27						// Potencia do motor para sequir reto.

void _start ();
void encontra_parede();
void encontrou();
void vira_direita();
void contorna_parede();

motor_cfg_t motor[2];
int flag;

/*	Funcao main
*/
void _start () {
//	motor_cfg_t motor[2];			// Estrutura para os motores.

	// Inicializa o id e a velocidade dos motores.
	motor[0].id = 0;
	motor[1].id = 1;
	// Escreve a velociade como 24 em ambos os motores.
	motor[0].speed = RAPIDO;
	motor[1].speed = RAPIDO;
	set_motors_speed(motor, (motor + 1));

	// Chamada das funcoes de encontrar e seguir a parede.
	encontra_parede();

	contorna_parede();
}

/*  Funcao que faz o robo andar reto ate encontrar uma parede.
 * Depois de encontrar, vira ate a parede ficar em sua esquerda.
 *  Parametros:
 *    motor_cfg_t motor[], a estrutuca com os dois motores.
 */
void encontra_parede() {
	int loop = 1, sonar = 3, dist = LIMIAR;
	unsigned short sonar3, sonar4;	// Variaveis auxiliares para a leitura
	// Espera o proximity callback ser acionado com um laco.

	register_proximity_callback(sonar, dist, encontrou);

	flag = 0;
	while(loop == 1) {
		if(flag == 1) {
			loop = 0;
		}
	}

	motor[0].speed = 0;
	motor[1].speed = 0;
	set_motors_speed(motor, (motor + 1));

	vira_direita();
}

void encontrou() {
	if(flag == 0)
		flag = 1;
}

void vira_direita() {
	int loop = 1;
	unsigned short sonar0;	// Variaveis auxiliares para a leitura dos sonares.

	// Manda o robo ir para a direta.
	motor[1].speed = LEVE;
	set_motor_speed(motor + 1);

	// Laco que faz o robo parar  de virar a direita depois de ter
	//encontrado a parede no sensor da esquerda e a frente estiver livra.
	while(loop == 1) {
		sonar0 = read_sonar(0);
		// Quando ele virar e nao estiver de frente a parede ele para.
		if(sonar0 <= LIMIAR) {
			motor[0].speed = 0;
			motor[1].speed = 0;
			set_motors_speed(motor, (motor + 1));
			loop = 0;
		}
	}
}

/*  Funcao que faz o Uoli contornar a parede sem bater. Quando
 * ele chega de frente a uma parede, ele vira para a direita.
 *  Parametros:
 *    motor_cfg_t motor[], a estrutura com os dois motores.
 */
void contorna_parede() {
	unsigned int loop = 1;
	unsigned short sonar1, sonar4;	// Variaveis auxiliares para a leitura dos sonares.
	while(loop == 1) {
		sonar1 = read_sonar(1);
		// Se estiver com a parede em sua esquerda
		if(sonar1 <= LIMIAR) {
			sonar4 = read_sonar(4);
			// Este caso eh se houver bloqueio a frente ou estiver muito proximo
			//a parede, faz ir para a direita.
			if(sonar1 <= LIMIAR_PERTO || sonar4 <= LIMIAR_PERTO) {
				motor[0].speed = 0;
				motor[1].speed = LEVE;
				set_motors_speed(motor, (motor + 1));
			}
			// Se nao, vai reto.
			else {
				motor[0].speed = RAPIDO;
				motor[1].speed = RAPIDO;
				set_motors_speed(motor, (motor + 1));
			}
		}
		// Se ele se perder, anda para frente ate achar algo.
		else if(sonar1 > LIMIAR && sonar4 > LIMIAR) {
			motor[0].speed = RAPIDO;
			motor[1].speed = RAPIDO;
			set_motors_speed(motor, (motor + 1));
		}
		// Se nao estiver com a parede em sua esquerda, vira a esquerda.
		else {
			motor[0].speed = LEVE;
			motor[1].speed = 0;
			set_motors_speed(motor, (motor + 1));
		}
	}
}
