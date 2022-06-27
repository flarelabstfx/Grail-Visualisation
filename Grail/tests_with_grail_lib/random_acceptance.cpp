//for request test 2:
/*

 The other thing I need is to find for me some topological/measure
 theory/probabilistic results relating the set of finite languages(DFAs
 accepting finite languages) to regular languages in general
 (arbitrary DFAs or DFAs recognizing infinite languages only).
 For example what is the probability that a random DFA recognizes a finite
 language? or is the set of finite languages dense in the set of regular
 languages?


 */

#include "grail_lib.h"
#include "math.h"
using std::cin;

long tobase(long num, int base);
int * comp_digits(long num, int * digits, int digit_num);

int main()
{
//alphabets 
	char alphabets[10] =
	{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	int alpha_num = 2; //now we use a b
	int states_num = 3; // this test is for 3 states

	std::cout << "states number=";
	cin >> states_num;

// the big guy who hold all dfas
	array<fm<char> *> dfas;

//first step, create all the COMPLETED DFA 
	for (long a = 0; a < pow(states_num, alpha_num * states_num); a++) //shape
	{
		int * shape_digits = new int[alpha_num * states_num];
		comp_digits(tobase(a, states_num), shape_digits,
				alpha_num * states_num);

		for (int b = 0; b < pow(2, states_num); b++) //finals
		{
			int * final_digits = new int[states_num];
			comp_digits(tobase(b, 2), final_digits, states_num);

//with the numbers, we make a completed dfa

			fm<char> * dfa = new fm<char>();
//structure
			for (int c = 0; c < alpha_num * states_num; c++)
			{
				int start = c / alpha_num;
				int end = shape_digits[c];
				int alph = c % alpha_num;

				inst<char> tmpInst;
				tmpInst.assign(start, alphabets[alph], end);
				dfa->add_instruction(tmpInst);
			}
//finals
			for (int c = 0; c < states_num; c++)
			{
				if (final_digits[c] == 1)
				{
					state tmp(c);
					dfa->add_final(tmp);
				}
			}

			dfa->add_start(0);

//debug
			/*
			 for(int x=0;x<alpha_num*states_num;x++)
			 std::cout<<shape_digits[x];

			 std::cout<<std::endl;

			 for(int x=0;x<states_num;x++)
			 std::cout<<final_digits[x];


			 std::cout<<"dfa"<<std::endl;
			 std::cout<<*dfa<<std::endl;
			 */

			delete final_digits;

//test if the dfa is valid
			dfa->reachable_fm();
			if (dfa->number_of_states() == states_num)
			{

				dfas += dfa;
				continue;

			}

//not useful
			delete dfa;

		}

		delete shape_digits;

	}

//now we have all the valid dfas

	/*
	 for(int x=0;x<dfas.size();x++)
	 std::cout<<*dfas[x]<<std::endl;
	 */

	std::cout << "we have " << dfas.size() << " valid dfas" << std::endl;
	std::cout << std::endl;

//we now have all the dfas, ask for language ansd tests

	int want_continue = 1;

	while (want_continue)
	{
		std::cout << "@Please enter the finite language  to test:" << std::endl;

		fl<char> lan;
		lan.clear();

		cin.ignore(); // rmove the sticky empty input

		std::cin >> lan;
		std::cout << "get language" << std::endl << lan;
		set<string<char> > words_lan;
		lan.get_words(words_lan);

//now  we count how many dfas accept this language

		int acc_count = 0;

		for (int a = 0; a < dfas.size(); a++)
		{
			bool accept = true;

			for (int b = 0; b < words_lan.size(); b++)
			{
				if (!dfas[a]->member_of_language(words_lan[b], 0))
				{
					accept = false;
					break;
				}
			}

			if (accept)
				acc_count++;

		}

		std::cout << acc_count << " dfas among " << dfas.size()
				<< " accept the language." << std::endl << "< < < < < <" << std::endl
				<< std::endl;

//clear EOF in languge entry
		cin.clear();

		std::cout << std::endl << "> > > > > >" << std::endl
				<< "enter 1 to continue, 0 to quit" << std::endl;
		std::cin >> want_continue;
	}

	return 0;
}

//help method to base n;
long tobase(long num, int base)
{
	long n = num;
	if (n < base)
		return n;
	else
		return (tobase(n / base, base) * 10 + n % base);
}

//help method, complete digits
int * comp_digits(long num, int * digits, int digit_num)
{

	for (int a = 0; a < digit_num; a++)
	{
		digits[a] = num / pow(10, digit_num - a - 1);
		num -= digits[a] * pow(10, digit_num - a - 1);
	}
	return digits;
}

