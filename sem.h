//
//
//


#ifndef SEMANTIQUE_ANALYSEUR_SEMANTIQUE_H
#define SEMANTIQUE_ANALYSEUR_SEMANTIQUE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<conio.h>

#define  lenName 40
#define lenValue  40
#define MaxSymbole 50
typedef enum {TPROG, TCONST, TVAR} TSYM;

typedef  struct{
    int id ;
    TSYM TIDF;
    char Name[lenName];
    char Value[lenValue];


}SYM;

//SYM=symbole
SYM SYM_T[MaxSymbole];
int CMP_TABSYM=0;//compteur de symbole existant
int nSymbol=0;

int id_courant=-1;

enum Erreurs_Semantique {DDEC, INDEC, CCVNA, TND, NCT, VNS, CNE} ;
//DDEC <=> Double Declaration
//INDEC <=> Identifiant Non Declar�
//CCVNA <=> Constante Change Valeur Non Autoris�
struct Messages_Erreurs_Semantique { enum Erreurs_Semantique CODE_ERR; char mes[100]; };
struct Messages_Erreurs_Semantique mess_err_sem[] = {   {DDEC, "double d�claration"},
                                                        {INDEC, "identificateur non d�clar�"},
                                                        {CCVNA, "constante ne peut changer de valeur"},
                                                        {TND, "type non declarer"},
                                                        {NCT , "nom coh�rent type"},
                                                        {VNS, "ce variable est n'est pas de type structure"},
                                                        {CNE , "champs non exite dans cette structure"}
};

void Erreurs_Sem(enum Erreurs_Semantique err);
void TEST_ALREADY_DEC(SYM Input, SYM Variable);




#endif //SEMANTIQUE_ANALYSEUR_SEMANTIQUE_H

