#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

	int pontos=0;
	char resposta, r;

	char *respostas[]={"a", "b", "b", "a", "b", "c", "a", "a", "b", "b", "a", "b", "b", "b", "b"};
	char *perguntas[]={
		"1 Nos nos estressamos quando:\n a. temos de nos adaptar ao nosso ambiente\n b. vamos fazer exames\n c. mudamos de trabalho\n Resposta:",
		"2. O hormonio secretado quando ha estresse e:\n a. o aperol\n b. o cortisol\n c. o sonasol\n Resposta:",
		"3. O estresse:\n a. e tratado do mesmo modo por todos\n b. pode ser fisico, psicologico e/ou emocional\n c. e um falso problema\n Resposta:",
		"4. Em geral, que doenca(s) nao e(sao) associada(s) ao estresse?\n a. a gripe\n b. alguns canceres\n c. as doencas cardiovasculares\n Resposta:",
		"5. Quem foi o primeiro cientista a estudar o estresse?\n a. Sigmund Freud\n b. Hans Selye\n c. Carl Rogers\n Resposta:",
		"6. Qual e a porcentagem de consultas medicas ligadas direta ou indiretamente ao estresse?\n a. 20\n b. 50\n c. 80\n Resposta:",
		"7. A respiracao diafragmatica e:\n a. uma fonte de relaxamento, pois permite oxigenar bem o sangue\n b. mais rapida que a respiracao natural\n c. uma respiracao que acontece essencialmente na parte de cima do corpo\n Resposta:",
		"8. O relaxamento muscular progressivo:\n a. centra-se na contracao e na descontracao fisica\n b. e uma especie de hipnose\n c. e uma disciplina esportiva\n Resposta:",
		"9. O estresse e:\n a. unicamente influenciado pelos eventos externos\n b. resultante da previsao de uma possivel ameaca e da capacidade de enfrenta-la\n c. uma emocao dificil\n Resposta:",
		"10. As distorcoes cognitivas sao:\n a. uma deformacao do estresse\n b. representacoes e interpretacoes distorcidas do mundo\n c. pensamentos apavorantes\n Resposta:",
		"11. O melhor meio de controlar os pensamentos e:\n a. confronta-los com a realidade\n b. procurar ter pensamentos pensativos\n c. procurar, a todo custo, evita-los\n Resposta:",
		"12. Entre as emocoes fundamentais, encontramos:\n a. a alegria, a vergonha, a aversao e a raiva\n b. a alegria, o medo, a raiva e a tristeza\n c. a alegria, o medo, a raiva e a vergonha\n Resposta:",
		"13. A inteligencia emocional e:\n a. equivalente ao Q.I\n b. fazer bom uso das emocoes, identificando-as, aceitando-as e admnistrando-as\n c. saber bloquear a emocao, se for necessario\n Resposta:",
		"14. A procrastinacao e:\n a. a tendencia a esquecer as coisas\n b. a tendencia de deixar para o dia seguinte\n c. o poder de antecipar\n Resposta:",
		"15. Um metodo de resolucao de problema pode:\n a. ajudar a procrastinar mais\n b. dividir-se em diversas etapas distintas: da definicao do problema a avaliacao dos resultados\n c. garantir-nos uma vida sem estresse\n Resposta:",
		};

	do{
		printf("Iniciar Quiz? Digite 's' para sim e 'n' para nao: ");
		scanf(" %c", &resposta);
		if(resposta=='n'){
			exit(0);
		}
		else if(resposta!='s'){
			printf("Resposta invalida! Digite apenas os caracteres indicados!\n");
		}

		for(int i=0; i<15; i++){
			do{
				printf("%s", perguntas[i]);
				scanf(" %c", &r);
				if (r!='a'&&r!='b'&&r!='c'){
					printf("Resposta invalida! Digite somente as letras das alternativas em minusculo!\n");
				}
				getchar();
			}while (r!='a'&&r!='b'&&r!='c');


				if (r==*respostas[i]){
					printf("Correto!\n");
					pontos++;
				}
				else{
					printf("Incorreto!\n");
				}
		}


		printf("Pontuacao: %d\n", pontos);
		printf("Jogar Novamente? Digite 's' para sim ou 'n' para nao: ");
		scanf(" %c", &resposta);
		if(resposta=='n'){
			printf("Obrigado por jogar!\n");
			break;
		}
	}while(resposta=='s');

	return 0;

}

