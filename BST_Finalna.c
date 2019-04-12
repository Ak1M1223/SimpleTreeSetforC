#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct WezelBST {
        int dane;

        struct WezelBST * lewy;
        struct WezelBST * prawy;

        struct WezelBST * rodzic;
};
void Dodaj(struct WezelBST ** korzen, int liczba) {
        if(*korzen) {
                struct WezelBST * tmp = *korzen;

                struct WezelBST * nowy = (struct WezelBST*) malloc(sizeof(struct WezelBST));
                nowy->dane = liczba;
                nowy->lewy = 0;
                nowy->prawy = 0;

                while(1) {
                        if(liczba > tmp->dane) {
                                if(tmp->prawy) {
                                        tmp=tmp->prawy;
                                } else {
                                        nowy->rodzic = tmp;
                                        tmp->prawy = nowy;
                                        break;
                                }
                        } else {
                                if(tmp->lewy) {
                                        tmp=tmp->lewy;
                                } else {
                                        nowy->rodzic = tmp;
                                        tmp->lewy = nowy;
                                        break;
                                }
                        }
                }
        } else {
                *korzen = (struct WezelBST *)malloc(sizeof(struct WezelBST));
                (*korzen)->lewy = 0;
                (*korzen)->prawy = 0;
                (*korzen)->rodzic = 0;
                (*korzen)->dane = liczba;
        }
}

void Wypisz(struct WezelBST * korzen) {
        if(korzen) {
        		printf("%X %d %X %X %X\n", korzen, korzen->dane, korzen->rodzic, korzen->lewy, korzen->prawy);
                Wypisz(korzen->lewy);
                Wypisz(korzen->prawy);

        }
}

struct WezelBST * Znajdz(struct WezelBST * korzen, int znajdz) {
        if(korzen) {
                if(korzen->dane == znajdz) return korzen;
                if(znajdz < korzen->dane) {
                        return Znajdz(korzen->lewy, znajdz);
                } else {
                        return Znajdz(korzen->prawy, znajdz);
                }
        } else {
                return 0;
        }
}

typedef struct arr {
    char str[512];
};
struct arr cr, cl, cp;

unsigned log2(unsigned x)
{
    unsigned y = 1;
    while ((x >>= 1) > 0) y <<= 1;
    return y;
}

void printBT(struct arr sp, struct arr sn, struct WezelBST * v)
{
    struct arr s;
    struct arr pom;

    if (v != NULL)
    {
        strcpy(s.str, sp.str);
        if (strcmp(sn.str, cr.str) == 0) s.str[(int)strlen(s.str) - 2] = ' ';
        strcpy(pom.str, s.str);
        strcat(pom.str, cp.str);
        printBT(pom, cr, v->prawy);
 		int i;
        for (i = 0; i < (int)strlen(sp.str) - 2; i++) {
            printf("%c", s.str[i]);
        }

            printf("%s%d\n", sn.str, v->dane);

        strcpy(s.str, sp.str);
        if (strcmp(sn.str, cl.str) == 0) s.str[(int)strlen(s.str) - 2] = ' ';
        strcpy(pom.str, s.str);
        strcat(pom.str, cp.str);
        printBT(pom, cl, v->lewy);
    }
}

int WypiszWys(struct WezelBST * korzen,int wys){
	int wys1,wys2;
	if(korzen) {
        		wys1=WypiszWys(korzen->lewy,wys+1);
        		wys2=WypiszWys(korzen->prawy,wys+1);
        		if(wys1>wys2)wys=wys1;
        		else wys=wys2;
        }
        return wys;
}

struct WezelBST* rotateR(struct WezelBST* korzen, struct WezelBST* obr) {
    struct WezelBST * b = obr->lewy;
    struct WezelBST * p = obr->rodzic;

    if (b != NULL) {
        obr->lewy = b->prawy;
        if (obr->lewy != NULL)
            obr->lewy->rodzic = obr;
        b->prawy = obr;
        b->rodzic = p;
        obr->rodzic = b;

        if (p != NULL) {
            if (p->lewy == obr)
                p->lewy = b;
            else p->prawy = b;
        }
        else korzen = b;
    }
    return korzen;
}

struct WezelBST* rotateL(struct WezelBST* korzen, struct WezelBST* obr) {
    struct WezelBST* b = obr->prawy;
    struct WezelBST* p = obr->rodzic;

    if (b != NULL) {
        obr->prawy = b->lewy;
        if (obr->prawy != NULL)
            obr->prawy->rodzic = obr;
        b->lewy = obr;
        b->rodzic = p;
        obr->rodzic = b;

        if (p != NULL) {
            if (p->lewy == obr)
                p->lewy = b;
            else p->prawy = b;
        }
        else korzen = b;
    }
    return korzen;
}

struct WezelBST* balanceTree(struct WezelBST* korzen) {
    unsigned int n, s;
    struct WezelBST* wsk;
    n = 0;
    wsk = korzen;
    while (wsk != NULL)
        if (wsk->lewy != NULL) {
            korzen = rotateR(korzen, wsk);
            wsk = wsk->rodzic;
        }
        else {
            n++;
            wsk = wsk->prawy;
        }
        s = n + 1 - log2(n + 1);
        wsk = korzen;
        int i;
        for (i = 0; i < s;i++) {
            korzen = rotateL(korzen, wsk);
            wsk = wsk->rodzic->prawy;
        }

        n = n - s;
        while (n > 1) {
            n >>= 1;
            wsk = korzen;
            for (i = 0; i < n; i++) {
                korzen = rotateL(korzen, wsk);
                wsk = wsk->rodzic->prawy;
            }
        }
        return korzen;
}

struct WezelBST ** Pierwszy(struct WezelBST ** korzen){
	while((*korzen)->rodzic){
		(*korzen)=(*korzen)->rodzic;

	}
	return korzen;
}

Scanner myObj = new Scanner(System.in);
void usun_drzewo(struct WezelBST *korzen)
{
        if (korzen->lewy!=NULL)
                usun_drzewo(korzen->lewy);
        if (korzen->prawy!=NULL)
                usun_drzewo(korzen->prawy);
        free(korzen);
}
void CzyBST(struct WezelBST **korzen){
		struct WezelBST *wsk=*korzen;
		if(wsk->lewy){
			if(wsk->dane>=wsk->lewy->dane){
				CzyBST(wsk->lewy);
			}else{
				printf("\nDRZEWO NIE JEST BST!\n");
			}
		}
		if(wsk->prawy){
			if(wsk->dane<wsk->prawy->dane){
				CzyBST(wsk->prawy);
			}else{
				printf("\nDRZEWO NIE JEST BST!\n");
			}
		}
}
int main(int argc, char *argv[]) { /////////////////////////////////////////////////////////////MAIN/////////////////////////////////////////////////////////
        struct WezelBST * korzen = 0;
        int ilosc=10;
 		//scanf("%d",&ilosc);
 		printf("\n");
        Dodaj(&korzen, 4);
        int i;
        for(i = 0 ; i < ilosc; i++) {
                int liczba = rand()%10;
                Dodaj(&korzen, liczba);
                printf("%d ", liczba);
        }
        printf("\n");
        Wypisz(korzen);
        cr.str[0] = 218; cr.str[1] = 196;//ramki do malowania drzewka
   		cl.str[0] = 192; cl.str[1] = 196;
   		cp.str[0] = 179; cp.str[1] = 32;
    	struct arr nothing;//dumb structure
    	printBT(nothing, nothing, korzen);
        printf("\n==================================");
        printf("\nWYS:%d",WypiszWys(korzen,0));
        printf("\n==================================\n");
        printf("WYPISYWANIE KOMUNIKATU JEZELI DRZEWO NIE JEST BST:");
        CzyBST(&korzen);
        korzen=balanceTree(korzen);
        int wys;
        wys= WypiszWys(korzen,0);
        Wypisz(korzen);

        printBT(nothing, nothing, korzen);
        printf("\n==================================");
        printf("\nWYS:%d",wys);
        printf("\n==================================\n");
		//usun_drzewo(korzen);
		//printBT(nothing,nothing,korzen);
        return 0;
}
