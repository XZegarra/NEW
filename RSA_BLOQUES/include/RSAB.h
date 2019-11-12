#ifndef RSAB_H
#define RSAB_H
#include <NTL/ZZ.h>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <sstream>

using namespace std;
using namespace NTL;

class RSAB
{
    public:
        RSAB(int);
        RSAB(ZZ,ZZ);
        string encrypt(string);
        vector<string> gen_blocks(string);
        string add_zero(string,int);
        string decrypt(string);
        ZZ getN(){return N;}
        ZZ get_e(){return e;}
    private:
        ZZ N;
        ZZ p;
        ZZ q;
        ZZ e;
        ZZ phi;
        ZZ d;
        string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789 ";
        ZZ convert(string s){
            int tam=s.size();
            ZZ res;
            res=0;

            for(int i=0; i<tam; i++){
                res=res*10+(s[i]-'0');
            }
            return res;
        }

        int to_int(string a){
            int tam=a.size();
            int res;
            res=0;
            for(int i=0; i<tam; i++){
                res=res*10+(a[i]-'0');
            }
            return res;
        }

        ZZ exp(ZZ m, ZZ e, const ZZ n){
            ZZ c=e;
            ZZ m2;
            ZZ result(1);
            ZZ bag=m;
            ZZ bag2(1);

            while(c>0){
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
            if(s1<0){
                s1=moduloE(s1,b);
            }
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

        ZZ CRT(vector<ZZ> a, vector<ZZ> p){
            ZZ q_inv=exp(p[1],p[0]-2, p[0]);
            int tam=a.size();

            for(int i=0; i<tam; i++){
                a[i]=moduloE(a[i], p[i]);
            }

            ZZ h=moduloE(q_inv*moduloE(a[0]-a[1], p[0]),p[0]);
            ZZ m=a[1]+h*p[1];
            return m;
        }

        string zeros(string m, int n){
            string aux;
            aux="0";
            string ans;
            int len=m.size();

            while(len<n){
                aux=aux+m;
                m=aux;
                aux="0";
                len=m.size();
            }
            return m;
        }

        string zb(string msj, int n){
            string z;
            z="0";

            while(msj.size()%n!=0){
                z=z+msj;
                msj=z;
                z="0";
            }
            return msj;
        }

        string zToString(const ZZ &z){
            stringstream buffer;
            buffer << z;
            return buffer.str();
        }
};

#endif // RSAB_H
