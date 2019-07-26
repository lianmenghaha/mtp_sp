#ifndef FUNCREADFILE_CPP
#define FUNCREADFILE_CPP
void funcReadFile(const char* filename_obj,const char *filename_conf)
{
    //read path info of objects,object.txt
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
void funcReadFile(const char* filename_dtime)
{
    fstream ReadFile_dtime(filename_dtime,fstream::in);
    string rname;
    while(!ReadFile_dtime.eof())
    {
	ReadFile_dtime>>rname;
	if(rname.compare("END")==0)
	    break;
	object *oi=mapnameo[rname];
	ReadFile_dtime>>rname;
	object *oj=mapnameo[rname];
	int rnbio=pow(oi->nbio+1,2);
	for(int i=0;i!=rnbio;++i)
	{
	    int itmp;
	    ReadFile_dtime>>itmp;
	    ReadFile_dtime>>oi->dtpkt[make_pair(itmp,oj)];
	}
    }
    ReadFile_dtime.close();
}


void funcWriteFile(const char* filename)
{
    for(int i=1;i!=maxL->intrval+1;++i)
    {
		ostringstream convi;
		convi<<i;
		string strtmp=filename;
		strtmp+="_objassign"+convi.str()+".txt";
		fstream WriteFile_oa(strtmp.c_str(),fstream::out);
		int itmp=0;
		for(auto o:seto)
		{
			//set<object*> settmp={o};
			//WriteFile_oa<<i<<" "<<o->bvl[i]->intrval<<" "<<zvl[settmp][i]->intrval<<endl;
			if(o->vl->intrval==i)
			{
				++itmp;
				WriteFile_oa<<o->name<<endl;
				WriteFile_oa<<"Informations:"<<endl;
				WriteFile_oa<<"Area of "<<o->name<<": ";
				WriteFile_oa<<"["<<o->oxmin<<","<<o->oxmax<<"]*["<<o->oymin<<","<<o->oymax<<"]"<<endl;
			}
		
			/*for(auto oj:seto)
			{set<object*> settmp2={o,oj};
			  WriteFile_oa<<o->name<<" "<<oj->name<<" "<<i<<" "<<zvl[settmp2][i]->intrval<<" ? "<<o->bvl[i]->intrval<<" ? "<<oj->bvl[i]->intrval<<endl;
			}*/
		}
		WriteFile_oa.setf(ios_base::fixed,ios_base::floatfield);
		WriteFile_oa.precision(10);
		WriteFile_oa<<"The total number of objects: "<<itmp<<endl;
		WriteFile_oa<<"The total drying time for this Printing group is: "<<vecl[i-1]->vmaxdt->dourval<<endl;
		//WriteFile_oa<<maxL->intrval;
		WriteFile_oa.close();
	}
}
#endif
