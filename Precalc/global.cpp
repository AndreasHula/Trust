#include "global.h"
#include "memorypool.h"



double generate_uniform_distributed_value()
{
	boost::random::uniform_01<double> d;

	return d(RandomSingleton::Instance());
}

double generate_beta_distributed_value(double alpha, double beta)
{
	boost::random::gamma_distribution<double> d1(alpha, 1.0);
    boost::random::gamma_distribution<double> d2(beta, 1.0);
	
	double d1v = d1(RandomSingleton::Instance());
	double d2v = d2(RandomSingleton::Instance());
	
	return d1v/(d1v + d2v);
}

boost::array<double,nob> generate_dirichlet_distributed_value(boost::array<double,nob> belief_vector)
{
	boost::array<double,nob> dirichlet_values;
	boost::array<double,nob> gamma_samples;
	
	double sum = 0.0;
	for(unsigned int belief_values =0; belief_values < nob; ++belief_values)
	{
		boost::random::gamma_distribution<double> gamrand(belief_vector[belief_values], 1.0);
		gamma_samples[belief_values] = gamrand(RandomSingleton::Instance());
		sum += gamma_samples[belief_values];
	}
	
	for(unsigned int belief_values =0; belief_values < nob; ++belief_values)
	{
		dirichlet_values[belief_values] = gamma_samples[belief_values]/sum;
	}

	return dirichlet_values;
}


double gamma_function(double z)
{
	return	boost::math::tgamma(z);
}


boost::array<double,nob> Dirichlet_Multinomial_probabilities(boost::array<double,nob> belief_values) //Calculate probabilities of a single multinomial sample with Dirichlet prior 
{
	boost::array<double,nob> result;
	double sum =0.0;
	for(int running_belief_index=0; running_belief_index < nob; ++running_belief_index)
	{
		result[running_belief_index] = gamma_function((belief_values[running_belief_index]+1.0))/gamma_function(belief_values[running_belief_index]);	
		sum += belief_values[running_belief_index];
	}

	for(int belief_index=0; belief_index < nob; ++belief_index)
	{		
		result[belief_index] = gamma_function( sum)/gamma_function((sum+1.0))*result[belief_index];
	}

	return result;
}

int pmax(int value)
{
	int maxp = (value < 1 ? 0: value);
	
	return maxp;
}

void print_matrix(Matrix const & m)
{
	for(unsigned int i = 0; i < m.size1(); ++i)
	{
		cout << i << ": "; 
		for(unsigned int j = 0; j < m.size2(); ++j)
		{
			cout << m(i,j) << "\t";
		}
		cout << "\n";
	}
	cout << endl;
}

template <class T> //for boost array
int softhelp( const T& probabilities, int const& Index)
{
	double draw = generate_uniform_distributed_value();
	int choice = 0;

	std::vector<double> new_prob (probabilities.size(), 0.0);
	double norm= 0.0;
	for(int i=0; i < probabilities.size() ; ++i)
	{
		norm += probabilities[i];
	}
	for(int i=0; i < probabilities.size() ; ++i)
	{
		new_prob[i] = probabilities[i]/norm;
	}	
	norm= 0.0;
	for(int i=0; i < probabilities.size() ; ++i)
	{
		norm += new_prob[i];
	}	
	
	double sum = new_prob[0];		
	while(sum < draw)
	{
		++choice;
		if(choice >= distance(probabilities.begin(), probabilities.end()))
		{
			cout << "Error: choice: " << choice << " size: " << distance(probabilities.begin(), probabilities.end())<< "Index" << Index << endl;
			cout << "sums to" << norm << endl;			
			for(int i =0; i < distance(probabilities.begin(), probabilities.end()); ++i)
			{
				cout << probabilities[i] << endl;
			}
			for(int i =0; i < distance(probabilities.begin(), probabilities.end()); ++i)
			{
				cout << new_prob[i] << endl;
			}			
			cout << "Draw" << draw << endl;
			assert(false);			
		}
		sum += new_prob[choice];
	}
	
	return choice;
}

unsigned int softmax(Matrix_row const& probabilities, int const& Index)
{
	return softhelp(probabilities, Index);
}

unsigned int softmax(Matrix_column const& probabilities, int const& Index)
{
	return softhelp(probabilities, Index);
}


std::vector<double> greedy_probabilities(unsigned int preferred_action, unsigned int actions)
{
	if(actions > 1)
	{
		std::vector<double> greedy_probabilities(actions, eps/(actions-1));
		
		greedy_probabilities[preferred_action] = 1-eps;
		
		return greedy_probabilities;
	}
	else
	{
		return std::vector<double>(1, 1.0);
	}
}
