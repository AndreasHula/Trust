#ifndef GLOBAL_H_INCLUDE_GUARD
#define GLOBAL_H_INCLUDE_GUARD

#include <ostream>
#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <fstream>

#include <math.h>
#include <time.h>
#include <boost/bind.hpp>
#include <deque>

#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random/gamma_distribution.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/math/special_functions/gamma.hpp>

#include "RandomSingleton.h"

#include "memorypool.h"



using namespace std;

typedef boost::numeric::ublas::matrix<double> Matrix;
typedef boost::numeric::ublas::matrix_row<const Matrix> Matrix_row;
typedef boost::numeric::ublas::matrix_column<const Matrix> Matrix_column;
typedef boost::numeric::ublas::zero_matrix<double> Zero_matrix;

typedef std::vector<Matrix> Matrix_vector;
typedef std::vector<Matrix::size_type> Index_vector;

const int max_amount = 4; // how much the investor can offer up (and is thus at risk)
const int global_time_horizon = 10; //number of exchanges between investor and trustee
const int nob = 3; //number of believes 
const Matrix::size_type noa = max_amount + 1; //number of actions 
const int ActionResponsePairs = 21;


//game specifier
const int rbf =3; // risk benefit factor (the number that the offered amount is multiplied by)
const double temperature =3.0; //softmax temperature parameter
//simulation specifier
const unsigned int simulation_iterations =2500; //how often the iterated game is simulated 
const double exploration_constant = 25.0; //bonus in exploration term
const double eps =0.5;



void initialize_globals(string const & filename);
double generate_uniform_distributed_value();
double generate_beta_distributed_value(double alpha, double beta);
double gamma_function(double z);
int pmax(int value);
boost::array<double,nob> generate_dirichlet_distributed_value(boost::array<double,nob> belief_values);
boost::array<double,nob> Dirichlet_Multinomial_probabilities(boost::array<double,nob> belief_values);
boost::array<int, global_time_horizon-1> custom_sort(boost::array<int, global_time_horizon-1> hist, int time);

void print_matrix(Matrix const & m);
std::vector<double> greedy_probabilities(unsigned int preferred_action, unsigned int actions);

unsigned int softmax(Matrix_row const& probabilities, int const& Index);
unsigned int softmax(Matrix_column const& probabilities, int const& Index);

template <class T> //for boost array
int softmax(const T& probabilities, int const& Ind)
{
	double draw = generate_uniform_distributed_value();
	int choice = 0;

	std::vector<double> new_prob (probabilities.size(), 0.0);	
	//include normalisation loop 
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
		if(choice >= probabilities.size())
		{
			cout << "Error in softmax: choice: " << choice << " size: " << probabilities.size() << "Index" << Ind << endl;
			cout << "sums to" << norm << endl;			
			for(int i =0; i < probabilities.size(); ++i)
			{
				cout << probabilities[i] << endl;
			}
			for(int i =0; i < probabilities.size(); ++i)
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



inline unsigned int nor(unsigned int action)
{
	return (action == 0 ? 1 : noa);
}

inline int minimalize(double value, boost::array<double,noa> reference)
{
	int min_int=0;
	double distance =40.0;
	for(int i=0; i <noa; ++i)
	{
		if(abs(value - reference[i]) < distance )
		{
			min_int = i;
			distance = abs(value - reference[i]);
		}
	}

	return min_int;
}


inline int math_round(double val)
{
	return static_cast<int>(val + 0.5);
}

template<class T>
void print_vector(T const& v)
{
	for(unsigned int i = 0; i < v.size(); ++i)
	{
		cout << i << ": " << v[i] << "\n";
	}
	cout << endl;
}

template <class T>
void greedy_probabilities(T begin, T end, unsigned int preferred_action)
{
	unsigned int actions = distance(begin, end);
	
	if(actions > 1)
	{
		for(unsigned int i = 0; i < actions; ++i, ++begin)
		{
			*begin = (i == preferred_action ? 1-eps : eps/(actions-1));
		}
	}
	else
	{
		*begin = 1.0;
	}
}

class True_node : public MEMORY_OBJECT
{
	public:
		True_node():
				  m_free_child(0) 
				 , m_expectation(0.0)
				 , m_rolled_out(false)	
		{
			for(int i = 0; i < noa; ++i)
			{
				m_children[i] =NULL;	
				m_payoff[i] = 0.0;
				m_action_count[i] = 0;
			}
		}

		
		True_node* get_child(int action) const
		{
			return m_children[action];
		}
		
		void set_exp_payoffs(int action, double value, int trustee_belief)
		{
			m_exp_payoffs[trustee_belief][action] = value;
		}
		
		boost::array<boost::array<double, noa>, nob> const& get_exp_payoffs() const
		{
			return m_exp_payoffs;
		}		
		
		int get_next_free_child() const
		{
			return m_free_child;
		}
		
		void set_child(int action, True_node* child)
		{
			assert(!m_children[action]);
			
			m_children[action] = child;
			
		    while(m_free_child < noa && m_action_count[m_free_child])
			{
				++m_free_child;
			}
		}
		
		double get_payoff(int action) const
		{
			return m_payoff[action];
		}
		
		void set_payoff(int action, double value)
		{
			m_payoff[action] = value;
		}
		
		void inc_action_count(int action)
		{
			++m_action_count[action];
			
			while(m_free_child < noa && m_action_count[m_free_child])
			{
				++m_free_child;
			}
		}
		
		unsigned int get_action_count(int action)
		{
			return m_action_count[action];
		}
		
		void rollout_done()
		{
			m_rolled_out = true;
		}
		
		bool is_rolled_out() const
		{
			return m_rolled_out;
		}
		
		void set_expectation(double value)
		{		
			m_expectation = value;
		}
		
		double get_expectation()
		{
			return m_expectation;
		}
		
		int get_next_exploration(int current_count) //expects that all children have been constructed!
		{
			boost::array<double,noa> exploration; 
			double sum =0.0;

				for(int action = 0; action < noa; ++action)
				{
					exploration[action] = exp(1.0/temperature*(m_payoff[action] + exploration_constant*sqrt(log(static_cast<double>(current_count))/(m_action_count[action])))); 
					sum += exploration[action];
				}

				for(int action = 0; action < noa; ++action)
				{
					exploration[action] = exploration[action]/sum;
				}

			int choice =softmax(exploration, 50);
			
			return choice;
		}


		~True_node()
		{
	
			for(int i=0; i <noa; ++i)
			{
				if(!(m_children[i]==NULL))
				{
					delete m_children[i];
				}
			}

		}

		
	private:
		boost::array<double, noa> m_payoff; 
		boost::array<True_node*,noa> m_children;
		boost::array<unsigned int, noa> m_action_count;
		boost::array<boost::array<double,noa>,nob> m_exp_payoffs;		
		int m_free_child;
		bool m_rolled_out;
		double m_expectation;
};

class Value_Node : public MEMORY_OBJECT
{
	public:
		Value_Node(int horizon):
		m_horizon(horizon)
		{
			for(int b=0; b<nob;++b)
			{		
					m_expectation[b]=std::vector<double>(m_horizon+1,0.0);
			}
			for(int b=0; b<nob;++b)
			{
						m_payoff[b] = Zero_matrix(m_horizon+1,noa);
			}
			for(unsigned int i = 0; i < ActionResponsePairs; ++i)
			{
				m_history_children[i]=NULL;
			}
		}	

		double get_payoff(int belief, int action, int time) const
		{
			return m_payoff[belief](time,action);
		}
		
		void set_payoff(int belief, int action, double value, int time)
		{
			m_payoff[belief](time,action) = value;
		}		
		void set_expectation(int belief, double value, int time)
		{
			m_expectation[belief][time] = value;
		}
		
		double get_expectation(int belief,int time)
		{
			return m_expectation[belief][time];
		}
		void set_history_child(Value_Node* child, int act)
		{
			m_history_children[act]=child;
		}
		
		Value_Node* get_history_child(int act)
		{
			return m_history_children[act];
		}

	private:
		int const& m_horizon;
		boost::array<Matrix,nob> m_payoff; 
		boost::array<Value_Node*, ActionResponsePairs> m_history_children;	
		boost::array<std::vector<double>,nob> m_expectation;		
};

#endif