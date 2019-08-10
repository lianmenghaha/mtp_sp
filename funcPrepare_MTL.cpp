#ifndef FUNCPREPARE
#define FUNCPREPARE

void funcPrepare_MTL()
{
    //from the elements in path, we want to find out for every object
    //oxmin,oxmax,oymin,oymax
    //we assume every pattern [oxmin,oxmax]*[oymin,oymax]
    int nboo=0;
	//we make a copy of seto
	set<object*> setcpy;
	for(auto o:seto)
	  setcpy.insert(o);
    for(auto o:setcpy)
	{
		int spi=0;
		vector<double> vx,vy;
		for(auto xy:o->path)
		{
			vx.push_back(xy.first);
			vy.push_back(xy.second);
			//store the endpoints of the pattern, without repetition
			o->opc.push_back(xy);
		}
		sort(o->opc.begin(),o->opc.end());
		auto end_unique=unique(o->opc.begin(),o->opc.end());
		o->opc.erase(end_unique,o->opc.end());
		//jiance
		cout<<o->name<<endl;
		for(auto xy:o->opc)
		  cout<<"("<<xy.first<<" "<<xy.second<<")"<<endl;
		//now o->opc contains only the endpoints of the pattern
		if(o->opc.size()==4)
		{
			o->oxmin=*min_element(vx.begin(),vx.end());
			o->oxmax=*max_element(vx.begin(),vx.end());
			o->oymin=*min_element(vy.begin(),vy.end());
			o->oymax=*max_element(vy.begin(),vy.end());
			//compute the coordinates for points in objects
			double deltax=(o->oxmax-o->oxmin)/o->nbio;
			double deltay=(o->oymax-o->oymin)/o->nbio;
			//?~@?~K@?
			//cout<<"deltax"<<deltax<<endl;
			//cout<<"deltay"<<deltay<<endl;
			for(int i=0;i!=o->nbio+1;++i)
			{   
				for(int j=0;j!=o->nbio+1;++j)
				{
					o->opkt.push_back({o->oxmin+i*deltax,o->oymin+j*deltay});
				}
			}   

		}
		else
		{
			//copy the vector of o->opc
			vector<pair<double,double>> opcsp=o->opc;
			//divide the patterns with more than 4 lines into small rectangles and store as new objects
			//in our project,we have 12 points.
			while(opcsp.size()!=0)
			{
				//we choose one point
				pair<double,double> fpt=opcsp[0];
				//remove this point from the copy
				for(vector<pair<double,double>>::iterator vit=opcsp.begin();vit!=opcsp.end();)
				{
					if(*vit==fpt)
					{
						vit=opcsp.erase(vit);
						break;
					}
					else
					  ++vit;
				}
				//choose another point,which has the same x-coor.as the 1st one
				pair<double,double> spt;
				for(vector<pair<double,double>>::iterator vit=opcsp.begin();vit!=opcsp.end();)
				{
					if(vit->first==fpt.first)
					{
						spt=*vit;
						vit=opcsp.erase(vit);
						break;
					}
					else
					  ++vit;
				}
				//we have chosen the 2nd point and remove it from the copy
				//we choose the 3rd point,which has the same y-coor.as the 2nd one
				pair<double,double> tpt;
				for(vector<pair<double,double>>::iterator vit=opcsp.begin();vit!=opcsp.end();)
				{
					if(vit->second==spt.second)
					//if(vit->second==fpt.second)
					{
						tpt=*vit;
						vit=opcsp.erase(vit);
						break;
					}
					else
					  ++vit;
				}
				//we have chosen the 3rd point and remove it from the copy
				//we choose the 4th point,which has the same x-coor.as the 3rd one
				pair<double,double> fopt;
				for(vector<pair<double,double>>::iterator vit=opcsp.begin();vit!=opcsp.end();)
				{
					if((vit->first==tpt.first)&&(vit->second==fpt.second))
					//if((vit->first==tpt.first)||(vit->second==spt.second))
					{
						fopt=*vit;
						vit=opcsp.erase(vit);
						break;
					}
					else
					  ++vit;
				}
				//jiance
				cout<<fopt.first<<","<<fopt.second<<endl;
				//we have already choose 4 points
				//for these 4 points, we build new object
				vector<double> endptx={fpt.first,spt.first,tpt.first,fopt.first};
				vector<double> endpty={fpt.second,spt.second,tpt.second,fopt.second};
				object *osp=new object;
				++spi;
				ostringstream obspi;
				obspi<<spi;

				//the name of new object
				osp->name=o->name+"sp"+obspi.str();
				mapnameo[osp->name]=osp;
				//opc
				osp->opc={fpt,spt,tpt,fopt};
				//seto.insert(osp);
				//jiance
				cout<<osp->name<<endl;
				//oxmin,oxmax,oymin,oymax
				osp->oxmin=*min_element(endptx.begin(),endptx.end());
				osp->oxmax=*max_element(endptx.begin(),endptx.end());
				osp->oymin=*min_element(endpty.begin(),endpty.end());
				osp->oymax=*max_element(endpty.begin(),endpty.end());
				//path
				osp->path={fpt,spt,spt,tpt,tpt,fopt,fopt,fpt};
				//setco,setbo
				for(auto on:o->setco)
				{
					osp->setco.insert(on);
					//cout<<on->name<<endl;
				}
				for(auto on:o->setbo)
				  osp->setbo.insert(on);
				//for other object,we want to find if there are objects whose setco or setbo contains this object,we delete it and add sp-obj. to it
				for(auto oc:seto)
				{
					//setco
					for(set<object*>::iterator ocn=oc->setco.begin();ocn!=oc->setco.end();)
					{
						if((*ocn)->name==o->name)
						{
							//jiance
							cout<<oc->name<<" ";
							//ocn=oc->setco.erase(ocn);
							oc->setco.insert(osp);
							//jiance
							cout<<osp->name<<endl;
							break;
						}
						else
						  ++ocn;
					}
					//setbo
					for(set<object*>::iterator ocn=oc->setbo.begin();ocn!=oc->setbo.end();)
					{
						if((*ocn)->name==o->name)
						{
							//ocn=oc->setbo.erase(ocn);
							oc->setbo.insert(osp);
							break;
						}
						else
						  ++ocn;
					}
				}
				seto.insert(osp);

				//opkt
				double deltax=(osp->oxmax-osp->oxmin)/osp->nbio;
				double deltay=(osp->oymax-osp->oymin)/osp->nbio;
				for(int i=0;i!=osp->nbio+1;++i)
				{
					for(int j=0;j!=osp->nbio+1;++j)
					{
						osp->opkt.push_back(make_pair(osp->oxmin+i*deltax,osp->oymin+j*deltay));
					}
				}
			}//while end here
			seto.erase(o);
		}//else end here
	}
	//jiance
	for(auto o:seto)
	{
	  cout<<o->name<<" "<<o->opc.size()<<" "<<o->setco.size()<<" "<<o->setbo.size()<<endl;
	  for(auto xy:o->opc)
		cout<<"("<<xy.first<<" "<<xy.second<<")";
	  cout<<endl;
	}


	set<object*> setcpy2;
	for(auto o:seto)
	  setcpy2.insert(o);
	//delet the redundant information
	for(auto o:seto)
	{
		//delete the redundant object in setco
		/*for(set<object*>::iterator setit=o->setco.begin();setit!=o->setco.end();)
		{
			//if((*setit)->path.size()!=8)
			if((*setit)->name=="o1")
			  setit=o->setco.erase(setit);
			else
			  ++setit;
		}
		//delete the redundant object in setbo
		for(set<object*>::iterator setit=o->setbo.begin();setit!=o->setbo.end();)
		{
			//if((*setit)->path.size()!=8)
			if((*setit)->name=="o12")
			  setit=o->setco.erase(setit);
			else
			  ++setit;
		}*/
		//setco
		for(auto on:o->setco)
		{
			if(on->path.size()!=8)
			  o->setco.erase(on);
		}
		//setbo
		for(auto on:o->setbo)
		{
			if(on->path.size()!=8)
			  o->setbo.erase(on);
		}
	}
	//jiance
	for(auto o:seto)
	{
		cout<<o->name<<": "<<endl;
		cout<<"setco: "<<o->setco.size()<<endl;
		for(auto on:o->setco)
		  cout<<on->name<<" ";
		cout<<endl;
		cout<<"setbo: "<<o->setbo.size()<<endl;
		for(auto on:o->setbo)
		  cout<<on->name<<" ";
		cout<<endl;
	}
	for(auto o:seto)
	  cout<<o->name<<" ";
	cout<<endl;



}
#endif
