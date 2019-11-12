#include "RSA.h"
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;
using namespace NTL;

RSA::RSA()
{
    //ctor
}

RSA::RSA(int numBits){
    p=GenPrime_ZZ(numBits);
    q=GenPrime_ZZ(numBits);
    N=p*q;
    phi=(p-1)*(q-1);
    e=GenPrime_ZZ(numBits);
    while(GCD(e,phi)!=1)
    {
        e=GenPrime_ZZ(numBits);
    }
    d=extendido(e,phi);
    cout<<"E: "<<e<<endl;
    cout<<"N: "<<N<<endl;
}
RSA::RSA(ZZ a, ZZ b){
    p = a;
    q = b;
}
vector <string> RSA::encrypt(string message){
    vector <string> result;
    for(int i=0; i<message.length(); i++){
        ZZ bc;
        ZZ tmp;
        tmp = alphabet.find(message[i]);
        bc =exp(tmp,e,N);
        string aux;
        aux=zToString(bc);
        result.push_back(aux);
    }
    cout<<"cifrado: "<<result[0]<<endl;
    cout<<"Cifrado terminado"<<endl;
    return result;
}

string RSA::decrypt(vector <string> encrypted){
    string result;
    for(int i=0; i<encrypted.size(); i++){
        ZZ bz;
        ZZ tmp = stringToZZ(encrypted[i]);
        bz =exp(tmp,d,N);
        string aux;
        aux =zToString(bz);
        int aux2 = stoi(aux);
        aux=alphabet[aux2];
        result = result + aux;
    }
    return result;
}
RSA::~RSA()
{
    //dtor
}
