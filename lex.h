#ifndef MY_LEX_H
#define MY_LEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char mot[255];
    enum
	{
            VAR_TOKEN,
            TAB_TOKEN,
            BEGIN_TOKEN,
            FOR_TOKEN,
            IN_TOKEN,
            ENDFOR_TOKEN,
            ENDIF_TOKEN,
            END_TOKEN,
            IF_TOKEN,
            ELSE_TOKEN,
            THEN_TOKEN,
            WHILE_TOKEN,
            ENDWHILE_TOKEN,
            READ_TOKEN,
            WRITE_TOKEN,
            STRING_TOKEN,
            ID_TOKEN,
            INT_TOKEN,
            FLOAT_TOKEN,
            AND_TOKEN,
            OR_TOKEN,
            AFF_TOKEN,
            INF_TOKEN,
            INFEG_TOKEN,
            SUP_TOKEN,
            SUPEG_TOKEN,
            DIFF_TOKEN,
            EQL_TOKEN,
            PO_TOKEN,
            PF_TOKEN,
            VIR_TOKEN,
            PP_TOKEN,
            PLUS_TOKEN,
            MOINS_TOKEN,
            MULT_TOKEN,
            DIV_TOKEN,
            NUM_TOKEN,
            FUNCTION_TOKEN,
            ENDFUNCTION_TOKEN,
            RETURN_TOKEN,
            EOF_TOKEN


	} code;
    char type[20];
} structToken;


static char token_Sym[100][20]= {
        "VAR_TOKEN",
        "TAB_TOKEN",
        "BEGIN_TOKEN",
        "FOR_TOKEN",
        "IN_TOKEN",
        "ENDFOR_TOKEN",
        "ENDIF_TOKEN",
        "END_TOKEN",
        "IF_TOKEN",
        "ELSE_TOKEN",
        "THEN_TOKEN",
        "WHILE_TOKEN",
        "ENDWHILE_TOKEN",
        "READ_TOKEN",
        "WRITE_TOKEN",
        "STRING_TOKEN",
        "ID_TOKEN",
        "INT_TOKEN",
        "FLOAT_TOKEN",
        "AND_TOKEN",
        "OR_TOKEN",
        "AFF_TOKEN",
        "INF_TOKEN",
        "INFEG_TOKEN",
        "SUP_TOKEN",
        "SUPEG_TOKEN",
        "DIFF_TOKEN",
        "EQL_TOKEN",
        "PO_TOKEN",
        "PF_TOKEN",
        "VIR_TOKEN",
        "PP_TOKEN",
        "PLUS_TOKEN",
        "MOINS_TOKEN",
        "MULT_TOKEN",
        "DIV_TOKEN",
        "NUM_TOKEN",
        "FUNCTION_TOKEN",
        "ENDFUNCTION_TOKEN",
        "RETURN_TOKEN",
        "EOF_TOKEN"

    };
static char token_Err[100][50]={
        "expected Variables",
        "expected tableau",
        "expected debut",
        "expected pour",
        "expected dans",
        "expected finpour",
        "expected finSi",
        "expected fin",
        "expected Si",
        "expected sinon",
        "expected alors",
        "expected tantQue",
        "expected FinTantQue",
        "expected lire",
        "expected ecrire",
        "expected chaine",
        "expected ID",
        "expected entier",
        "expected reel",
        "expected et",
        "expected ou",
        "expected affectation",
        "expected INF_TOKEN",
        "expected INFEG_TOKEN",
        "expected SUP_TOKEN",
        "expected SUPEG_TOKEN",
        "expected DIFF_TOKEN",
        "expected EQL_TOKEN",
        "expected PO_TOKEN",
        "expected PF_TOKEN",
        "expected VIR_TOKEN",
        "expected PP_TOKEN",
        "expected PLUS_TOKEN",
        "expected MOINS_TOKEN",
        "expected MULT_TOKEN",
        "expected DIV_TOKEN",
        "expected NUM_TOKEN",
        "expected FUNCTION_TOKEN",
        "expected ENDFUNCTION_TOKEN",
        "expected RETURN_TOKEN",
        "expected EOF_TOKEN"
    };


structToken SYMBOLES[255];


static int listSymbolesLen=0;

FILE * Ouvrir_Fichier(char* file);
int get_mot_cle(char* mot);
structToken Sym_Suiv(FILE* file,char ch);
void storeToken(structToken token );
void analyse_lex(char* file);









#endif

