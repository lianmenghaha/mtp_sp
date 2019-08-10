#ifndef FUNCSCREENMESSAGE_MTL_CPP
#define FUNCSCREENMESSAGE_MTL_CPP
void funcScreenMessage()
{
	for(auto o:seto)
	{
		cout<<"Informations of objects: "<<o->name<<endl;
		cout<<"Area: "<<"["<<o->oxmin<<","<<o->oxmax<<"]*["<<o->ymin<<","<<o->oymax<<"]"<<endl;
		cout<<"The number of points in "<<o->name<<" :"<<o->opkt.size()<<endl;
	}



















#endif
