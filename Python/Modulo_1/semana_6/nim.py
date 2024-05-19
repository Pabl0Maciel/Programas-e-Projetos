def computador_escolhe_jogada(n,m):
    comp=n%(m+1)
    if comp==0:
        comp=1
    return comp

def usuario_escolhe_jogada(n,m):
    jog=int(input("Quantas peças voce quer tirar? "))
    while jog>m or jog>n or jog<1:
        print("Jogada invalida! Digite novamente!")
        jog=int(input("Quantas peças voce quer tirar? "))
    return jog


def partida():
    print("Bem-vindo ao jogo do NIM! Escolha:\n")
    print("1 - para jogar uma partida isolada")
    print("2 - para jogar um campeonato\n")
    resp=input("Digite a opcao: ")
    while resp!='1' and resp!='2':
        print("Resposta invalida! Digite 1 ou 2")
        resp=input("Digite a opcao: ")

    if resp=='1':
        print("Voce escolheu uma partida isolada!\n")
        n=int(input("Quantas peças? "))
        m=int(input("Limite de peças por jogada? "))
        while m<1 or n<1:
            print("valores invalidos! Digite novamente!")
            n=int(input("Quantas peças? "))
            m=int(input("Limite de peças por jogada? "))
        if n%(m+1)==0:
            print("Voce começa!")
            jogador_comeca=True
        else:
            print("Computador começa!")
            jogador_comeca=False
        while n>0:
            if jogador_comeca:
                jog=usuario_escolhe_jogada(n,m)
                n-=jog
                print("Voce tirou",jog,"peça(s). Restam",n,"peça(s) no tabuleiro.")
                if n<=0:
                    print("Fim do jogo! O jogador venceu!")
                    break

            else:
                comp=computador_escolhe_jogada(n,m)
                n-=comp
                print("O computador tirou",comp,"peça(s). Restam",n,"peça(s) no tabuleiro.")
                if n<=0:
                    print("Fim do jogo! O computador venceu!")
                    break
            jogador_comeca=not jogador_comeca
    else:
        print("Voce escolheu um campeonato!")
        i=1
        comp_final=0
        while i<=3:
            print("**** Rodada",i," ****")
            n=int(input("Quantas peças? "))
            m=int(input("Limite de peças por jogada? "))
            while m<1 or n<1:
                print("valores invalidos! Digite novamente!")
                n=int(input("Quantas peças? "))
                m=int(input("Limite de peças por jogada? "))

            if n%(m+1)==0:
                print("Voce começa!")
                jogador_comeca=True
            else:
                print("Computador começa!")
                jogador_comeca=False
            while n>0:
                if jogador_comeca:
                    jog_final=0
                    jog=usuario_escolhe_jogada(n,m)
                    n-=jog
                    print("Voce tirou",jog,"peça(s). Restam",n,"peça(s) no tabuleiro.")
                    if n<=0:
                        print("Fim do jogo! O jogador venceu!")
                        break

                else:
                    comp=computador_escolhe_jogada(n,m)
                    n-=comp
                    print("O computador tirou",comp,"peça(s). Restam",n,"peça(s) no tabuleiro.")
                    if n<=0:
                        print("Fim do jogo! O computador venceu!")
                        comp_final+=1
                        break
                jogador_comeca=not jogador_comeca
            i+=1    
        print("**** Final do Campeonato! ***")
        print("Placar: Voce 0 X",comp_final," Computador")


    

print(partida())
    