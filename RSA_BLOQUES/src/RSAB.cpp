#include "RSAB.h"
#include <NTL/ZZ.h>
#include <sstream>
#include <vector>

using namespace NTL;
using namespace std;

RSAB::RSAB(int num)
{
    p=GenPrime_ZZ(num);
    q=GenPrime_ZZ(num);
    N=p*q;
    phi=(p-1)*(q-1);
    e=GenPrime_ZZ(num);
    while(GCD(e,phi)!=1)
    {
        e=GenPrime_ZZ(num);
    }
    d=extendido(e,phi);
}
RSAB::RSAB(ZZ n, ZZ c)
{
    N=n;
    e=c;
}
string RSAB::encrypt(string message)
{
    ZZ nn;
    nn=3;
    int n2=zToString(nn).size();
    message=add_zero(message,n2);
    vector<string> blocks=gen_blocks(message);
    int len=blocks.size();
    vector<string> BC;
    string result;
    int dig = zToString(N).size();

    for(int i=0; i<len; i++){
        ZZ bc;
        ZZ tmp=convert(blocks[i]);
        bc = exp(tmp,e,N);
        string aux;
        aux=zToString(bc);
        result=result+zeros(aux,dig);
    }

    cout<<"MENSAJE CIFRADO: "<<result<<endl;
    return result;
}

string RSAB::decrypt(string encrypted)
{
    cout<<"MENSAJE DECIFRADO: "<<endl;
    int len=encrypted.size();
    string result;
    int tam=zToString(N).size();
    ZZ dp=moduloE(d,p-1);
    ZZ dq=moduloE(d,q-1);
    vector<ZZ> m={p,q};

    for(int i=0; i<len; i=i+tam){
        ZZ bd;
        bd=convert(encrypted.substr(i,tam));                                //SBSTR SELECCIONA UN STRING DENTRO DE OTRO; DESDE LA POSICION I A TAM
        ZZ aux1(0), aux2(0);
        aux1=exp(bd,dp,p); aux2=exp(bd,dq,q);
        vector<ZZ> a={aux1, aux2};
        ZZ aux;
        aux=CRT(a,m);
        result=result+zb(zToString(aux), 3);
    }

    int l=result.size();
    string result1;
    string aux;

    for(int i=0; i< l; i=i+3){
        aux=char(stoi(result.substr(i,3)));
        result1=result1+aux;
        //result.clear();
    }

    cout<<result<<endl;
    int t=result.size();
    string md;
    cout<<"MENSAJE ARMADO EN STRING: "<<result1<<endl;
    return result1;
}


string RSAB::add_zero(string msj, int n)
{
    int len=msj.size();
    string answer;
    string aux;
    string l;
    int cont=0;

    for(int i=0; i< len; i++){
        int tmp=int(char(msj[i]));

        if(to_string(tmp).size()==1){
            aux="00";
            aux=aux+to_string(tmp);
        }
        else if(to_string(tmp).size()==2){
            aux="0";
            aux=aux+to_string(tmp);
        }
        else{
            aux=aux+to_string(tmp);
        }
        answer=answer+aux;
        aux.clear();
    }

    return answer;
}

vector<string> RSAB::gen_blocks(string msje)
{
    vector<string> blocks;
    string block;
    int len1=zToString(N).size();
    int len2=msje.size();
    int cont=0;

    while(cont<len2){
        if((block+msje.substr(cont,3)).size()<=len1 and convert(block+msje[cont])<N){            //GENERACION DE BLOQUES, SEPARAMOS LAS PALABRAS
            block=block+msje.substr(cont,3);
            cont=cont+3;
        }
        else{
            blocks.push_back(block);
            block.clear();
        }
    }

    if(block.size()){
        blocks.push_back(block);
    }

    int a=blocks.size();
    return blocks;
}
