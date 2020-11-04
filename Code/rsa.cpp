#include <iostream>
#include "BigIntegerLibrary.hh"
#include <string>
#include <math.h> // to use fmod
#include <random> // for stackoverflow rand
#include <tuple> //for generate_keys function
using namespace std;

/*  Cite 1: https://www.tutorialspoint.com/cplusplus-program-to-implement-the-rsa-algorithm
        Used for concept and idea of what algorithm consists of:
            1. Choose two prime numbers p and q.
            2. Compute n = p*q.
            3. Calculate phi = (p-1) * (q-1).
            4. Choose an integer e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
            5. Calculate d as d ≡ e^−1 (mod phi(n)); here, d is the modular multiplicative inverse of e modulo phi(n).
            6. For encryption, c = m^e mod n, where m = original message.
            7. For decryption, m = c^d mod n.
   Cite 2: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
        Used to make the number generation of public key more random than would be using rand.
*/

char encryption[10];
int e, d;

int gcd(int a, int b) // O(b) ???
{
    int r;
    while (b != 0){
        r = a % b;
        a = b;
        b = r;
    }
    return a; 
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

bool isPrime(int n) { //O(sqrt n
	for (int i = 2; i <= sqrt(n); i++) { 
		if (fmod(n,i) == 0.0)
			return false; // not prime
	}
	return true; // prime
}

// x^n mod m
int powermod(int x, int n, int m)
{
	int prod = 1;
	while (n > 0) {
		if (n % 2 != 0) {
			prod = (prod * x) % m;
		}
		x = x * x % m;
		n = n / 2;
	}
	return prod;
}

void generate_keys(int p, int q) {
    if (isPrime(p) && isPrime(q)){
        if (p == q){
            cout << " Cannot have identical prime numbers"<<endl;
        }
        int n = p * q;//calculate n
        int phi = (p-1) * (q-1);//calculate phi aka the totient
        int toient = lcm(p-1, q-1);

        cout<<"\n"<<"p = "<<p;
        cout<<"\n"<<"q = "<<q;
        cout<<"\n"<<"n = p*q = "<<n;
        cout<<"\n"<<"phi = "<<phi<< endl;

        // E such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
        random_device rd;
        mt19937 gen(rd()); //A Mersenne Twister pseudo random generation of 32-bit numbers & state size of 19937 bits
        uniform_real_distribution<> distr(1, phi); // define the range

        e = distr(gen);
        while (e < toient){
            int check = gcd (e, toient);
            cout << "check: " << check << endl;
            if (check == 1){
                break;
            }
            else {
                e = distr(gen);
            }
        }
        cout << "e: " << e << endl;
        
        // D ≡ e^−1 (mod phi(n))
        // d = fmod(1/e, phi);
        d = (1 + 2*toient)/e;
    }
    else {
        cout << " P and Q are not primes." << endl;
    }
}

void encryptMsg(int pbk, string msg, int n){
//    For encryption, c = m^e mod n, where m = original message.
    int ciphertxt;
    int temp=1;
    int x;

    for (int i = 0; i < msg.length(); i++)
    {
        x = int(msg.at(i));
        // cout << x << ".";
        // ciphertxt = powermod(x, pbk, n);
        // temp = pow(x, pbk); // m^e where m = message and e = public key
        // ciphertxt = temp % n; 
        for (int j= 0; j < pbk; j++){
            temp = x * temp;
        }
        ciphertxt = temp % n;
        cout << ciphertxt << "." ;
        encryption[i] = ciphertxt;
    }
    cout << endl;
    
    for (int j = 0; j < sizeof(encryption)/sizeof(encryption[0]); j++){
        cout << encryption[j] << " ";
    }
    cout <<"len " << sizeof(encryption)/sizeof(encryption[0]);
    // for (int j = 0; j < strlen(encryption); j++){
    //     cout << encryption[j] << " ";
    // }
    // cout <<"len " << strlen(encryption);
    cout << endl;
}

void decryptMsg(int prvk, int n){
//    For decryption, m = c^d mod n.
    int spooky, temp=1;
    char spookyNoMore;
    char y;

    for (int i = 0; i < sizeof(encryption)/sizeof(encryption[0]); i++)
    { 
        y = int(encryption[i]); // y holds the encrypted message [int]
        cout << "y: " << y << endl;
        for (int j= 0; j < prvk; j++){
            temp = y * temp;
        }
        spooky = temp % n;
        // temp = pow(y, prvk);                // c^d where c = encrypted message and d = private key
        // spooky = fmod(temp, n);        
        cout << "spooky: " << spooky << endl;  
        spookyNoMore = char(spooky);
        // spookyNoMore = powermod(encryption[i], prvk, n);
        // spookyNoMore = int(pow(encryption[i], prvk)) % n;
        // spookyNoMore = fmod(encryption[i] * prvk, n);
        cout << spookyNoMore << " " << endl;
    }
    cout << endl;   
}

int main() {

    int p = 7;
    int q = 13; 

    int n = p * q;
    int toient = lcm(p-1, q-1);

    cout << "\n... Generating public/private key ..." << endl;
    generate_keys(p , q);
    cout << "Public Key: " << e << endl;
    cout << "Private Key: " << d << endl;

    // cout << "test: " << fmod(d*e, toient) << endl;

    string message = "a";
    // string message = "apple sauce is gross.";
    cout<<"\nOriginal Message = "<< message << endl;
    cout << "\n... Encrypting message ..." << endl;
    cout << "Encrypted Message: ";
    encryptMsg(e, message, n);

    cout << "\n... Decrypting message ..." << endl;
    cout << "Decrypted Message: ";
    decryptMsg(d, n);

    return 0;
}