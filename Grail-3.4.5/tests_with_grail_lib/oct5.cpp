#include "grail_lib.h"
#include <iostream>
#include <string>
//using namespace std;

int main()
{
//get the string 
	std::cout << "Please enter the word to test:";
	string<char> str;
	std::string input_string;
	std::cin >> input_string;

	for (int a = 0; a < input_string.length(); a++)
		str += (char) (input_string[a]);

// calculate the length
	int l; //lenghth of the string
	l = str.size();
	std::cout << "You input <" << str << ">, length is " << l << std::endl;

//generare all the prefix
	array<string<char> > words;

	for (int a = 0; a <= l; a++)
	{
		words[a].clear();
		for (int b = 0; b < a; b++)
		{
			words[a] += str[b];
		}
//output the prefix
		std::cout << "The prefix " << a << " is " << words[a] << std::endl;
	}

	fcm<char> min, max; //holder
	int n = 10000000, x = 0; //min and  max size of dfca

//for the lengh l, there will be 2 to l languages
//test them and record the smallest and biggest dfca
	for (long a = 0; a < pow((long) 2, (long) (l + 1)); a++)
	{
		if (a % 10000 == 0)
		{
			std::cout << "working on No." << a << "sub language" << std::endl;
		}
		fl<char> language; //temp language
		language.clear();

//assamble the language by proccess the binary form of the index
		long index = a;
		int digit = 0;
		while (index != 0)
		{
			if (index % 2 == 1)
			{
				language += words[digit];
			}
			index /= 2;
			digit++;
		}

//if the original word is not in it, add it in
		if (language.member(str) < 0)
			language += str;

		std::cout << "The language is " << std::endl << language;

		fm<char> dfa;
		dfa.fltofm(language);

//if(dfa.number_of_states()<2)
//	continue;

		std::cout << "The fm is " << std::endl << dfa;

		fcm<char> dfca;

		dfca.convert_to_fcm2(dfa);

		std::cout << "The fcm is " << std::endl << dfca;

		dfca.fcmmin(); //make sure it is minimized

		if (dfca.fm<char>::number_of_states() > x)
		{
			x = dfca.fm<char>::number_of_states();
			max = dfca;
		}

		if (dfca.fm<char>::number_of_states() < n)
		{
			n = dfca.fm<char>::number_of_states();
			min = dfca;
		}

	}

	std::cout << "test results:" << std::endl;
	std::cout << "min:" << std::endl << min << std::endl;

	std::cout << "max:" << std::endl << max << std::endl;
	;

	return 0;
}
