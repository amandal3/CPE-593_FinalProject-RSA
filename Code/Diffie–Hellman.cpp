
// Written by Ghaith Arar
// Diffie–Hellman Key Exchange using GMP
// Programs should be linked with the libgmpxx and libgmp libraries

#include <stdio.h>
#include <iostream>
#include <gmp.h>
#include <cmath>
#include <ctime> 
using namespace std;

int main() {

	cout << "test" << endl;

//In this protocol we have two parties, Alice and Bob, who would like to
//establish a shared secret key. There is possibly a trusted third party that properly
//chooses the public parameters which are needed for the key exchange. However, it is
//also possible that Alice or Bob generate the public parameters
//Strictly speaking, the DHKE consists of two protocols, the set-up protocol and the 
//main protocol, which performs the actual key exchange.	
	
	mpz_t p;  		//1. Choose a large prime p.
	mpz_t alpha; 	//2. Choose an integer α ∈ {2,3, . . . , p−2}.
	mpz_t op;		// Randomly generated number; used to get a prime number through mpz_nextprime 

	
	//The newer random number functions of GMP accept a state parameter that is read and modified.
	
	
	gmp_randstate_t state1;		//The variable must be initialized by calling one of the gmp_randinit functions 
	gmp_randstate_t state2;
	
	gmp_randinit_mt (state1);	//Initialize state for a Mersenne Twister algorithm.
	gmp_randinit_mt (state2);	//This algorithm is fast and has good randomness properties.
	
	
	mp_bitcnt_t n1 = 1024;		//Counts of bits of a multi-precision number are represented in the C type mp_bitcnt_t.
	
	mpz_t n2;
	mpz_init(n2);

	
	mpz_inits(p, alpha, op, NULL);	//The functions for integer arithmetic assume that all integer objects are initialized.
									//You do that by calling the function mpz_inits.
	
	gmp_randseed_ui(state1, time(NULL) );
	gmp_randseed_ui(state2, time(NULL) );
									
	mpz_urandomb (op, state1, n1); //Generate a uniformly distributed random integer in the range 0 to 2^(n1-1), inclusive.
	
	mpz_nextprime(p, op);		//Set p to the next prime greater than op.
								//This function uses a probabilistic algorithm to identify primes. 
								//For practical purposes it’s adequate, the chance of a composite passing will be extremely small.
	
	mpz_sub_ui(n2, p, 2); 				// n2 holds the value of P-2 in the formula α ∈ {2,3, . . . , p−2}.
	mpz_urandomm(alpha, state2, n2);	// Generate Random number less than p-2
	
	cout << "P is: " << endl;
	gmp_printf("attempt p: %Zd \n", p);
	cout << endl;
	
	cout << "n2 is: " << endl;
	gmp_printf("attempt n2: %Zd \n", n2);
	cout << endl;
	
	cout << "Alpha is: " << endl;
	gmp_printf("attempt alpha: %Zd \n", alpha);
	cout << endl;
	
	cout << "op is: " << endl;
	gmp_printf("attempt op: %Zd \n", op);
	cout << endl;
	
	cout << "n1 is: " << n1 << endl;
	
	cout <<"Is P prime: " << mpz_probab_prime_p(p, 60) << endl;
	cout <<"Is alpa prime: " << mpz_probab_prime_p(alpha, 60) << endl;
	
//These two values (p, alpha) are sometimes referred to as domain parameters. If Alice and
//Bob both know the public parameters p and α computed in the set-up phase, they
//can generate a joint secret key k as below

// Below:
// Alice choose a = kpr,A ∈ {2, . . . , p−2}
// Alice compute A = kpub,A ≡αa mod p

// Bob choose b = kpr,B ∈ {2, . . . , p−2}
// Bob compute B = kpub,B ≡αb mod p

  return 0;
}