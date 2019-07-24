#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<ctime>
#include<algorithm>
#include"gurobi_c++.h"

#include"class.h"
#include"gv.h"
#define Mval 1000000

#include"funcRWFile.cpp"
#include"funcPrepare.cpp"
#include"funcModel_Var.cpp"
#include"funcModel_Cons.cpp"
#include"funcScreenMessage.cpp"
#include"funcGurobi.cpp"
using namespace std;
int main (int argc,char**argv)
{
    cout<<"Start Reading Files: objects.txt conflict.txt"<<endl;
    funcReadFile(argv[1],argv[2]);
    cout<<"Finished Reading Files."<<endl;
    cout<<"Start Computing the coordinates of the points in each object."<<endl;
    funcPrepare();
    cout<<"Finished Computing."<<endl;
    cout<<"Start Reading Files: dtime.txt"<<endl;
    funcReadFile(argv[3]);
    cout<<"Finished Reading Files."<<endl;
    cout<<"Start Building Variables."<<endl;
    funcModel_Var();
    cout<<"Finished Building Variables: "<<vvar.size()<<" Variables."<<endl;
    cout<<"Start Building Constraints:"<<endl;
    funcModel_Cons();
    cout<<"Finished Building Constraints: "<<nCons<<" Constraints."<<endl;
    funcGurobi(0,0.05,atoi(argv[4]),0.0,0.01,1,1);
    funcWriteFile(argv[5]);
    funcScreenMessage();
    return 0;
}
