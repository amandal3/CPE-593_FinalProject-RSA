//Written by: Neel Haria, Amanda Ly and Ghaith Arar

#include<boost/multiprecision/cpp_int.hpp>
#include<iostream>
#include<cmath>
#include<vector>
#include<numeric>
using namespace std;


class KeyGeneration {
public:
	unsigned p; //First prime Number
	unsigned q; // Second Prime Number
	unsigned n; // For the product of p and q
	unsigned phi_n; // For the product of p-1 and q-1
	unsigned e; // Select e such that e is co-prime to phi_n, 1<e<phi_n
	unsigned d; //d such that e.d = 1 mod phi_n
	unsigned m; //Message to be encrypted

	boost::multiprecision::cpp_int c; //cipher text message
	boost::multiprecision::cpp_int m_0; //Decryption Result

	void prompter();
	void primality_check();
	unsigned calculate_n();
	unsigned calculate_phi();
	unsigned calculate_e();
	unsigned calculate_d();
	unsigned GCD(unsigned i, unsigned phi_n);

	boost::multiprecision::cpp_int encryption(); 
	//Using boost, since encryption function involves large computations
	boost::multiprecision::cpp_int decryption(); 
	//Using boost, since decryption function involves large computations
};

void KeyGeneration::prompter() {
	cout << "Please Enter first prime number p: ";
	cin >> p;
	cout << "Please Enter first prime number q: ";
	cin >> q;
}

void KeyGeneration::primality_check() { //Check if number is prime or not
	vector<unsigned> p_factors;
	for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(p)); i++) {
		if (p % i == 0) {
			p_factors.push_back(i);
			p_factors.push_back(p / i);
		}

	}
	vector<unsigned> q_factors;
	for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(q)); i++) {
		if (p % i == 0) {
			q_factors.push_back(i);
			q_factors.push_back(q / i);
		}

	}

	if (p_factors.size() != 0 || q_factors.size() != 0) {
		throw(runtime_error("Non Prime Input"));
	}
}

unsigned KeyGeneration::calculate_n() { //Calculate n = p*q
	n = p * q;
	return n;
}



unsigned KeyGeneration::GCD(unsigned i, unsigned phi_n) { 
//Calculate GCD to calculate e
	for (unsigned j = min(i, phi_n); j > 2; j--) {
		if (i % j == 0 && phi_n % j == 0) { return j; }
	}
}

unsigned KeyGeneration::calculate_e() { 
//Calculate e, such that 1<e<phi_n and e is co-prime to phi_n
	unsigned i = 2;

	while (GCD(i, phi_n) != 1) {
		i++;
	}
	e = i;
	if (e > phi_n) {
		throw(runtime_error("e is greater phi_n"));
	}
	return e;
}
unsigned KeyGeneration::calculate_phi() { 
//Calculate phi_n = (p-1) * (q-1)
	phi_n = (p - 1) * (q - 1);
	return phi_n;
}

unsigned KeyGeneration::calculate_d() { 
//Calculate d such that e.d = 1 mod phi_n
	/*
	e*d mod phi_n = 1
	*/
	unsigned k = 1;
	while ((k * phi_n + 1) % e != 0) {
		k++;
	}
	d = ((k * phi_n) + 1) / e;
	return d;
}

boost::multiprecision::cpp_int KeyGeneration::encryption() { //C=P^e mod n.
	cout << "Enter message m to encrypt: ";
	cin >> m;
	c = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(m), e))) % n;
	return c;
}

boost::multiprecision::cpp_int KeyGeneration::decryption() { //P = C^d mod n
	//c^d % n = m
	m_0 = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(c), d))) % n;
	return m_0;
}


int main(int argc, const char* argv[]) {
	
	try {
		KeyGeneration obj1;
		obj1.prompter();
		obj1.primality_check();
		cout << "n: "<<obj1.calculate_n() << endl;
		cout << "phi: "<<obj1.calculate_phi() << endl;
		
		cout << obj1.calculate_e() << endl;
		cout << obj1.calculate_d() << endl;
		
		
		cout << obj1.encryption()<<endl;
		cout << obj1.decryption() << endl;
		//cout<<obj1.gcd(53,61);
	}
	catch (runtime_error& s) {
		cout << s.what() << endl;
	}
	return 0;


}
