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
//#include"funcScreenMessage_MTL.cpp"
using namespace std;
int main (int argc,char**argv)
{
    cout<<"Start Reading Files: object.txt and conflict.txt"<<endl;
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
    cout<<"The drying time for the points in each pattern has been written in "<<argv[2]<<endl;
    //funcScreenMessage();

    return 0;
}
