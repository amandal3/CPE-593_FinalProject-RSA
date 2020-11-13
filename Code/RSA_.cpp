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

int main(){
	GCD g1;
	GCD g2(10,5);
	RPrime r1(100);
	Encryption e1(1,2 );

	//cout<<"g1: "<<g1.calculate(g1)<<" "<<'\n';
	//g1.print();cout<<'\n';
	//cout<<"g2: "<<g2.calculate(g2)<<" "<<'\n';
	//g2.print();cout<<'\n';

	r1.generate(r1);
	cout<<e1.check();

}