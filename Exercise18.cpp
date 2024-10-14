#include <bits/stdc++.h>
using namespace std;
struct compte {
string id;
int solde;
};
int& operation(compte* tar,string tar_compt)
{
    for(int i=0; i<4; i++)
    {
        if(tar[i].id == tar_compt)
        {
            return tar[i].solde;
        }
    }
}
void essai_comptes(){
compte tab[4]={ {"courant", 0},{"codevi", 1500 },
{"epargne", 200 }, { "cel", 300 } };
operation(tab,"courant")=100;
operation(tab,"codevi")+=100;
operation(tab,"cel")-=50;
for(int i=0; i<4; i++) cout<<tab[i].id<<" : "<<tab[i].solde<<"\n";
}
int main()
{
    essai_comptes();
}