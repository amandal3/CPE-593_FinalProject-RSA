#include <iostream>
#include <gmp.h>
#include "gmpxx.h"
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
            4. Public Key: Choose an integer e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1; i.e., e and phi(n) are coprime.
            5. Private Key: Calculate d as d ≡ e^−1 (mod phi(n)); here, d is the modular multiplicative inverse of e modulo phi(n).
            6. For encryption, c = m^e mod n, where m = original message.
            7. For decryption, m = c^d mod n.
   Cite 2: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
        Used to make the number generation of public key more random than would be using rand.
*/

char encryption[10];

// x^n mod m
// int powermod(int x, int n, int m)
// {
// 	int prod = 1;
// 	while (n > 0) {
// 		if (n % 2 != 0) {
// 			prod = (prod * x) % m;
// 		}
// 		x = x * x % m;
// 		n = n / 2;
// 	}
// 	return prod;
// }

void generate_keys(mpz_t p, mpz_t q) {
    //Miller-Rabin Prime: Determine whether n is prime. Return 2 if n is definitely prime, 
    // return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.
    if (mpz_probab_prime_p(p, 1) == 2 && mpz_probab_prime_p(q, 1) == 2){
        if (p == q){
            cout << " Cannot have identical prime numbers"<<endl;
        }

        mpz_t n, phi, e, check, d;
        mpz_inits(n, phi, e, check, d, NULL);
        mpz_mul(n, p, q);
        mpz_sub_ui(p, p, 1);
        mpz_sub_ui(q, q, 1);
        mpz_mul(phi, p, q);

        cout << "n: " << n << " phi: " << phi << endl;

        // int n = p * q;//calculate n
        // int phi = (p-1) * (q-1)
        // int toient = lcm(p-1, q-1);

        // cout << phi << endl;

    //     cout<<"\n"<<"p = "<<p;
    //     cout<<"\n"<<"q = "<<q;
    //     cout<<"\n"<<"n = p*q = "<<n;
    //     cout<<"\n"<<"phi = "<<phi<< endl;

    //     // E such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
        // random_device rd;
        // mt19937 gen(rd()); //A Mersenne Twister pseudo random generation of 32-bit numbers & state size of 19937 bits
        // uniform_real_distribution<> distr(1, phi); // define the range
        gmp_randstate_t rd;
        gmp_randinit_mt(rd);
        mpz_urandomm(e, rd, phi);

        cout << "e: " << e << endl;

        while (mpz_cmp(e, phi) < 0){
            mpz_gcd(check, e, phi);
            cout << "check: " << check << endl;
            if (mpz_cmp_ui(check, 1) == 0){
                break;
            }
            else {
                mpz_urandomm(e, rd, phi);
                cout << "next e: " << e << endl;
            }
        }
        cout << "final e: " << e << endl;
        
    //     // D ≡ e^−1 (mod phi(n))
    //     // d = fmod(1/e, phi);
    //     d = (1 + (2*toient))/e;
        // d = 1/e % toient;


    //     if (e*d == 1 % phi){
    //         cout << "okay...." <<endl;
    //     }
    //     else {
    //         cout << "not okay" << endl;
    //     }
    }
    else {
        cout << " P and Q are not primes." << endl;
    }
}

// void encryptMsg(int pbk, string msg, int n){
// //    For encryption, c = m^e mod n, where m = original message.
//     int ciphertxt;
//     int temp=1;
//     int x;

//     for (int i = 0; i < msg.length(); i++)
//     {
//         x = int(msg.at(i));
//         // cout << x << ".";
//         // ciphertxt = powermod(x, pbk, n);
//         // temp = pow(x, pbk); // m^e where m = message and e = public key
//         // ciphertxt = temp % n; 
//         for (int j= 0; j < pbk; j++){
//             temp = x * temp;
//         }
//         ciphertxt = temp % n;
//         cout << ciphertxt << "." ;
//         encryption[i] = ciphertxt;
//     }
//     cout << endl;
    
//     for (int j = 0; j < sizeof(encryption)/sizeof(encryption[0]); j++){
//         cout << encryption[j] << " ";
//     }
//     cout <<"len " << sizeof(encryption)/sizeof(encryption[0]);
//     // for (int j = 0; j < strlen(encryption); j++){
//     //     cout << encryption[j] << " ";
//     // }
//     // cout <<"len " << strlen(encryption);
//     cout << endl;
// }

// void decryptMsg(int prvk, int n){
// //    For decryption, m = c^d mod n.
//     int spooky, temp=1;
//     char spookyNoMore;
//     char y;

//     for (int i = 0; i < sizeof(encryption)/sizeof(encryption[0]); i++)
//     { 
//         y = int(encryption[i]); // y holds the encrypted message [int]
//         cout << "y: " << y << endl;
//         for (int j= 0; j < prvk; j++){
//             temp = y * temp;
//         }
//         spooky = temp % n;
//         // temp = pow(y, prvk);                // c^d where c = encrypted message and d = private key
//         // spooky = fmod(temp, n);        
//         cout << "spooky: " << spooky << endl;  
//         spookyNoMore = char(spooky);
//         // spookyNoMore = powermod(encryption[i], prvk, n);
//         // spookyNoMore = int(pow(encryption[i], prvk)) % n;
//         // spookyNoMore = fmod(encryption[i] * prvk, n);
//         cout << spookyNoMore << " " << endl;
//     }
//     cout << endl;   
// }

int main() {

    mpz_t p, q, n;
    // const mpz_t apple = 55702919;
    mpz_init(n);
    mpz_init_set_ui(p, 11);
    mpz_init_set_ui(q, 13);
    mpz_mul(n, p, q);

    cout << p << " " << q << " " << n  <<endl;
    
    cout << "\n... Generating public/private key ..." << endl;
    generate_keys(p , q);
    // cout << "Public Key: " << e << endl;
    // cout << "Private Key: " << d << endl;

    // // cout << "test: " << fmod(d*e, toient) << endl;

    // string message = "a";
    // // string message = "apple sauce is gross.";
    // cout<<"\nOriginal Message = "<< message << endl;
    // cout << "\n... Encrypting message ..." << endl;
    // cout << "Encrypted Message: ";
    // encryptMsg(e, message, n);

    // cout << "\n... Decrypting message ..." << endl;
    // cout << "Decrypted Message: ";
    // decryptMsg(d, n);

    return 0;
}