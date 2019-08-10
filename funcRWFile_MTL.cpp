#ifndef FUNCRWFILE_MTL_CPP
#define FUNCRWFILE_MTL_CPP
void funcReadFile_MTL(const char* filename_obj,const char* filename_conf)
{
    //read path info of objects, objtects.txt
    fstream ReadFile_obj(filename_obj,fstream::in);
    string rname,line;
    ReadFile_obj>>rname;
    while(!ReadFile_obj.eof())
    {
	object *o=new object;
	o->name=rname;
	mapnameo[rname]=o;
	seto.insert(o);
	ReadFile_obj>>o->area;
	
	//read details of path
	while(ReadFile_obj>>rname)
	{
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

	    //cout<<x1<<endl;
	    //cout<<y1<<endl;
	    //cout<<x2<<endl;
	    //cout<<y2<<endl;
	}
    }
    ReadFile_obj.close();
	//read conflict info of objects
	fstream ReadFile_conf(filename_conf,fstream::in);
	while(getline(ReadFile_conf,line))
	{
		if(ReadFile_conf.eof())
		  break;
		if(line.compare("no merge conflict:")==0)
		{
			while(ReadFile_conf>>rname)
			{
				if(rname.compare("FIN")==0)
				  break;
				object *o=mapnameo[rname];
				int nobj;
				ReadFile_conf>>nobj;
				for(int i=0;i!=nobj;++i)
				{
					ReadFile_conf>>rname;
					o->setco.insert(mapnameo[rname]);
				}
			}
		}
		if(line.compare("no absorption conflict:")==0)
		{
			while(ReadFile_conf>>rname)
			{
				if(rname.compare("FIN")==0)
				  break;
				object *o=mapnameo[rname];
				int nobj;
				ReadFile_conf>>nobj;
				for(int i=0;i!=nobj;++i)
				{
					ReadFile_conf>>rname;
					o->setbo.insert(mapnameo[rname]);
				}
			}
		}
	}
		ReadFile_conf.close();

}
//write file:object.txt and conflict.txt
//for the objects which have been decomposed
void funcWriteFile_ori_sp(const char* filename_obj_sp,const char* filename_conf_sp)
{
	//write the object information
	fstream WriteFile_obj(filename_obj_sp,fstream::out);
	for(auto o:seto)
	{
		WriteFile_obj<<o->name<<" "<<o->area<<endl;
		int j=1;
		for(int i=0;i!=o->path.size();)
		{
			WriteFile_obj<<"line"<<j<<": "<<o->path[i].first<<"+"<<o->path[i].second<<"i,"<<o->path[i+1].first<<"+"<<o->path[i+1].second<<"i"<<endl;
			i+=2;
			++j;
		}
		//jiance
		cout<<o->name<<endl;
		for(auto xy:o->path)
		  cout<<xy.first<<"?"<<xy.second<<endl;

	}
	WriteFile_obj.close();
	//write the conflict relation between objects
	fstream WriteFile_conf(filename_conf_sp,fstream::out);
	//no merge conflict:
	WriteFile_conf<<"no merge conflict:"<<endl;
	for(auto o:seto)
	{
		WriteFile_conf<<o->name<<" "<<o->setco.size()<<" ";
		for(auto on:o->setco)
		  WriteFile_conf<<on->name<<" ";
		WriteFile_conf<<endl;
	}
	WriteFile_conf<<"FIN"<<endl;
	WriteFile_conf<<endl;
	//no absorption conflict:
	WriteFile_conf<<"no absorption conflict:"<<endl;
	for(auto o:seto)
	{
		WriteFile_conf<<o->name<<" "<<o->setbo.size()<<" ";
		for(auto on:o->setbo)
		  WriteFile_conf<<on->name<<" ";
		WriteFile_conf<<endl;
	}
	WriteFile_conf<<endl;
	WriteFile_conf<<"FIN";
	WriteFile_conf.close();
}

				
		




//write file:dtime.txt
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
		WriteFile_dtime<<i<<" "<<oi->dtpkt[make_pair(i,oj)]<<endl;
	    }
	}
    }
    WriteFile_dtime<<"END";
}
#endif
