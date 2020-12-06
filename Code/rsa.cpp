// Amanda Ly & Ghaith Arar
// RSA using GMP
// Programs should be linked with the libgmpxx and libgmp libraries

#include <iostream>
//#include <gmp.h>
#include "gmpxx.h"
#include <string>
#include <time.h>
#include <string> 
#include <ctime> 
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
         * 
         * 
         * 
         * Random Number Functions
         * Sequences of pseudo-random numbers in GMP are generated using a variable of type gmp_
            randstate_t, which holds an algorithm selection and a current state. Such a variable must be
            initialized by a call to one of the gmp_randinit functions, and can be seeded with one of the
            gmp_randseed functions.
         * 
*/

mpz_t e, d;
vector <int> arr;

void generate_keys(mpz_t p, mpz_t q) {
    //Miller-Rabin Prime: Determine whether n is prime. Return 2 if n is definitely prime, 
    // return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.
    if (mpz_probab_prime_p(p, 50) == 2 && mpz_probab_prime_p(q, 50) == 2){
        if (p == q){
            cout << " Cannot have identical prime numbers"<<endl;
            return;
        }

        mpz_t phi, check;
        mpz_inits(phi, e, check, d, NULL);
        // mpz_mul(n, p, q);
        mpz_sub_ui(p, p, 1);
        mpz_sub_ui(q, q, 1);
        mpz_mul(phi, p, q);

        // cout << "n: " << n << " phi: " << phi << endl;
        // E such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
        // random_device rd;
        // mt19937 gen(rd()); //A Mersenne Twister pseudo random generation of 32-bit numbers & state size of 19937 bits
        // uniform_real_distribution<> distr(1, phi); // define the range
        gmp_randstate_t rd;
        gmp_randinit_mt(rd);   // Initialize state for a Mersenne Twister algorithm. 
                                //This algorithm is fast and has good randomness properties.
        unsigned long int seed = 20201204; 
        gmp_randseed_ui (rd, seed);
        
        // The size of a seed determines how many different sequences of random numbers that it’s
        //possible to generate. The “quality” of the seed is the randomness of a given seed compared
        //to the previous seed used, and this affects the randomness of separate number sequences. The
        //method for choosing a seed is critical if the generated numbers are to be used for important
        //applications, such as generating cryptographic keys.
        //Traditionally the system time has been used to seed, but care needs to be taken with this.
        //If an application seeds often and the resolution of the system clock is low, then the same
        //sequence of numbers might be repeated. Also, the system time is quite easy to guess, so if
        //unpredictability is required then it should definitely not be the only source for the seed value.
        //On some systems there’s a special device /dev/random which provides random data better
        //suited for use as a seed.

                
        mpz_urandomm(e, rd, phi); //Generate a uniform random integer in the range 0 to n n-1, inclusive.
                                    // We need to check if the random number is 0 
        // cout << "e: " << e << endl;

        while (mpz_cmp(e, phi) < 0){
            mpz_gcd(check, e, phi); // We need to test if gcd(e, phi) = 1  
                                    // mpz_gcd sets (check) to the greatest common divisor of (e) and (phi). The result is always positive even if
                                    //one or both input operands are negative. Except if both inputs are zero; then this function
                                    //defines gcd(0; 0) = 0.
            
            
            if (mpz_cmp_ui(check, 1) == 0){     //int mpz_cmp_ui (const mpz t op1, unsigned long int op2)
                                                //Compare op1 and op2. Return a positive value if op1 > op2, zero if op1 = op2, or a negative
                                                //value if op1 < op2.
                break;
            }
            else {
                seed = seed + 3;                // Increase seed by arbitrary number. Here it is 3
                gmp_randseed_ui (rd, seed);
                mpz_urandomm(e, rd, phi);
                                                    // cout << "next e: " << e << endl;

            }
        }
                                                    // cout << "final e: " << e << endl;
        
                                                    // D ≡ e^−1 (mod phi(n))
                                                    // mpz_invert op1*rop = 1 mod op2
        
        mpz_invert(d, e, phi);                      //int mpz_invert (mpz t rop, const mpz t op1, const mpz t op2)
                                                    //Compute the inverse of op1 modulo op2 and put the result in rop. If the inverse exists, the
                                                    //return value is non-zero and rop will satisfy 0 <= rop < |op2| (with rop = 0 possible only
                                                    //when jop2j = 1, i.e., in the somewhat degenerate zero ring). If an inverse doesn’t exist the
                                                    //return value is zero and rop is undefined. The behaviour of this function is undefined when
                                                    //op2 is zero.
        mpz_clears(check, phi, NULL);               // mpz_clears frees the space occupied by a NULL-terminated list of mpz_t variables.
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
        // cout << "i is: " << i << " the vaule of ciphertxt is: " << ciphertxt << endl;
        tst = mpz_get_ui(ciphertxt);   // If op is too big to fit an unsigned long then just the least significant bits that do fit are
                                        // returned. The sign of op is ignored, only the absolute value is used.
        
        // cout << "i is: " << i << " the vaule of ciphertxt to int is: " << tst << endl;
        arr.push_back(int(tst));
        
        //cout << "i is: " << i << endl;
        //cout << "Real letter is " << msg.at(i) << endl;
        cout << tst;
        
        
    }
    cout << endl;
    mpz_clears(x, ciphertxt, NULL);
    cout << endl;
}







void decryptMsg(mpz_t prvk, mpz_t n){
//    For decryption, m = c^d mod n.
    mpz_t OG, c, temp;
    mpz_t N1, N2;
    mpz_inits(N1, N2, NULL);
    mpz_init_set(N1, prvk);
    mpz_init_set(N2, n);

    
    mpz_init(c);
    long int temp2 = 0;
    
   // cout << prvk << " " << n << endl;
   //  cout << "Arr size is: " << arr.size() << endl;
    
    for (int i = 0; i < arr.size(); i++){
        temp2 = arr[i];
        mpz_init_set_ui(temp, temp2); //1
        mpz_set_ui(c, temp2);           //2
        //cout << temp << " ";            //3
        
        mpz_powm(OG, temp, N1, N2);
        //mpz_powm(OG, temp, prvk, n);        //4
    
    
    unsigned long int tst2;
    tst2 = mpz_get_ui(OG);
    cout << static_cast<char>(tst2); 
    }
    cout <<endl; 
}









int main() {

    mpz_t p, q, n;
    mpz_init(n);
    mpz_init(p);
    mpz_init(q);
    
    gmp_randstate_t P_rn;
    gmp_randstate_t Q_rn;
    gmp_randinit_mt(P_rn);
    gmp_randinit_mt(Q_rn);
    //unsigned long int seed_P = 20201209;
    //unsigned long int seed_Q = 20201276;
    gmp_randseed_ui (P_rn, time(NULL));
    gmp_randseed_ui (Q_rn, time(NULL)*3);
    mp_bitcnt_t P_N = 8;
    mp_bitcnt_t Q_N = 8;
    
    mpz_urandomb (p, P_rn, P_N);
    mpz_urandomb (q, Q_rn, Q_N);
    
    while (1){
          if (mpz_probab_prime_p(p, 20) > 0){
              break;
              }
            else
                {

                gmp_randseed_ui (P_rn, time(NULL));
                mpz_urandomb (p, P_rn, P_N);
                }
        }


    while (1){
          if (mpz_probab_prime_p(q, 20) > 0){
              break;
              }
            else
                {
 
                gmp_randseed_ui (Q_rn, time(NULL)*3);
                mpz_urandomb (q, Q_rn, Q_N);
                }
        }




    mpz_mul(n, p, q);

    cout << p << " " << q << " " << n;
    
    cout << endl << "*** Generating public/private key ***" << endl;
    generate_keys(p , q);
    cout << "Public Key: " << e << endl;
    cout << "Private Key: " << d << endl;

    string message = "THIS IS A TEST";
    cout<<"\nOriginal Message: "<< endl << message << endl;
    cout << "... Encrypting message ..." << endl;
    cout << "Encrypted Message: ";
    encryptMsg(e, message, n);

    cout << "\n... Decrypting message ..." << endl;
    cout << "Decrypted Message: " << endl;
    decryptMsg(d, n);
    cout << "Private Key: " << d << endl;

    return 0;
}