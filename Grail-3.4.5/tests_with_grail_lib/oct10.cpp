#include "grail_lib.h"
#include <iostream>
#include <string>
//using namespace std;

fcm<char> min, max; //holder
int n = 10000000, x = 0; //bounds of minimal size of dfca
string<char> mins, maxs; //the corresponding string
int count[12]; //statistics

void process(string<char>); //calculate one string

int main()
{
//clean statistics
	for (int a = 0; a < 12; a++)
		count[a] = 0;

//get the string 
	string<char> toTest;
	for (long a = 0; a < pow(2, 10); a++)
	{

		std::cout << "percentage:" << (float) a / pow(2, 10) << std::endl;

		toTest.clear();
		int value = a;
//assemble the string with the value a
		for (int b = 0; b < 10; b++)
		{
			if (value / 2 * 2 == value)
				toTest += 'b';
			else
				toTest += 'a';

			value /= 2;
		}

		process(toTest);
	}

	std::cout << "[test results:]" << std::endl;
	std::cout << "lower bound:" << std::endl << min << std::endl;
	std::cout << "upper bound:" << std::endl << max << std::endl;
	;
	std::cout << "statistics:" << std::endl;
	for (int a = 0; a < 12; a++)
	{
		std::cout << "Minimal dfca  size: " << a << " : " << count[a]
				<< std::endl;

	}

	return 0;
}

void process(string<char> str)
{

// calculate the length
	int l; //lenghth of the string
	l = str.size();
//std::cout<<"You input <"<<str<<">, length is "<<l<<std::endl;

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
//std::cout<<"The prefix "<<a<<" is "<<words[a]<<std::endl;
	}

	fcm<char> smallestInThisStr; //the smallest of the string;
	smallestInThisStr.clear();
	int sm = 1000;

//for the lengh l, there will be 2 to l languages
//test them and record the smallest and biggest dfca
	for (long a = 0; a < pow((long) 2, (long) l); a++)
	{
		if (a % 10000 == 0)
		{
//std::cout<<"working on No."<<a<<"sub language"<<std::endl;
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

//ithe original word is not in it, add it in
		language += str;

//std::cout<<"The language is "<<std::endl<<language;

		fm<char> dfa;
		dfa.fltofm(language);

//if(dfa.number_of_states()<2)
//	continue;

//std::cout<<"The fm is "<<std::endl<<dfa;

		fcm<char> dfca;

		dfca.convert_to_fcm2(dfa);

//std::cout<<"The fcm is "<<std::endl<<dfca;

		dfca.fcmmin(); //make sure it is minimized

		if (dfca.fm<char>::number_of_states() < sm)
		{
			sm = dfca.fm<char>::number_of_states();
			smallestInThisStr = dfca;
		}

	}

	std::cout << "The samllest dfca for word " << str << " is " << std::endl
			<< smallestInThisStr << std::endl;

	count[smallestInThisStr.fm<char>::number_of_states()]++;

	if (smallestInThisStr.fm<char>::number_of_states() > x)
	{
		x = smallestInThisStr.fm<char>::number_of_states();
		max = smallestInThisStr;
	}

	if (smallestInThisStr.fm<char>::number_of_states() < n)
	{
		n = smallestInThisStr.fm<char>::number_of_states();
		min = smallestInThisStr;
	}

}
