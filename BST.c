#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct WezelBST {
        int dane;
 
        struct WezelBST * lewy;
        struct WezelBST * prawy;
        
        struct WezelBST * rodzic;
};
 
void Dodaj(struct WezelBST ** korzen, int liczba);
void Wypisz(struct WezelBST * korzen);
 
struct WezelBST * Znajdz(struct WezelBST * korzen, int find);

typedef struct arr {//to c wiec aby przekazac char[] przez wartosc potrzebna jest struktura oslonowa
    char str[512];
};
struct arr cr, cl, cp;//globalne ramki

unsigned log2(unsigned x)
{
    unsigned y = 1;
 
    while ((x >>= 1) > 0) y <<= 1;
 
    return y;
}

void printBT(struct arr sp, struct arr sn, struct WezelBST * v)//malowanie drzewa w c, czyli bawienie sie c stringami
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

/*void RotujWPrawo(struct WezelBST *wsk) {
		struct WezelBST * temp = wsk->lewy; //temp = temp wsk = wsk
		temp->rodzic=wsk->rodzic;
		if(temp->prawy){
			//printf(" prawy \n");
			wsk->lewy=temp->prawy;
			wsk->lewy->rodzic=wsk;
			if(wsk->rodzic){
				wsk->rodzic->prawy=temp;
				temp->rodzic=wsk->rodzic;
			}
			wsk->rodzic=temp;
			wsk->rodzic->prawy=wsk;	
		
		}
		else if(temp->rodzic) {
			//printf(" ma rodzica \n");
			temp->rodzic=wsk->rodzic;
			wsk->rodzic=temp;
			wsk->rodzic->prawy=wsk;
			temp->rodzic->prawy=temp;
			wsk->lewy=NULL;
		}else{
			//printf("brak rodzica\n");
			wsk->rodzic=temp;			//
			wsk->lewy=temp->prawy;		//
			temp->prawy=wsk;
		}
		
}*/
struct WezelBST* rotateR(struct WezelBST* root, struct WezelBST* rot) {
    struct WezelBST * b = rot->lewy;
    struct WezelBST * p = rot->rodzic;
 
    if (b != NULL) {
        rot->lewy = b->prawy;
        if (rot->lewy != NULL)
            rot->lewy->rodzic = rot;
        b->prawy = rot;
        b->rodzic = p;
        rot->rodzic = b;
 
        if (p != NULL) {
            if (p->lewy == rot)
                p->lewy = b;
            else p->prawy = b;
        }
        else root = b;
    }
    return root;
}
struct WezelBST* rotateL(struct WezelBST* root, struct WezelBST* rot) {
    struct WezelBST* b = rot->prawy;
    struct WezelBST* p = rot->rodzic;
 
    if (b != NULL) {
        rot->prawy = b->lewy;
        if (rot->prawy != NULL)
            rot->prawy->rodzic = rot;
        b->lewy = rot;
        b->rodzic = p;
        rot->rodzic = b;
 
        if (p != NULL) {
            if (p->lewy == rot)
                p->lewy = b;
            else p->prawy = b;
        }
        else root = b;
    }
    return root;
}
struct WezelBST* balanceTree(struct WezelBST* root) {
	//pierwsza faza
    unsigned int n, s;
    struct WezelBST* p;
    n = 0;
    p = root;
    while (p != NULL)
        if (p->lewy != NULL) {
            root = rotateR(root, p);
            p = p->rodzic;
        }
        else {
            n++;
            p = p->prawy;
        }
 		//druga faza
        s = n + 1 - log2(n + 1);
        p = root;
        int i;
        for (i = 0; i < s;i++) {
            root = rotateL(root, p);
            p = p->rodzic->prawy;
        }
 
        n = n - s;
        while (n > 1) {
            n >>= 1;
            p = root;
            for (i = 0; i < n; i++) {
                root = rotateL(root, p);
                p = p->rodzic->prawy;
            }
        }
        return root;
}
/* Pseudokod ilustruj¹cy powstawanie krêgos³upa, wskutek dzia³ania pierwszej fazy DSW
   TworzKregoslup (wêze³ korzen, liczba ca³kowita n)
       tmp = korzen; //tmp to zmienna tymczasowa
       while tmp nie jest równe NULL
           if tmp posiada lewego potomka
               wykonaj rotacjê tego potomka wzglêdem tmp; //Czyli lewy potomek zostaje ojcem wêz³a tmp
               tmp zostaje przesuniêty do nowo powsta³ego rodzica;
           else
               tmp zostaje przesuniêty w miejsce swojego prawego potomka; */
/*void Faza1 (struct WezelBST ** korzen){
	struct WezelBST *wsk = *korzen;
	int i =0;
	while(wsk){
		i++;
		if(wsk->lewy){
			printf("\nROT:%d",i);
			RotujWPrawo(wsk);
			wsk=wsk->rodzic;
			
		}
		else {
			wsk=wsk->prawy;
			printf("\nPRZ:%d \n",i);
		}
		
	}
}
void Faza2 (struct WezelBST ** korzen,int wezly){
	struct WezelBST *wsk = *korzen;
	printf("M:");
	float m =pow(2,floor(log2f((float)wezly)))-1;
	printf("%f\n",m);
}*/
struct WezelBST ** Pierwszy(struct WezelBST ** korzen){
	while((*korzen)->rodzic){
		(*korzen)=(*korzen)->rodzic;
		
	}
	return korzen;
}
int main(int argc, char *argv[]) { /////////////////////////////////////////////////////////////MAIN/////////////////////////////////////////////////////////
        struct WezelBST * korzen = 0;
        int ilosc=40;
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
        //Wypisz(korzen);
        cr.str[0] = 218; cr.str[1] = 196;//ramki do malowania drzewka
   		cl.str[0] = 192; cl.str[1] = 196;
   		cp.str[0] = 179; cp.str[1] = 32;
    	struct arr nothing;//dumb structure
    	printBT(nothing, nothing, korzen);
        printf("\n==================================");
        printf("\nWYS:%d",WypiszWys(korzen,0));
        printf("\n==================================\n");
        //Faza1(&korzen);
        korzen=balanceTree(korzen);
        //Pierwszy(&korzen);
        int wys;
        wys= WypiszWys(korzen,0);
        //Faza2(&korzen,wys);
        //Wypisz(korzen);
        
        printBT(nothing, nothing, korzen);
        printf("\n==================================");
        printf("\nWYS:%d",wys);
        printf("\n==================================\n");
        
        return 0;
} 
struct WezelBST * Znajdz(struct WezelBST * korzen, int find) {
        if(korzen) {
                if(korzen->dane == find) return korzen;
                if(find < korzen->dane) {
                        return Znajdz(korzen->lewy, find);
                } else {
                        return Znajdz(korzen->prawy, find);
                }
        } else {
                return 0;
        }
}
void Dodaj(struct WezelBST ** korzen, int liczba) {             //DODAWANIE LICZBY
        if(*korzen) {
                struct WezelBST * tmp = *korzen; //TWORZENIE TYMCZASOWAEGO?
                
                struct WezelBST * nowy = (struct WezelBST*) malloc(sizeof(struct WezelBST)); //TWORZENIE NOWEGO
                nowy->dane = liczba;
                nowy->lewy = 0;
                nowy->prawy = 0;
                
                while(1) {
                        if(liczba > tmp->dane) { // tmp->dane<liczba
                                //To dodaj po prawej stronie
                                if(tmp->prawy) { //istnieje prawy
                                        tmp=tmp->prawy; //przesuniecie znacznika na prawe dziecko
                                } else { //przypisywanie
                                        nowy->rodzic = tmp;
                                        tmp->prawy = nowy;
                                        break;  
                                }
                        } else {
                                //To dodaj po lewej stronie
                                if(tmp->lewy) {
                                        tmp=tmp->lewy;
                                } else {
                                        nowy->rodzic = tmp;
                                        tmp->lewy = nowy;
                                        break;
                                }
                        }
                }       
        } else { //tworzenie pierwszeeeeego
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
