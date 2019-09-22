using namespace std;
class var;
class object
{
	public:
		// input
		object();
		string name;
		vector<pair<double,double>> path;
		double area;
		set<object*> setco, setbo; // conflict: no merge, no absorption
		int nbio;

		//store the coordinatens of these points
		//opkt.size()=(nbio+1)^2;
		vector<pair<double,double>> opkt;

		//read from Matlab, store the drying time which increased by patterns (including itself)
		//int:the number of these points,which from 0 to (nbio+1)^2-1
		//object*:the pattern which increases the drying time for o
		//double:the increased drying time
		map<pair<int,object*>,double> dtpkt;

		//assume every pattern is [oxmin,oxmax]*[oymin,oymax]
		double oxmin,oxmax,oymin,oymax;


		//information about priting group and drying time
		//vl:the printing group which object will be assigned to
		//bvl:binary variable,indicated if this object assigned to this printing group
		var *vl, **bvl; // layer assignment
		//zvl:indicates if two patterns are assigned to the same printing group
		//qmc:indicates if two patterns have merging conflict
		map<object*,var*> qmc;
		//t_{i,m,r},r=1,_,n_i denoted the drying time for points in Pi in m-th printing group
		//1st int:index for priting group,2st int:index for points.
		map<pair<int,int>,var*> tpkt;
		//t_(i,m,maxPi) denote the maximum drying time for Pi in m-th printing group
		//int:index for printing group
		map<int,var*> tpktmax;
};
object::object()
{
	vl=0;
	bvl=0;
	nbio=10;
}
class layer
{
        public:
		layer();
		//t_{m,max m},m=1,_,N_G;//maximal drying time for printing group
		var *vmaxdt;
};
layer::layer()
{
	vmaxdt=0;
}
class var
{
        public:
                var();
                int typ; // 0: binary, 1: integer, 2: continuous
				int index;
                double lb, ub;
                set<int> cons_i;
                map<int,double> coef_cons; // cons_i, coef
				//store the result after Gurobi
                int intrval;//int val
                double dourval; // double val
				//store the sub-optimal solution after Gurobi
				//int intrval2;
				//double dourval2;
				vector<int> intrval2;
				vector<double> dourval2;
		// quadratic
		map<int, set<var*>> coef_setvar;
		map<pair<int, var*>, double> coef_varcons;
};
var::var()
{
        typ=-1;
        intrval=-1;
        dourval=-1;
}
