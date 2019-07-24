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
#include<cmath>
#include<random>
#include<algorithm>
#include<chrono>

#include"class.h"
#include"gv.h"
#define Mval 1000000

#include"funcRWFile_MTL.cpp"
#include"funcPrepare.cpp"
#include"funcMatlab.cpp"
using namespace std;
int main (int argc,char**argv)
{
    cout<<"Start Reading Files"<<endl;
    funcReadFile_MTL(argv[1]);
    cout<<"Finished Reading Files"<<endl;
    cout<<"Start Computing the coordinates of points in each object."<<endl;
    funcPrepare();
    cout<<"Finished Computing the coordinates of points in each object."<<endl;
    cout<<"Start Computing the drying time for each point."<<endl;
    cout<<"Matlab Begin"<<endl;
    funcMatlab();
    cout<<"Matlab End"<<endl;
    funcWriteFile_MTL(argv[2]);
    cout<<"The result has been written in "<<argv[2]<<endl;
    //funcScreenMessage();

    return 0;
}
