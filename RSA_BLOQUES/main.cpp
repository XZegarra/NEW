#include <iostream>
#include <NTL/ZZ.h>
#include <vector>
#include "RSAB.h"
#include <time.h>
#include <iomanip>
using namespace NTL;
using namespace std;
int main()
{
    RSAB usuario(1024);
    string mensaje = usuario.encrypt("hola como estas amigo mio ");
    usuario.decrypt(mensaje);
    return 0;
}
