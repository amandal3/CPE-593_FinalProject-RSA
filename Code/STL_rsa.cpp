
#include<iostream>
#include<cmath>
#include<vector>
#include<math.h>
#include<numeric>
#include<string>
using namespace std;

class KeyGeneration {
public:
	double p, q, n, e, d,phi_n,track,m,c,m_0,enck,enc,d1,dec,deck;

	void prompter();
	void prime_check();
	double calculate_n();
	double calculate_e();
	double calculate_d();
	double calcualte_phi();
	double GCD(double i , double phi);
	double encryption();
	double decryption();
};

void KeyGeneration::prompter() {
	cout << "enter first prime number p: ";
	cin >> p;
	cout << "enter first prime number q: ";
	cin >> q;
}

void KeyGeneration::prime_check() {
	vector<double> p_factors;
	for (double i = 2; i <= static_cast<double>(sqrt(p)); i++) {
		if (fmod(p,i) == 0) {
			p_factors.push_back(i);
			p_factors.push_back(p / i);
		}
	}
	vector<double> q_factors;
	for (double i = 2; i <= static_cast<double>(sqrt(q)); i++) {
		if (fmod(q,i) == 0) {
			p_factors.push_back(i);
			p_factors.push_back(p / i);
		}
	}
	if (p_factors.size() != 0 || q_factors.size() != 0) {
		throw(runtime_error("Non Prime Input"));
	}
}

double KeyGeneration::calculate_n() {
	n = p * q;
	return n;
}
double KeyGeneration::GCD(double i, double phi) {
	double temp; 
	for (;;) {
		temp = fmod(i, phi);
		if (temp == 0) {
			return phi;
		}
		i = phi;
		phi = temp;
	}
}

double KeyGeneration::calculate_e() {
	e = rand() % 100;
	while (e < phi_n) {
		track = GCD(e, phi_n);
		if (track == 1) {
			break;
		}
		else {
			e++;
		}
	}
	return e;
}

double KeyGeneration::calcualte_phi() {
	phi_n = (p - 1) * (q - 1);
	return phi_n;
}

double KeyGeneration::calculate_d() {
	 d1 = 1 / e;
	 d = fmod(d1, phi_n);                        //private key
	return d;
													   //double deck = pow(enc, d);
	
}

double KeyGeneration::encryption() {
	cout << "Enter Message: ";
	cin >> m; 
	enck = pow(m, e);
	d1 = 1 / e;
	d = fmod(d1, phi_n);                        //private key
	deck = pow(c, d);
	enc = fmod(enck, n);
	return enck;
}

double KeyGeneration::decryption() {
	double d1 = 1 / e;
	double d = fmod(d1, phi_n);                        //private key
	double deck = pow(enck, d);                         //decryption key 

	double dec = fmod(deck, n);
	return deck;
}
int main(int argc, const char* argv[]) {
	try {
	string message;
		KeyGeneration obj1;
		obj1.prompter();
		obj1.prime_check();
		cout << "n:"<<obj1.calculate_n() << endl;
		cout << "phi: " << obj1.calcualte_phi() << endl;
		cout << "e: " << obj1.calculate_e() << endl;
		cout << "d: " << obj1.calculate_d() << endl;
		cout << "Encryption: " << obj1.encryption() << endl;
		cout << "Decryption: " << obj1.decryption() << endl;
		
	}
	catch (runtime_error& s) {
		cout << s.what() << endl;
	}
	return 0;
	
}