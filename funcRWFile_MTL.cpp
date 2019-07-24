#ifndef FUNCRWFILE_MTL_CPP
#define FUNCRWFILE_MTL_CPP
void funcReadFile_MTL(const char* filename_obj)
{
    //read path info of objects, objtects.txt
    fstream ReadFile_obj(filename_obj,fstream::in);
    string rname,line;
    ReadFile_obj>>rname;
    while(!ReadFile_obj.eof())
    {
	//cout<<"obj"<<endl;//检测
	object *o=new object;
	o->name=rname;
	mapnameo[rname]=o;
	seto.insert(o);
	ReadFile_obj>>o->area;
	//检测
	//cout<<rname<<endl;
	//cout<<o->area<<endl;
	
	//read details of path
	while(ReadFile_obj>>rname)
	{
	    //检测
	    //cout<<"line"<<endl;
	    if(ReadFile_obj.eof()||rname[rname.size()-1]!=':')
		break;
	    getline(ReadFile_obj,line);
	    auto strpos1=1;
	    auto strpos2=line.find_first_of("+");
	    auto strpos3=line.find_first_of("i");
	    auto strpos4=line.find_last_of("+");
	    double x1,x2,y1,y2;
	    x1=atof(line.substr(strpos1,strpos2-strpos1).c_str());
	    y1=atof(line.substr(strpos2+1,strpos3-strpos2-1).c_str());
	    x2=atof(line.substr(strpos3+2,strpos4-strpos3-2).c_str());
	    y2=atof(line.substr(strpos4+1,line.size()-strpos4-2).c_str());
	    o->path.push_back({x1,y1});
	    o->path.push_back({x2,y2});

	    //jiance
	    //cout<<x1<<endl;
	    //cout<<y1<<endl;
	    //cout<<x2<<endl;
	    //cout<<y2<<endl;
	}
    }
    ReadFile_obj.close();
}
void funcWriteFile_MTL(const char* filename)
{
    fstream WriteFile_dtime(filename,fstream::out);
    for(auto oi:seto)
    {
	for(auto oj:seto)
	{
	    WriteFile_dtime<<oi->name<<" "<<oj->name<<endl;
	    for(int i=0;i!=oi->opkt.size();++i)
	    {
		//WriteFile_dtime<<i<<" ";
		//WriteFile_dtime<<"("<<oi->opkt[i].first<<","<<oi->opkt[i].second<<")"<<" ";
		//10 digits after decimal point
		WriteFile_dtime.setf(ios_base::fixed,ios_base::floatfield);
		WriteFile_dtime.precision(10);
		WriteFile_dtime<<i<<" "<<oi->dtpkt[{i,oj}]<<endl;
	    }
	}
    }
    WriteFile_dtime<<"END";
}
#endif
