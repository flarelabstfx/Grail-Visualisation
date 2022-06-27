//for request test 2:
/*

 Test to list all the DFA that after transformation  to DFCA, the size do not
 change

 before we test , we make sure the dfa does not have any unreachable states

 */

#include "grail_lib.h"
#include "math.h"
using std::cin;
using std::cout;

long toBase(long num, int base);
int * compDigits(long num, int * digits, int digit_num);
int find_count;

int main()
{
	find_count = 0;

//alphabets
	char alphabets[10] =
	{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	int alpha_num = 2; //now we use {a , b}
	int states_num = -1;

	std::cout << "states number=";
	cin >> states_num; //get the states number

	long long togo = pow(states_num, alpha_num * states_num);
	std::cout << togo << std::endl;
//first step, create all the COMPLETED DFA
	for (long long a = 0; a < togo; a++) //shape
	{
		std::cout << (float) (100 * a / togo) << "% ";
//std::cout<<"s";
		int * shape_digits = new int[alpha_num * states_num];
//std::cout<<"cb";
		compDigits(toBase(a, states_num), shape_digits, alpha_num * states_num);

		for (int b = 0; b < pow(2, states_num); b++) //finals
		{
//std::cout<<b;
			int * final_digits = new int[states_num];
			compDigits(toBase(b, 2), final_digits, states_num);

//with the numbers, we make a completed dfa

			fm<char> dfa;
			dfa.clear();
//structure
			for (int c = 0; c < alpha_num * states_num; c++)
			{
				int start = c / alpha_num;
				int end = shape_digits[c];
				int alph = c % alpha_num;

				inst<char> tmpInst;
				tmpInst.assign(start, alphabets[alph], end);
				dfa.add_instruction(tmpInst);
			}
//finals
			for (int c = 0; c < states_num; c++)
			{
				if (final_digits[c] == 1)
				{
					state tmp(c);
					dfa.add_final(tmp);
				}
			}

			dfa.add_start(0);

//debug
			/*
			 for(int x=0;x<alpha_num*states_num;x++)
			 //std::cout<<shape_digits[x];

			 //std::cout<<std::endl;

			 for(int x=0;x<states_num;x++)
			 //std::cout<<final_digits[x];


			 //std::cout<<"dfa"<<std::endl;
			 //std::cout<<dfa<<std::endl;
			 */

			delete final_digits;

//test if the dfa is valid
			dfa.reachable_fm();
			dfa.min_by_partition();
			dfa.complete();
			if (dfa.number_of_states() == states_num && dfa.is_finite())
			{
//this dfa does not contain unreachable states_num
				fcm<char> dfca;
				dfca.clear();
				dfca.convert_to_fcm2(dfa);
				if (dfca.fm<char>::number_of_states() == states_num)
				{
					find_count++;
					std::cout << "Find No. " << find_count << " :" << std::endl;
					std::cout << "Dfa" << std::endl << dfa << std::endl;
					std::cout << "Dfca" << std::endl << dfca << std::endl;

				}

			}

		}

		delete shape_digits;

	}

	return 0;
}

//help method to base n;
long toBase(long num, int base)
{
//std::cout<<"b";
	long n = num;
	if (n < base)
		return n;
	else
		return (toBase(n / base, base) * 10 + n % base);
}

//help method, complete digits
int * compDigits(long num, int * digits, int digit_num)
{

	for (int a = 0; a < digit_num; a++)
	{
//std::cout<<"c";
		digits[a] = num / pow(10, digit_num - a - 1);
		num -= digits[a] * pow(10, digit_num - a - 1);
	}
	return digits;
}
