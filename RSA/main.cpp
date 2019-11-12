#include <iostream>
#include <RSA.h>
using namespace std;

int main()
{
    RSA usuario(1024);
    cout << "///////////////////////////////////////////////////////////////////////////////////";
    vector<string> mensajeCifrado = usuario.encrypt("hola como estas amigo mio");
    cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << usuario.decrypt(mensajeCifrado);
    return 0;
}
