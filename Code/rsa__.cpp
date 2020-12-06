#include<iostream>
#include<vector>
using namespace std;


int64_t display(vector<int64_t> vec){
	for(uint64_t i = 0; i<vec.size(); i++){
		cout<<vec.at(i)<<" ";
	}
	//cout<<'\n';
}
vector<int64_t> vec;
int64_t generate(int64_t n){
	
	bool *isPrime = new bool[n+1];
	for(uint64_t i = 2; i<=n; i++){
		isPrime[i] = true;
	}
	for(uint64_t i =2 ;i<=n ; i++){
		if(isPrime[i] == true){
			for(uint64_t j = 2*i; j<=n ; j+=i){
				isPrime[j] = false;
			}
		}
	}

	for(uint64_t i = 0; i<n ; i++){
		if(isPrime[i] == true){
			vec.push_back(i);
		}
	}

	cout<<display(vec);
}

int main(){
	generate(100);
}