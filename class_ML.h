#ifndef CLASS_ML_H
#define CLASS_ML_H
using namespace std;
class var;
class object
{
	public:
		object();
		string name;
		vector<pair<double,double>> path;
		double area;
		//Conflict:Merging Conflict,Laplace Pressure Conflict
		set<object*> setco,setbo;
		//the side of object will be divided into nbio parts
		int nbio;
		//the coordinates of points in object
		vector<pair<double,double>> opkt;
		//read from Matlab,store the drying time which increased by patterns(includeing itself)
		//int:the index of the points
		//object*:the pattern which increases the drying time
		//double:the drying time increased
		map<pair<int,object*>,double> dtpkt;
		//assum every object is [oxmin,oxmax]*[oymin,oymax]
		double oxmin,oxmax,oymin,oymax;

		//o->vl indicates the printing group, which it is assigned to 
		//o->bvl[i]=1 indicates this object is assigned to i-th printing group
		var *vl,**bvl;
}
object::object()
{
	vl=0;
	bvl=0;
	nbio=9;
}
class layer
{
	public:
		layer();
		//t_{gm,maxgm},gm=1,...,Ng
		//maximal drying time for this layer
		var *vmaxdt;





















#endif
