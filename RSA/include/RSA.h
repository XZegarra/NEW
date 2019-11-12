#ifndef RSA_H
#define RSA_H
#include <NTL/ZZ.h>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <sstream>
#include <stdlib.h>
using namespace std;
using namespace NTL;

class RSA
{
    public:
        RSA();
        RSA(int);
        RSA(ZZ,ZZ);
        vector <string> encrypt(string);
        string decrypt(vector<string>);

        virtual ~RSA();

    protected:

    private:
        ZZ N;
        ZZ p;
        ZZ q;
        ZZ e;
        ZZ phi;
        ZZ d;
        string alphabet="abcdefghijklmnopqrstuvwxyz0123456789 ";

        string zToString(const ZZ &z){

            stringstream buffer;
            buffer << z;
            return buffer.str();
        }

        ZZ extendido(ZZ a,ZZ b){
            ZZ r1=a;
            ZZ r2=b;
            ZZ s1(1),s2(0),t1(0),t2(1),q,r,s,t;
            while(r2>0){
                q=r1/r2;
                r=r1-q*r2;
                r1=r2;
                r2=r;
                s=s1-q*s2;
                s1=s2;
                s2=s;
                t=t1-q*t2;
                t1=t2;
                t2=t;
            }
            if(s1<0)
                s1=moduloE(s1,b);
            return s1;
        }
        ZZ moduloE(ZZ a, ZZ b){
            ZZ q(a/b);
            ZZ r(a-q*b);
            if(r<0){
                ZZ q((a/b)-1);
                r=a-q*b;
            }
            return r;
        }
        ZZ exp(ZZ m, ZZ e, const ZZ n){
            ZZ c=e;
            ZZ m2;
            ZZ result(1);
            ZZ bag=m;
            ZZ bag2(1);
            while(c>0)
            {
                m2=e%2;
                bag=(bag*bag2)%n;
                if(m2==1)
                {
                    result=(bag*result)%n;
                }
                c=c/2;
                e=c;
                bag2=bag;
            }
            return result;
        }
        ZZ stringToZZ(string s){
            int tam=s.size();
            ZZ res;
            res=0;
            for(int i=0; i<tam; i++)
            {
                res=res*10+(s[i]-'0');
            }
            return res;
        }
};

#endif // RSA_H
