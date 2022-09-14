
#include "syn.h"
#include "lex.h"


int cursor=0;

void Test_Symbole (int cl , char* COD_ERR)
{
     if (SYMBOLES[cursor].code==cl)
    {
        cursor++;
    }else
    {
        printf("%s\n",COD_ERR);
        exit(-1);
    }

}

//CORPS ::= DECLARATION MAIN
void CORPS() {
    DECLARATION();
    MAIN();
}

//DECLARATION ::= TAB VARS FONCTIONS | eps
void DECLARATION()
{
        TAB();
        VARS();
        FONCTIONS();
}

//MAIN = debut INSTS fin     V
void MAIN()
{
    Test_Symbole(BEGIN_TOKEN,token_Err[BEGIN_TOKEN]);
    INSTS();
    Test_Symbole(END_TOKEN,token_Err[END_TOKEN]);
}

//TAB   	:=   tableau ID( NUM ) TYPE | eps   V
void TAB()
{
    switch (SYMBOLES[cursor].code)
    {
    case TAB_TOKEN:
        cursor++;
        Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
        Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
        Test_Symbole(NUM_TOKEN,token_Err[NUM_TOKEN]);
        Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
	    if (SYMBOLES[cursor].code==INT_TOKEN || SYMBOLES[cursor].code==FLOAT_TOKEN || SYMBOLES[cursor].code==STRING_TOKEN)
        {
            cursor++;
        }
        else {
            printf("error : expected type \n");
            exit(-1);}
        break;

    case VAR_TOKEN:
    case FUNCTION_TOKEN:
    case BEGIN_TOKEN:
        break;

    default:
        printf("Erreur variables or fonction or begin expected \n");
        exit(-1);
        break;
    }
}

//VARS = Variables  ID { ,ID }  TYPE | eps   V
void VARS()
{
    switch (SYMBOLES[cursor].code)
    {
    case VAR_TOKEN:
        cursor++;
        Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
        while (SYMBOLES[cursor].code==VIR_TOKEN)
        {
            cursor++;
            Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
        }

	    if (SYMBOLES[cursor].code==INT_TOKEN || SYMBOLES[cursor].code==FLOAT_TOKEN || SYMBOLES[cursor].code==STRING_TOKEN)
        {
            cursor++;
        }
        else{
            printf("ERROR : expected type \n");
             exit(-1);}
        break;

    case FUNCTION_TOKEN :
    case BEGIN_TOKEN:
        break;

    default:
        printf("Erreur expected Variables or fonction or debut\n");
        exit(-1);
        break;
    }
}

//FONCTIONS := FOCNTION{FONCTION}   V
void FONCTIONS()
{
    FONCTION();
    while(SYMBOLES[cursor].code == FUNCTION_TOKEN)
    {
        FONCTION();
    }
}

//FONCTION ::=  fonction ID (  ID {,ID} )  INSTS  RETURN   finFonction  |eps    V
void FONCTION()
{
    switch (SYMBOLES[cursor].code)
    {
    case FUNCTION_TOKEN:
        cursor++;
        Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
        Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
        if (SYMBOLES[cursor].code == ID_TOKEN ){
            cursor++;
            while (SYMBOLES[cursor].code==VIR_TOKEN)
            {
                cursor++;
                Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
            }
        }
            Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
            INSTS();
            RETURN();
            Test_Symbole(ENDFUNCTION_TOKEN,token_Err[ENDFUNCTION_TOKEN]);
        break;
    case BEGIN_TOKEN:
        break;

    default:
        printf("Erreur fonction or begin expected \n");
        exit(-1);
        break;
    }
}

//RETURN := return  EXPR    V
void RETURN()
 {
    Test_Symbole(RETURN_TOKEN,token_Err[RETURN_TOKEN]);
    EXPR();
 }

 //INSTS := INST{INST}  V
void INSTS()
{
    while(INST()){}
}

//INST = LIRE | ECRIRE | POUR | SI |TANTQUE | AFFECT|CALLFUNC | eps   V
int INST()
{
    switch (SYMBOLES[cursor].code)
    {
    case READ_TOKEN:
        LIRE();
        return 1;
        break;
    case WRITE_TOKEN:
        ECRIRE();
        return 1;
        break;
    case FOR_TOKEN:
        POUR(); return 1;
        break;
    case IF_TOKEN:
        SI(); return 1;
        break;
    case WHILE_TOKEN:
        TANTQUE(); return 1;
        break;
    case ID_TOKEN:
        cursor++;
        if (SYMBOLES[cursor].code == AFF_TOKEN)
           {
               AFFEC();
            return 1; }
        if (SYMBOLES[cursor].code==PO_TOKEN)
           { CALLFUNC(); return 1;}
        break;
    default:
        return 0;
        break;
    }
}

//AFFEC ::= ID $ EXPR    V
void AFFEC()
{
    Test_Symbole(AFF_TOKEN,token_Err[AFF_TOKEN]);
    EXPR();
}

//SI ::= si  COND alors  INST  {sinon  INST}  finsi    V
void SI()
{
    Test_Symbole(IF_TOKEN,token_Err[IF_TOKEN]);
    CONDS();
    Test_Symbole(THEN_TOKEN,token_Err[THEN_TOKEN]);
    INSTS();
    switch (SYMBOLES[cursor].code)
    {
    case ELSE_TOKEN:
        cursor++;
        INSTS();
        break;
    case ENDIF_TOKEN:
        break;
    default:
        printf("Erreur finSi expected\n");
        exit(-1);
        break;
    }
}

//POUR ::= pour (ID dans NUM : NUM)  INSTS  finPour   V
void POUR()
 {
        Test_Symbole(FOR_TOKEN,token_Err[FOR_TOKEN]);
        Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
        Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
        Test_Symbole(IN_TOKEN,token_Err[IN_TOKEN]);
        Test_Symbole(NUM_TOKEN,token_Err[NUM_TOKEN]);
        Test_Symbole(PP_TOKEN,token_Err[PP_TOKEN]);
        Test_Symbole(NUM_TOKEN,token_Err[NUM_TOKEN]);
        Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
        INSTS();
        Test_Symbole(ENDFOR_TOKEN,token_Err[ENDFOR_TOKEN]);
 }

 //TANTQUE ::= TantQue ( CONDS)  INSTS FinTantQue    V
void TANTQUE()
{
        Test_Symbole(WHILE_TOKEN,token_Err[WHILE_TOKEN]);
        Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
        CONDS();
        Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
        INSTS();
        Test_Symbole(ENDWHILE_TOKEN,token_Err[ENDWHILE_TOKEN]);
}

//ECRIRE ::= ecrire  ( EXPR { , EXPR } )   V
void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN,token_Err[WRITE_TOKEN]);
    Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
    EXPR();
    while (SYMBOLES[cursor].code==VIR_TOKEN)
    {
        cursor++;
        EXPR();
    }

    Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
}

//LIRE ::= lire ( ID { , ID } )
void LIRE()
{
    Test_Symbole(READ_TOKEN,token_Err[READ_TOKEN]);
    Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
    Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
    while (SYMBOLES[cursor].code==VIR_TOKEN)
    {
        cursor++;
        Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
    }

    Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
}



///////////////////////////////////////////////////////

//CALLFUNC ::= ID ( { ID {,ID } })    V
void CALLFUNC()
{
    Test_Symbole(PO_TOKEN,token_Err[PO_TOKEN]);
    if (SYMBOLES[cursor].code == ID_TOKEN)
    {
        cursor++;
        while(SYMBOLES[cursor].code == VIR_TOKEN)
        {
        cursor++;
        Test_Symbole(ID_TOKEN,token_Err[ID_TOKEN]);
        }
    }
    Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
}




// COND :=  EXPR OPCON EXPR  //N<10 et I>2 ou i>0     V
void COND()
{

			EXPR();
            switch (SYMBOLES[cursor].code)
            {
                case INF_TOKEN:
                case INFEG_TOKEN:
                case SUP_TOKEN:
                case SUPEG_TOKEN:
                case DIFF_TOKEN:
                case EQL_TOKEN:
                    cursor++;
                    break;

                default:
                    printf("Erreur: operateur de comparaison expected\n");
                    exit(-1);
                    break;
                }
            EXPR();
}

//CONDS ::= COND {OPLOG  COND}
void CONDS()
{   COND();
    while( (SYMBOLES[cursor].code == AND_TOKEN) || (SYMBOLES[cursor].code == OR_TOKEN) )
    {
        cursor++;
        COND();
    }
}

//EXPR ::= TERM { ADDOP TERM }   V
void EXPR()
{
    TERM();
    while (SYMBOLES[cursor].code==PLUS_TOKEN || SYMBOLES[cursor].code==MOINS_TOKEN)
    {
        cursor++;
        TERM();
    }
}

//TERM ::= FACT { MULOP FACT }    V
void TERM()
{
    FACT();
    while (SYMBOLES[cursor].code==MULT_TOKEN || SYMBOLES[cursor].code == DIV_TOKEN)
    {
        cursor++;
        FACT();
    }

}

//FACT ::= ID | NUM | ( EXPR ) | CALLFUNC   V
void FACT()
{
    switch (SYMBOLES[cursor].code)
    {
    case ID_TOKEN :
        cursor++;
        if (SYMBOLES[cursor].code == PO_TOKEN)  { CALLFUNC();}
        break;
    case NUM_TOKEN :
        cursor++;
        break;
    case PO_TOKEN :
        cursor++;
        EXPR();
        Test_Symbole(PF_TOKEN,token_Err[PF_TOKEN]);
        break;

    default:
        printf("Erreur: ( ,id or num  expected\n");
        exit(-1);
        break;
    }
}

void analyse_syn()
{
    CORPS();
    if (SYMBOLES[cursor].code==EOF_TOKEN)
    {
        printf("\n\n\nTHERE IS NO ERROR !!!\n");
    }
    else{
        printf("Erreur: !!!!!!!!!\n");
    }
}





