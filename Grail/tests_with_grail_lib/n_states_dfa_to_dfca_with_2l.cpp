/* This is for tests:

 "
 Hi Ray and Sherry,

 I need you to do the following test:
 Take a random DFA with $n$ states.
 Use $n$ or $n/2$ as $l$ and compute the minimal DFCA
 for this $l$.
 Make a table with the results obtained and compute some average.
 "

 requested by Dr.Campeanu
 */

#include"grail_lib.h"
int main()
{
//alphabets
	char alphabets[10] =
	{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

//test  fatcors
	int start, end, repeat_time, alphabets_num;

// ask user the factors of the tests
	std::cout << std::endl << "start from n=";
	std::cin >> start;
	std::cout << std::endl;

	std::cout << "end with n=";
	std::cin >> end;
	std::cout << std::endl;

	std::cout << "invlove how many alphabets? ";
	std::cin >> alphabets_num;
	std::cout << std::endl;

	std::cout << "generate how many samples for each n? :";
	std::cin >> repeat_time;
	std::cout << std::endl;

	std::cout << "Tests begin:" << std::endl;
	std::cout << "n=" << start << " to " << end
			<< " ,each n will be tested with " << repeat_time << " samples"
			<< std::endl;
	std::cout << "using alphabets: {";
	for (int a = 0; a < alphabets_num; a++)
		std::cout << alphabets[a] << " ";
	std::cout << " }" << std::endl;

	std::cout << "This test consider 0 as start and last state as final"
			<< std::endl;

//records
	array<array<int> *> half_l; //for l=n/2
	array<array<int> *> l; //for l=n

	for (int a = start; a <= end; a++)
	{

		array<int> * head = new array<int>();
		half_l += head;

		array<int> * head2 = new array<int>();
		l += head2;

	}

	int valid = 0;

//loop 1
	for (int n = start - 1; n < end * 2; n++) //BECASUE states number changes
	{
		std::cout << end * 2 - n << "more group need to test" << std::endl;

//loop2
		for (int a = 0; a < repeat_time; a++)
		{
//generate a dfa sample
			fm<char> dfa;

//construct edges between each pair of nodes
			for (int i = 0; i < n; i++) //start
			{
				for (int j = 0; j < alphabets_num; j++)
				{
					int add = rand() % n; // 1/n  possibility not add arc
					if (add)
					{
						int to = random() % n;
						inst<char> tmpInst;
						tmpInst.assign(i, alphabets[j], to);
						dfa.add_instruction(tmpInst);
					}
				}

				/*
				 for(int j=0;j<n;j++)//end
				 {
				 for(int k=0;k<alphabets_num;k++)//label
				 {
				 int add=rand()%2;
				 if(add)
				 {
				 inst<char> tmpInst;
				 tmpInst.assign(i,alphabets[k], j);
				 dfa.add_instruction(tmpInst);
				 }
				 }

				 }
				 */
			}

//set start
			state tmpst0(0);
			dfa.add_start(tmpst0);
//set final
			state tmpstf(n - 1);
			dfa.add_final(tmpstf);

//std::cout<<"orginal dfa for n="<<n<<std::endl;
//std::cout<<dfa;

// if this sample is not valid, do nothing
			dfa.reduce();
			if (dfa.number_of_final_states() == 0)
				continue;

//std::cout<<"dfa after reduce"<<dfa;

			dfa.min_by_partition();
			dfa.complete();

			int realn = dfa.number_of_states();

			if (realn < start || realn > end)
				continue;

//report the dfa
//std::cout<<"get a valid dfa with "<<realn<<"states"<<std::endl;
//std::cout<<dfa;

			valid++; //count the total valid dfa tested

//test it with l=n/2
			fcm<char> dfca;
			dfca.copyfm(dfa);
			dfca.set_max(realn / 2);

//std::cout<<"dfca:"<<std::endl<<dfca<<std::endl;

			dfca.fcmmin();
			dfca.fm<char>::complete();
			int ndfca = dfca.fm<char>::number_of_states();

//std::cout<<"min dfca:"<<std::endl<<dfca<<std::endl;
//std::cout<<"states number:"<<ndfca;

			*(half_l[realn - start]) += ndfca;

//test it with l=n
			fcm<char> dfca2;
			dfca2.copyfm(dfa);
			dfca2.set_max(realn);

//std::cout<<"dfca2:"<<std::endl<<dfca2<<std::endl;

			dfca2.fcmmin();
			dfca2.fm<char>::complete();
			ndfca = dfca2.fm<char>::number_of_states();

//std::cout<<"min dfca2:"<<std::endl<<dfca2<<std::endl;
//std::cout<<"states number:"<<ndfca;

			(*l[realn - start]) += ndfca;

		}

	}

// report

	std::cout << "valid test count: " << valid << std::endl;

	for (int a = 0; a <= end - start; a++)
	{

		std::cout << "**************   n=" << a + start << "  ***************"
				<< std::endl;

		std::cout << "@ prat a: l=n/2:" << std::endl;
		array<int> st1 = *(half_l[a]);
		int total = 0, min = 100, max = 0, count = 0;

		for (int b = 0; b < st1.size(); b++)
		{
			total += st1[b];
			count++;

			if (min > st1[b])
				min = st1[b];

			if (max < st1[b])
				max = st1[b];

		}

		std::cout << "Valid test number: " << count << std::endl;

		if (count == 0)
			continue;

		std::cout << "   average: " << (1.0f * total / count) << std::endl;
		std::cout << "min" << min << ", max" << max << std::endl;

//std::cout<<"";

//std::cout<<"   range: ["+min<<" , "<<max<<" ]"<<std::endl;

		std::cout << std::endl;

		std::cout << "@ prat b: l=n:" << std::endl;

		array<int> st2 = *(l[a]);

		total = 0, min = 100, max = 0, count = 0;

		for (int b = 0; b < st2.size(); b++)
		{
			total += st2[b];
			count++;
			if (min > st2[b])
				min = st2[b];
			if (max < st2[b])
				max = st2[b];
		}

		std::cout << "Valid test number: " << count << std::endl;

		if (count == 0)
			continue;

		std::cout << "   average: " << (1.0f * total / count) << std::endl;

		std::cout << "min" << min << ", max" << max << std::endl;

//std::cout<<"";

//std::cout<<"   range: ["+min<<" , "<<max<<" ]"<<std::endl;

//std::cout<<std::endl;

	}

}
