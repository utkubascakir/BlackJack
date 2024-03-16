#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

// h: hearts(kupa), d: diamonds(karo), c: clubs(sinek), s: spades(maça)

void baslat(char *pd, char *ps, int *pc);
void kart_cekPlayer(char *pd, char *ps, int *pc);
void kart_cekComp(char *pd, char *ps, int *pc);
int toplaPlayer(char *pd, int *pc, int *toplam_player);
int toplaComp(char *pd, int *pc, int *toplam_comp);

int main() {

    char deck[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
    char symbol[4] = {'h', 'd', 'c', 's'}; 

    int control[52] = {0};
    int oyuncu=0, comp=0, i, check=0;
    int oyuncu_score=0, pc_score=0;
    char hamle;

    printf("\nh-Hearts(Kupa)\nd-Diamonds(Karo)\nc-Clubs(Sinek)\ns-Spades(Maca)\n\n1-Kart Cek\n2-Kal\n");
    printf("\n------------------------------------------------------------\n\n");
    Sleep(1000);

        baslat(deck, symbol, control);
        Sleep(1000);
        toplaComp(deck, control, &comp);
        //printf("\n\n\nBilgisayar: %d\n", toplaComp(deck, control, &comp));
        printf("\nOyuncu: %d\n\n\n", toplaPlayer(deck, control, &oyuncu));
        Sleep(1000);

        while (oyuncu<21 && comp<21) {

            //Oyuncu kart çekme
            printf("\nHamlenizi giriniz: ");
            hamle = getch();
            if (hamle == '1') {
        	    printf("\n\nYeni Kart:");
                Sleep(1000);
        	    kart_cekPlayer(deck, symbol, control);
                Sleep(1000);
        	    printf("\n\nOyuncu: %d\n", toplaPlayer(deck, control, &oyuncu));
        	    if (oyuncu>=21) break;
		    }
		    else if (hamle == '2') {
			    printf("\nKaldin.\n\n");
		    }
		    else printf("\nHatali hamle!\n");

		
            //Bilgisayar kart çekme		
		    if (comp<=16) {
			    printf("\n\nBilgisayar Yeni Kart:");
                Sleep(1000);
			    kart_cekComp(deck, symbol, control);
                Sleep(1000);
                toplaComp(deck, control, &comp);
			    //printf("\n\n\nBilgisayar: %d", toplaComp(deck, control, &comp));
			    if (comp>=21) break;
		    }
		    else {
                if (hamle == '2') {
                    printf("\nIkiniz de kaldiniz.\n");
                    check = 1;
                    break;
                }
            }

        }
        printf("\n\n\nBilgisayar: %d", toplaComp(deck, control, &comp));
        
        Sleep(1000);
        
        if (check == 0) {
        	if (oyuncu>21 || comp == 21) {
    	    	printf("\nTuru Kaybettin!\n");
    	    	pc_score++;
			}
			if (comp>21 || oyuncu == 21) {
				printf("\nTuru Kazandin!\n");
				oyuncu_score++;
			}
			if (oyuncu == comp) printf("\nBerabere\n");
		}
        // Kalarak mı bitti kontrolü
		if (check == 1) {
			if (oyuncu<comp) {
				printf("\nTuru Kaybettin!\n");
				pc_score++;
			}
			if (oyuncu>comp) {
				printf("\nTuru Kazandin!\n");
				oyuncu_score++;
			}
			if (oyuncu == comp) printf("\nBerabere\n");
		}

    printf("Skorun: %d\n", oyuncu_score);
    printf("Bilgisayarin skoru: %d\n", pc_score);
    system("pause");
    system("CLS");
    return 0;
}

int toplaComp(char *pd, int *pc, int *toplam_comp) { 

	*toplam_comp = 0;
	int i;
    for (i=0;i<52;i++) {
        if (pc[i] == 1) {
            if (i<13) { 
                if (pd[i] == 'A') {
                    *toplam_comp += ((*toplam_comp) + 11 > 21) ? 1 : 11;
                }
                else if (pd[i] == 'J' || pd[i] == 'Q' || pd[i] == 'K' || pd[i] == '0') {
                    *toplam_comp += 10;
                }
                else *toplam_comp += i+1;
            }
            else {
                if (pd[i%13] == 'A') {
                    *toplam_comp++;
                }
                else if (pd[i%13] == 'J' || pd[i%13] == 'Q' || pd[i%13] == 'K' || pd[i%13] == '0') {
                    *toplam_comp += 10;
                }
                else *toplam_comp += (i%13)+1;
            } 
        }      
    }
    return *toplam_comp;
}

int toplaPlayer(char *pd, int *pc, int *toplam_player) {
	
	*toplam_player = 0;
	int i;
    for (i=0;i<52;i++) {
        if (pc[i] == 2) {
            if (i<13) {
                if (pd[i] == 'A') {
                    *toplam_player += ((*toplam_player) + 11 > 21) ? 1 : 11;
                }
                else if (pd[i] == 'J' || pd[i] == 'Q' || pd[i] == 'K' || pd[i] == '0') {
                    *toplam_player += 10;
                }
                else *toplam_player += i+1;
            }
            else {
                if (pd[i%13] == 'A') {
                    *toplam_player += 1;
                }
                else if (pd[i%13] == 'J' || pd[i%13] == 'Q' || pd[i%13] == 'K' || pd[i%13] == '0') {
                    *toplam_player += 10;
                }
                else *toplam_player += (i%13)+1;
            } 
        }
    }
    return *toplam_player;
}

void baslat(char *pd, char *ps, int *pc) {

    srand(time(0));
    int deste, sembol;
    int x=0;
    printf("Bilgisayar: \n");
//Bilgisayara dağıtılıyor.
        deste = rand()%13;
        sembol = rand()%4;
        if (pc[(13*sembol+deste)]==0) {
            printf("---  ");
            //printf("%c-%c  ", ps[sembol], pd[deste]);
            pc[(13*sembol+deste)] = 1;
        }
        deste = rand()%13;
        sembol = rand()%4;
        if (pc[(13*sembol+deste)]==0) {
            printf("%c-%c  ", ps[sembol], pd[deste]);
            pc[(13*sembol+deste)] = 1;
        }
        

    x=0;
    printf("\n\n\n\n");
    printf("Sen: \n");
//Oyuncuya dağıtılıyor.
    while (x!=2) {
        deste = rand()%13;
        sembol = rand()%4;
        if (pc[(13*sembol+deste)]==0) {
            printf("%c-%c  ", ps[sembol], pd[deste]);
            pc[(13*sembol+deste)] = 2;
            x++;
        }
        
    }
}

void kart_cekPlayer(char *pd, char *ps, int *pc) {

    srand(time(0));
    int deste, sembol, x=0;
    while (x!=1) {
        deste = rand()%13;
        sembol = rand()%4;
        if (pc[(13*sembol+deste)]==0) {
            printf("\n%c-%c\n", ps[sembol], pd[deste]);
            pc[(13*sembol+deste)] = 2;
            x++;
        }
    }
}

void kart_cekComp(char *pd, char *ps, int *pc) {

    srand(time(0));
    int deste, sembol, x=0;
    while (x!=1) {
        deste = rand()%13;
        sembol = rand()%4;
        if (pc[(13*sembol+deste)]==0) {
            printf("\n%c-%c\n", ps[sembol], pd[deste]);
            pc[(13*sembol+deste)] = 1;
            x++;
        }
    }
}

