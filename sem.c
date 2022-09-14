
//
//
//

#include "sem.h"
#include "lex.h"
#define UNDECLARED  100
/* Errors of Semantic

    Type mismatch
    Undeclared variable
    Number of arguments in function

*/
//ERROR SEMANTIQUE
void Erreurs_Sem(enum Erreurs_Semantique err){
    int ind_err = err;
    printf("\nErreur Semantique numero %d\t:%s\n", ind_err, mess_err_sem[ind_err].mes);
    //getch();
    exit(EXIT_FAILURE);
}


int isIDDeclared(SYM token){
    int n = 0;
    while( strcmp(SYM_T[n].Name, token.Name ) && n < nSymbol )
        n++;

    // If Not declared
    if(n == nSymbol) return UNDECLARED;
    // If already declared
    return n;
}

// test if its already decleared
void TEST_ALREADY_ifDEC(char *dec){
    int i;
    for(i=0; i<CMP_TABSYM ; i++){

            if(SYM_T[i].id==id_courant){
                if(!strcmp(dec, SYM_T[i].Name))   Erreurs_Sem(DDEC);
        }

    }
}

// Check if the variable to assign is declared
void AFF_DEC(SYM Input, SYM Variable){
    int a=0,b=0;
    // If the input variable is not declared, it's an error
    if( (a = isIDDeclared(Input)) == UNDECLARED )
        Erreurs_Sem(DDEC);
    //
    if( (b = isIDDeclared(Variable)) == UNDECLARED){
        // Add this Symbol to the table
        strcpy (SYM_T[nSymbol].Name , Variable.Name);
        strcpy (SYM_T[nSymbol].Value , SYM_T[a].Value);
        SYM_T[nSymbol].TIDF = SYM_T[a].TIDF;
        nSymbol++;
        // If the variable is already declared, modify its information
    }else{
        strcpy (SYM_T[b].Value , SYM_T[a].Value);
        SYM_T[b].TIDF = SYM_T[a].TIDF;
    }

}

void Control_SYM_DATA(SYM Input, SYM Variable){
    int b=0;
    if( (b = isIDDeclared(Variable)) == UNDECLARED){
        // Add this Symbol to the table
        strcpy(SYM_T[nSymbol].Name , Variable.Name);
        strcpy (SYM_T[nSymbol].Value , Input.Value);
        SYM_T[nSymbol].TIDF = Input.TIDF;
        nSymbol++;
        // If the variable is already declared, modify its information
    }else{
        strcpy (SYM_T[b].Value , Input.Value);
        SYM_T[b].TIDF = Input.TIDF;
    }
}

void printSymbolTable(){
    int n = 0;

    while( n < nSymbol){
        printf("Name  :%s\tValue  :%s \n", SYM_T[n].Name , SYM_T[n].Value   );
        n++;
    }
}
