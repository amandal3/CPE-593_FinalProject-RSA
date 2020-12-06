
/*
#include<iostream>
#include<algorithm>
#include<cmath>
#include<random>
#include<stdlib.h>
#include<time.h>
using namespace std;

class GCD
{
private:
	int a,b;
public:
	GCD():a(10),b(20){}
	GCD(int a, int b): a(a),b(b){}
	void print(){
		cout<<a<<" "<<b;
	}
	int calculate(GCD r){
		for(int i = min(r.a,r.b); i>2; i--){
			if(r.a%i == 0 && r.b%i == 0){return i;}
			}
		}

};



class RPrime{
private:
	int64_t p;
	int64_t q;
	int64_t n;
	int64_t m;
	int64_t e;
public:
	RPrime(int64_t k):m(k){}
	int64_t phi;
	vector<int64_t> Rnumber;
	
	uint64_t value(uint64_t p, uint64_t q,uint64_t n,uint64_t phi){
		cout<<"p: "<<p<<'\n';
		cout<<"q: "<<q<<'\n';
		cout<<"n: "<<n<<'\n';
		cout<<"phi: "<<phi<<'\n';
		cout<<'\n';
	}
	int64_t generate(RPrime R){
		bool *isPrime = new bool[R.m+1];
		for(int64_t i =2; i<=R.m; i++){
			isPrime[i] = true;
		}
		for(int64_t i =2;i<=R.m; i++){
			if(isPrime[i] == true){
				for(int64_t j = 2*i; j<=R.m; j+=i){
					isPrime[j] = false;
					
				}
			}
		}

		for(int64_t i = 2; i<=R.m; i++){
		    srand(time(NULL));
			if(isPrime[i] == true){
				Rnumber.push_back(i);
			}

		}
		uint64_t size = Rnumber.size();
		cout<<"size: "<<size<<'\n';
		
	//	srand(time(NULL));
		uint64_t r = rand()%size+1;
		
	//	srand(time(NULL));
		uint64_t s = rand()%size+1;
		
		cout<<"r: "<<r<<'\n';
		cout<<"s: "<<s<<'\n';
		
		R.p = Rnumber.at(r);
		R.q = Rnumber.at(s);
		R.n =  R.p*R.q;
		R.phi = (R.p-1) * (R.q -1);
		return value(R.p,R.q,R.n,R.phi);
	    
	}

	
		
};
#if 0
class Encryption : RPrime{
private:
	int64_t e;
	int64_t track;
public:
	Encryption(int64_t e, int64_t track) : e(e),track(track){}
	int check(){
		return phi;
	}
};
#endif

int main(){
	GCD g1;
	GCD g2(10,5);
	RPrime r1(100);

	//cout<<"g1: "<<g1.calculate(g1)<<" "<<'\n';
	//g1.print();cout<<'\n';
	//cout<<"g2: "<<g2.calculate(g2)<<" "<<'\n';
	//g2.print();cout<<'\n';

	r1.generate(r1);
	cout<<r1.check();

}
*/

#include<iostream>
#include<cmath>
#include<vector>
#include<numeric>
using namespace std;

class KeyGeneration{
public:
	unsigned p;
	unsigned q;
	unsigned n;
	unsigned phi_n;
	unsigned e;
	unsigned d;

	void prompter();
	void primality_check();
	unsigned calculate_n();
	unsigned calculate_phi();
	unsigned calculate_e();
	unsigned calculate_d();
	unsigned gcd(unsigned i, unsigned phi_n );
};

void KeyGeneration::prompter(){
	cout<<"Please Enter first prime number p: ";
	cin>>p;
	cout<<"Please Enter first prime number q: ";
	cin>>q;
}

void KeyGeneration::primality_check(){
	vector<unsigned> p_factors;
	for(unsigned i =2; i<= static_cast<unsigned>(sqrt(p)); i++){
		if(p%i == 0){
			p_factors.push_back(i);
			p_factors.push_back(p/i);
		}

	}
	vector<unsigned> q_factors;
	for(unsigned i =2; i<= static_cast<unsigned>(sqrt(q)); i++){
		if(p%i == 0){
			q_factors.push_back(i);
			q_factors.push_back(q/i);
		}

	}

	if(p_factors.size()!=0 || q_factors.size()!=0){
		throw(runtime_error("Non Prime Input"));
	}	 
}

unsigned KeyGeneration::calculate_n(){
	n = p*q;
	return n;
}

unsigned KeyGeneration::calculate_phi(){
	phi_n =(p-1) *( q-1);
	return phi_n;
}

unsigned KeyGeneration:: gcd(unsigned i, unsigned phi_n){
		for(unsigned j = min(i,phi_n); j>2; j--){
			if(i%j == 0 && phi_n%j == 0){return j;}
			}
		}
	
unsigned KeyGeneration::calculate_e(){
	unsigned i = 2;
	
	while(gcd(i,phi_n)!=1){
		i++;
	}
	e = i;
	if(e>phi_n){
		throw(runtime_error("e is greater phi_n"));
	}
	return e;
}


unsigned KeyGeneration::calculate_d(){
	/*
	e*d mod phi_n = 1
	*/
	unsigned k = 1;
	while((k*phi_n + 1) % e != 0){
		k++;
	}
	d = ((k*phi_n) + 1)/e;
	return d;
}

int main(int argc, const char *argv[]){
	try{
		KeyGeneration obj1;
		obj1.prompter();
		obj1.primality_check();
		cout<<obj1.calculate_n()<<endl;
		cout<<obj1.calculate_phi()<<endl;
		cout<<obj1.calculate_e()<<endl;
		cout<<obj1.calculate_d()<<endl;
		//cout<<obj1.gcd(53,61);
	}
	catch(runtime_error &s ){
		cout<<s.what()<<endl;
	}
	return 0;
}
