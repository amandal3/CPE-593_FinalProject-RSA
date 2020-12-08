# CPE-593_FinalProject-RSA
### By Amanda Ly, Neel Haria, and Ghaith Arar
Implement RSA using a biginteger library. It doesn’t have to be production quality, but you would need to implement Diffie-Hellman key exchange and use AES-256 (you don’t have to write that) to exchange secret messages.


## Concerns: 
- RSA is having problems with decrypt (Amanda: I'm sure how to debug - been stuck on it for a week now) - Fixed Dec 5, 2020
- The algorithm doesn't generate large numbers for q, p. 

## Tasks To Do: 
- Generate p, q that are large engough to make encryption secure. Right now the algorithem accepts the first two prime numbers it can get.
- Add padding to the algorithem
- Use **void mpz_powm_sec (mpz t rop, const mpz t base, const mpz t exp(** instead of  **mpz_powm** .
- Generate a very large prime either (p, q) then use **mpz_nextprime** to generate the other one.

*"This function is designed to take the same time and have the same cache access patterns for any two same-size arguments, assuming that function arguments are placed at the same position and that the machine state is identical upon function entry. This function is intended for cryptographic purposes, where resilience to side-channel attacks is desired."*

- Feed text file to the algorithem instead of simple string.

- Begin writting final paper
- Put together final presentation

## Tasks Completed: 
- Diffie-Hellman Key Exchange
- RSA Algorithem

## RSA: 
The implemented algorithem is a textbook algorithm. The algorithm can be improved by adding padding. Each time the algorithm runs, it generate new two prime numbers and use them to generate the private and publick key. System time was used to seed the random number generator. 

to do:
-
The following is a screenshot for the RSA Algorithem test
![alt text](https://raw.githubusercontent.com/amandal3/CPE-593_FinalProject-RSA/main/Research%20Papers/RSA_test.png)
