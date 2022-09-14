
#include "syn.h"
#include "lex.h"

int main()
{
char file[25]="TESTS/test1.txt";
analyse_lex(file);
analyse_syn();
printSymbolTable();
}
