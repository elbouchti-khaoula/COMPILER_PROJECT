#include "lex.h"

FILE * Ouvrir_Fichier(char* file){  //Ouverture du fichier

    FILE *fp ;
    fp = fopen(file,"r");

    if (fp == NULL ) // au cas d'erreur
    {
        perror("Error while opening the file . \n");
        exit (EXIT_FAILURE);
    }
    return fp ;
}

int get_mot_cle (char* mot){  //verifier et retourner les mots cles

    if (strcmp(mot,"Variables")==0){
         return VAR_TOKEN ;
    }
    else if (strcmp(mot,"tableau")==0){
        return TAB_TOKEN;
    }
    else if (strcmp(mot,"fonction")==0){
        return FUNCTION_TOKEN;
    }
    else if (strcmp(mot,"finFonction")==0){
        return ENDFUNCTION_TOKEN;
    }
    else if (strcmp(mot,"return")==0){
        return RETURN_TOKEN;
    }
    else if (strcmp(mot,"Debut")==0){
        return BEGIN_TOKEN;
    }
    else if (strcmp(mot,"Fin")==0){
        return END_TOKEN;
    }
    else if (strcmp(mot,"Ecrire")==0){
        return WRITE_TOKEN;
    }
    else if (strcmp(mot,"Lire")==0){
        return READ_TOKEN ;
    }
    else if (strcmp(mot,"Pour")==0){
        return FOR_TOKEN ;
    }
    else if (strcmp(mot,"finPour")==0){
        return ENDFOR_TOKEN ;
    }
    else if (strcmp(mot,"Si")==0){
        return IF_TOKEN ;
    }
    else if (strcmp(mot,"Alors")==0){
        return THEN_TOKEN ;
    }
    else if (strcmp(mot,"finsi")==0){
        return ENDIF_TOKEN ;
    }
    else if (strcmp(mot,"Tantque")==0){
        return WHILE_TOKEN ;
    }
    else if (strcmp(mot,"dans")==0){
        return IN_TOKEN ;
    }
    else if (strcmp(mot,"finTantque")==0){
        return ENDWHILE_TOKEN ;
    }
    else if (strcmp(mot,"Entier")==0){
        return INT_TOKEN ;
    }
    else if (strcmp(mot,"Numerique")==0){
        return NUM_TOKEN ;
    }
    else if (strcmp(mot,"reel")==0){
        return FLOAT_TOKEN ;
    }
    else if (strcmp(mot,"et")==0){
        return AND_TOKEN ;
    }
    else if (strcmp(mot,"ou")==0){
        return OR_TOKEN ;
    }
    else {
        return -1 ;
    }

}

structToken Sym_Suiv(FILE* file,char ch){
    structToken token;
    char localChar=ch;
    while (localChar==' ' || localChar=='\n'|| localChar=='\t')//sauter les espaces et retour à la ligne
    {
        localChar=fgetc(file);
    }
    //verifions le char
    if ((localChar>='A' && localChar<='Z') ||(localChar>='a' && localChar<='z'))//au cas de chaine de caracteres
    {
        char word[255];//var pour stocker la chaine
        int i=0;//la taille
        do //boucle jusqu'à la fin du mot
        {
            word[i]=localChar;
            localChar=fgetc(file);
            word[i+1]='\0';
            i++;
        } while ((localChar>='A' && localChar<='Z') ||(localChar>='a' && localChar<='z')||(localChar>='0' && localChar<='9'));

        fseek(file,-1,SEEK_CUR);

        int res=get_mot_cle(word);//verifions si le mot est un mot cle
        strcpy(token.mot,word);
        token.code=(res==-1)?ID_TOKEN:res;
    }
    else if ((localChar>='0' && localChar<='9'))//nombre
    {
        char word[255];//var pour stocker la chaine
        int i=0;//la taille
        do
        {
            word[i]=localChar;
            localChar=fgetc(file);
            word[i+1]='\0';
            i++;
        } while ((localChar>='0' && localChar<='9'));
        fseek(file,-1,SEEK_CUR);
        strcpy(token.mot,word);
        //strcpy(token.type,"NUM_TOKEN");
        token.code=NUM_TOKEN;
    }
    //autre cas (:.;>....)

    else if (localChar=='+'){
        strcpy(token.mot,"+");
        //strcpy(token.type,"PLUS_TOKEN");
        token.code=PLUS_TOKEN;
        return token;
    }
    else if (localChar=='-'){
        strcpy(token.mot,"-");
        //strcpy(token.type,"MOINS_TOKEN");
        token.code=MOINS_TOKEN;
        }

    else if (localChar=='*'){
        strcpy(token.mot,"*");
        //strcpy(token.type,"MULT_TOKEN");
        token.code=MULT_TOKEN;
        }

    else if (localChar=='/'){
        strcpy(token.mot,"/");
        //strcpy(token.type,"DIV_TOKEN");
        token.code=DIV_TOKEN;
        }

    else if (localChar=='='){
        strcpy(token.mot,"=");
        //strcpy(token.type,"EQL_TOKEN");
        token.code=EQL_TOKEN;
        }

    else if (localChar=='$'){
        strcpy(token.mot,"$");
        //strcpy(token.type,"VIR_TOKEN");
        token.code=AFF_TOKEN;
        }

    else if (localChar=='('){
        strcpy(token.mot,"(");
        //strcpy(token.type,"PO_TOKEN");
        token.code=PO_TOKEN;
        }

    else if (localChar==')'){
        strcpy(token.mot,")");
        //strcpy(token.type,"PF_TOKEN");
        token.code=PF_TOKEN;
        }
    else if (localChar==','){
        strcpy(token.mot,",");
        //strcpy(token.type,"PF_TOKEN");
        token.code=VIR_TOKEN;
        }
    else if (localChar==':'){
        strcpy(token.mot,":");
        //strcpy(token.type,"PF_TOKEN");
        token.code=PP_TOKEN;
        }

    else if (localChar=='<'){

        localChar=fgetc(file);
        switch (localChar)
        {
            case '>':
                strcpy(token.mot,"<>");
                //strcpy(token.type,"DIFF_TOKEN");
                token.code=DIFF_TOKEN;
                break;

            case '=':
                strcpy(token.mot,"<=");
                //strcpy(token.type,"INFEG_TOKEN");
                token.code=INFEG_TOKEN;
                break;

            default:
                strcpy(token.mot,"<");
                //strcpy(token.type,"INF_TOKEN");
                token.code=INF_TOKEN;
                return token;
                fseek(file,-1,SEEK_CUR);
                break;
        }

    }

    else if (localChar=='>'){
        localChar=fgetc(file);
        switch (localChar)
        {
            case '=':
                strcpy(token.mot,">=");
                //strcpy(token.type,"SUPEG_TOKEN");
                token.code=SUPEG_TOKEN;
                break;

            default:
                strcpy(token.mot,">");
                //strcpy(token.type,"SUP_TOKEN");
                token.code=SUP_TOKEN;
                fseek(file,-1,SEEK_CUR);
                break;
        }
    }

    else if (localChar==EOF){
        strcpy(token.mot,"EOF");
        //strcpy(token.type,"FIN_TOKEN");
    token.code=EOF_TOKEN;}

    else{
        strcpy(token.mot,"");
        strcpy(token.type,"");
    }

    return token;

}

void storeToken(structToken token ){//fonction d'affichage
    SYMBOLES[listSymbolesLen++]=token;
     printf("( %s )::::( %s )\n",token.mot,token_Sym[token.code]);
}

void analyse_lex(char* file){
    listSymbolesLen=0;

    char ch;
    FILE *fp=Ouvrir_Fichier(file);

    while((ch = fgetc(fp)) != EOF) {

        structToken token=Sym_Suiv(fp,ch);

        storeToken(token );
    }
    //structToken token;
    //token.code=EOF_TOKEN;
    //storeToken(token);


}

/*int main ( int argc , char const *argv[]) {

    char file[25]="TESTS/test1.txt";
    //strcat(file,argv[1]);
    //strcat(file,".txt");
    analyse_lex(file);

}*/

