// Amanda Ly
// RSA using GMP
// Programs should be linked with the libgmpxx and libgmp libraries

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

mpz_t e, d;
vector <int> arr;

void generate_keys(mpz_t p, mpz_t q) {
    //Miller-Rabin Prime: Determine whether n is prime. Return 2 if n is definitely prime, 
    // return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.
    if (mpz_probab_prime_p(p, 50) == 2 && mpz_probab_prime_p(q, 50) == 2){
        if (p == q){
            cout << " Cannot have identical prime numbers"<<endl;
        }

        mpz_t phi, check;
        mpz_inits(phi, e, check, d, NULL);
        // mpz_mul(n, p, q);
        mpz_sub_ui(p, p, 1);
        mpz_sub_ui(q, q, 1);
        mpz_mul(phi, p, q);

        // cout << "n: " << n << " phi: " << phi << endl;

    //     // E such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
        // random_device rd;
        // mt19937 gen(rd()); //A Mersenne Twister pseudo random generation of 32-bit numbers & state size of 19937 bits
        // uniform_real_distribution<> distr(1, phi); // define the range
        gmp_randstate_t rd;
        gmp_randinit_mt(rd);
        mpz_urandomm(e, rd, phi);

        // cout << "e: " << e << endl;

        while (mpz_cmp(e, phi) < 0){
            mpz_gcd(check, e, phi);
            // cout << "check: " << check << endl;
            if (mpz_cmp_ui(check, 1) == 0){
                break;
            }
            else {
                mpz_urandomm(e, rd, phi);
                // cout << "next e: " << e << endl;
            }
        }
        // cout << "final e: " << e << endl;
        
        // D ≡ e^−1 (mod phi(n))
        // mpz_invert op1*rop = 1 mod op2
        
        mpz_invert(d, e, phi);
        mpz_clears(check, phi, NULL);
        // cout << "d value: " << d << endl;
    }
}

void encryptMsg(mpz_t pbk, string msg, mpz_t n){
//    For encryption, c = m^e mod n, where m = original message.
    mpz_t ciphertxt, x;
    // int i = 0;
    unsigned long int tst;
    // mpz_class i; 
    mpz_init(ciphertxt);

    
    for (int i = 0; i < msg.length(); i++)
    {
        // x = int(msg.at(i));
        mpz_init_set_ui(x, int(msg.at(i)));

        // cout << x << ".";
        // ciphertxt = powermod(x, pbk, n);
        mpz_powm(ciphertxt, x, e, n);

        tst = mpz_get_ui(ciphertxt);
        cout << char(tst) << " ";
        arr.push_back(int(tst));
    }
    cout << endl;
    mpz_clears(x, ciphertxt, NULL);
}

void decryptMsg(mpz_t prvk, mpz_t n){
//    For decryption, m = c^d mod n.
    mpz_t OG, c, temp;
    mpz_init(c);

    cout << prvk << " " << n << endl;

    for (int i = 0; i < arr.size(); i++){
        // cout << " i made it " <<endl;
        mpz_init_set_ui(temp, arr[i]);
        mpz_set(c, temp);
        cout << temp << " ";
        mpz_powm(OG, temp, prvk, n);

    //     // cout << spookyNoMore << " "; 
    }
    cout <<endl; 
}

int main() {

    mpz_t p, q, n;
    mpz_init(n);
    mpz_init_set_ui(p, 11);
    mpz_init_set_ui(q, 13);
    mpz_mul(n, p, q);

    cout << p << " " << q << " " << n;
    
    cout << "\n... Generating public/private key ..." << endl;
    generate_keys(p , q);
    cout << "Public Key: " << e << endl;
    cout << "Private Key: " << d << endl;

    string message = "apple sauce sucks.";
    cout<<"\nOriginal Message = "<< message << endl;
    cout << "... Encrypting message ..." << endl;
    cout << "Encrypted Message: ";
    encryptMsg(e, message, n);

    cout << "\n... Decrypting message ..." << endl;
    cout << "Decrypted Message: ";
    decryptMsg(d, n);

    return 0;
}