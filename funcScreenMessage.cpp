#ifndef FUNCSCREENMESSAGE_CPP
#define FUNCSCREENMESSAGE_CPP
void funcScreenMessage()
{
    //object info
    for(auto o:seto)
    {
			cout<<"Object name: "<<o->name<<" ";
	//cout<<"Object area: "<<o->area<<endl;
		if(o->setco.size()!=0)
		{
			cout<<"Mergen Conflict: ";
			for(auto on:o->setco)
			  cout<<on->name<<" ";
		}
		if(o->setbo.size()!=0)
		{
			cout<<"Laplace Pressure Conflict: ";
			for(auto on:o->setbo)
			  cout<<on->name<<" ";
		}
		cout<<endl;
    }
	cout<<endl;
    //layer info
    for(int i=1;i!=maxL->intrval+1;i++)
    {
	cout<<"Printing group "<<i<<" :"<<endl;
	for(auto o:seto)
	{
	    if(o->vl->intrval==i)
		cout<<o->name<<" ";
	}
	cout<<endl;
	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(10);
	cout<<"The drying time for this printing group: "<<vecl[i-1]->vmaxdt->dourval<<endl;
    }
	cout<<endl;
    cout<<"Total printing group: "<<maxL->intrval<<endl;
	//
}




























#endif
