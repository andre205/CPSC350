#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdlib.h> 

using namespace std;

int main(int argc, char** argv)
{
	bool running = true;
	string inputfilename = argv[1];
	while(running)
	{
		int string_count = 0;
		int sum_length = 0;
		float mean_length = 0;
		int sum_a = 0;
		int sum_c = 0;
		int sum_t = 0;
		int sum_g = 0;
		float variance = 0;
		float st_dev = 0;
		float prob_a = 0;
		float prob_c = 0;
		float prob_t = 0;
		float prob_g = 0;
		int bigram_total = 0;
		int bigram_aa = 0;
		int bigram_ac = 0;
		int bigram_at = 0;
		int bigram_ag = 0;
		int bigram_ca = 0;
		int bigram_cc = 0;
		int bigram_ct = 0;
		int bigram_cg = 0;
		int bigram_ta = 0;
		int bigram_tc = 0;
		int bigram_tt = 0;
		int bigram_tg = 0;
		int bigram_ga = 0;
		int bigram_gc = 0;
		int bigram_gt = 0;
		int bigram_gg = 0;
		float aa_prob = 0;
		float ac_prob = 0;
		float at_prob = 0;
		float ag_prob = 0;
		float ca_prob = 0;
		float cc_prob = 0;
		float ct_prob = 0;
		float cg_prob = 0;
		float ta_prob = 0;
		float tc_prob = 0;
		float tt_prob = 0;
		float tg_prob = 0;
		float ga_prob = 0;
		float gc_prob = 0;
		float gt_prob = 0;
		float gg_prob = 0;

		//INPUT
		ifstream inputfile;
		inputfile.open(inputfilename.c_str());
		string line;
		if (inputfile.is_open())
		{
		    while ( getline (inputfile,line) )
		    {
		    	transform(line.begin(), line.end(), line.begin(), ::toupper);

		    	//ADD LENGTH TO SUM
		    	sum_length = sum_length + line.size();

		    	//COUNT NUCLEOTIDES
		    	for (int i = 0; i < line.size(); ++i)
		    	{
		    		if(line[i] == 'A') ++sum_a;
		    		if(line[i] == 'C') ++sum_c;
		    		if(line[i] == 'T') ++sum_t;
		    		if(line[i] == 'G') ++sum_g;
		    	}

		    	//KEEP TRACK OF NUMBER OF STRINGS
		    	string_count++;
		    }

		    inputfile.close();

			//CALCULATE MEAN
		    mean_length = (float)sum_length/(float)string_count;

		    //REOPEN FILE TO CALCULATE VARIANCE AND COUNT BIGRAMS
		    inputfile.open(inputfilename.c_str());
		    while ( getline (inputfile,line) )
		    {	
		    	transform(line.begin(), line.end(), line.begin(), ::toupper);

		    	//VARIANCE
		    	float temp = 0;
		    	temp = mean_length - line.size();
		    	temp = temp * temp;
		    	variance = variance + temp;

		    	//COUNT BIGRAMS
		    	string bi;
		    	for (int i = 0; i < line.size()-1; ++i)
		    	{
		    		bi = "";
		    		bi.push_back(line[i]);
		    		bi.push_back(line[i+1]);

		    		if (bi == "AA") ++bigram_aa;
		    		if (bi == "AC") ++bigram_ac;
		    		if (bi == "AT") ++bigram_at;
		    		if (bi == "AG") ++bigram_ag;
		    		if (bi == "CA") ++bigram_ca;
		    		if (bi == "CC") ++bigram_cc;
		    		if (bi == "CT") ++bigram_ct;
		    		if (bi == "CG") ++bigram_cg;
		    		if (bi == "TA") ++bigram_ta;
		    		if (bi == "TC") ++bigram_tc;
		    		if (bi == "TT") ++bigram_tt;
		    		if (bi == "TG") ++bigram_tg;	    		
		    		if (bi == "GA") ++bigram_ga;
		    		if (bi == "GC") ++bigram_gc;
		    		if (bi == "GT") ++bigram_gt;
		    		if (bi == "GG") ++bigram_gg;
		    	}
		    }

			inputfile.close();		
		}

		//CALCULATIONS
		bigram_total = bigram_aa + bigram_ac + bigram_at + bigram_ag + bigram_ca + bigram_cc + bigram_ct + bigram_cg + bigram_ta + bigram_tc + bigram_tt + bigram_tg + bigram_ga + bigram_gc + bigram_gt + bigram_gg;
		aa_prob = (float)bigram_aa/(float)bigram_total * 100;
		ac_prob = (float)bigram_ac/(float)bigram_total * 100;
		at_prob = (float)bigram_at/(float)bigram_total * 100;
		ag_prob = (float)bigram_ag/(float)bigram_total * 100;
		ca_prob = (float)bigram_ca/(float)bigram_total * 100;
		cc_prob = (float)bigram_cc/(float)bigram_total * 100;
		ct_prob = (float)bigram_ct/(float)bigram_total * 100;
		cg_prob = (float)bigram_cg/(float)bigram_total * 100;
		ta_prob = (float)bigram_ta/(float)bigram_total * 100;
		tc_prob = (float)bigram_tc/(float)bigram_total * 100;
		tt_prob = (float)bigram_tt/(float)bigram_total * 100;
		tg_prob = (float)bigram_tg/(float)bigram_total * 100;
		ga_prob = (float)bigram_ga/(float)bigram_total * 100;
		gc_prob = (float)bigram_gc/(float)bigram_total * 100;
		gt_prob = (float)bigram_gt/(float)bigram_total * 100;
		gg_prob = (float)bigram_gg/(float)bigram_total * 100;

	    prob_a = sum_a/(float)sum_length;
	    prob_c = sum_c/(float)sum_length;
		prob_t = sum_t/(float)sum_length;
		prob_g = sum_g/(float)sum_length;

	    variance = variance/string_count;
	    st_dev = sqrt(variance);


	    //OUTPUT
		ofstream outputfile;
		//ALWAYS APPEND
		outputfile.open ("tylerandrews.out", std::ios_base::app);
		outputfile << "Tyler Andrews \nID: 2263083\n\n";
		outputfile << "Results from  " << inputfilename << '\n';
	    outputfile << "Length Sum: " << sum_length << '\n';
	    outputfile << "Length Mean: " << mean_length << "\n";
	    outputfile << "Length Variance: " << variance << '\n';
	    outputfile << "Length Standard Deviation: " << st_dev << '\n';
	    outputfile << "Nucleotide Probabilities" << '\n';
	    outputfile << "A: " << prob_a*100 << "%" <<'\n';
	    outputfile << "C: " << prob_c*100 << "%" <<'\n';
	    outputfile << "T: " << prob_t*100 << "%" <<'\n';
	    outputfile << "G: " << prob_g*100 << "%" <<'\n';
	    outputfile << "Bigram Probabilities" << '\n';
	    outputfile << "AA: " << aa_prob << "%\nAC: " << ac_prob << "%\nAT: " << at_prob << "%\nAG: " << ag_prob << "%\n";
	    outputfile << "CA: " << ca_prob << "%\nCC: " << cc_prob << "%\nCT: " << ct_prob << "%\nCG: " << cg_prob << "%\n";
		outputfile << "TA: " << ta_prob << "%\nTC: " << tc_prob << "%\nTT: " << tt_prob << "%\nTG: " << tg_prob << "%\n";
	    outputfile << "GA: " << ga_prob << "%\nGC: " << gc_prob << "%\nGT: " << gt_prob << "%\nGG: " << gg_prob << "%\n\n";

	    //1000 STRINGS
	    double c;
	    int randlength;
	    double r1;
	    double r2;
	    double r3;

	    for (int i = 0; i < 1000; ++i)
	    {
	    	c = 0;
	    	//RANDOM NUMBER BETWEEN 0 AND 1
	    	r1 = (double)rand() / (double)(RAND_MAX);
	    	r2 = (double)rand() / (double)(RAND_MAX);

	    	//cout << "R1: " << r1 << '\n';
			//cout << "R2: " << r2 << '\n';

	    	//FORMULA USED TO DETERMINE STRING LENGTH
			c = sqrt((-2)*log(r1)) * cos(2*M_PI*r2);
			randlength = st_dev * c + mean_length;

			//cout << "C: " << c << '\n';
			//cout << "String length: " << randlength << '\n';

			//Account for negative lengths (unlikely but just in case of small input strings)
			if (randlength < 1) randlength = 0;

			//RANDOM NUMBER BETWEEN 0 AND 1 GENERATED
			//NUCLEOTIDE PROBABILITES FROM INPUT STRING USED
			//TO DETERMINE WHICH CHAR IS GENERATED AND APPENDED TO THE STRING
			string randstring = "";
			for (int j = 0; j < randlength; ++j)
			{
				r3 = (double)rand() / (double)(RAND_MAX);
				if (r3 < prob_a) randstring.push_back('A');
				else if (r3 < prob_a + prob_c) randstring.push_back('C');
				else if (r3 < prob_a + prob_c + prob_t) randstring.push_back('T');
				else randstring.push_back('G');	
			} 
			outputfile << randstring << '\n';
	    }

	    outputfile << "--------------------------" << '\n';
	    outputfile << "END OF LIST" << '\n';
	    outputfile << "--------------------------" << "\n\n\n";

		outputfile.close();

		//PROCESS ANOTHER LIST (change inputfilename)
		string response = "";
		cout << "Would you like to process another list? (Type YES or NO): ";
		cin >> response;
		transform(response.begin(), response.end(), response.begin(), ::toupper);
		if (response == "YES")
		{
			cout << "Please enter a file name: ";
			cin >> response;
			inputfilename = response;
		}
		else if (response == "NO")
		{
			cout << "Exiting application\n";
			running = false;
		}
		else
		{
			cout << "Invalid response - exiting application \n";
			running = false;
		}

	}
	return 0;
}

