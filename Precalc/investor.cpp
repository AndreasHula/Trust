

#include "global.h"
#include "investor.h"
#include "memorypool.h"


Matrix initialize_ui_init(int guilt)
{
	Matrix ui_init = Zero_matrix(noa, 5);
	for(Matrix::size_type money_invested = 0; money_invested < ui_init.size1(); ++money_invested)
	{
		for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
		{
			int money_kept = 5*max_amount - 5*money_invested;
			int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6);
			int total_profit_investor = money_kept + money_returned;
			int total_profit_trustee = rbf*5*money_invested - money_returned;
			double believed_guilt = static_cast<double>(guilt);			
			ui_init(money_invested,response) = (total_profit_investor - believed_guilt*(0.1*believed_guilt+0.3) * max(total_profit_investor - total_profit_trustee, 0));
		}
	}
	
	return ui_init;
}

Matrix_vector initialize_utpi_init()
{
    Matrix_vector utpi_init(nob, Zero_matrix(noa, 5)); //utility of the trustee as perceived by the investor given a belief (either 0 = greedy, or 1 = cooperative)
	for(Matrix_vector::size_type b = 0; b < nob; ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < utpi_init[b].size1(); ++money_invested)
		{
			for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
			{
				int money_kept = 5*max_amount - 5*money_invested;
				int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6);
				int total_profit_trustee = rbf * 5*money_invested - money_returned;
				int total_profit_investor = money_kept + money_returned;
				double believed_guilt = static_cast<double>(b);
				utpi_init[b](money_invested, response) = (total_profit_trustee - believed_guilt*(0.1*believed_guilt+0.3) * max(total_profit_trustee - total_profit_investor, 0));
			}
		}
	}

	return utpi_init;
}

Matrix initialize_investor_utility(Matrix const& ui_init, Matrix_vector const& choice_likelihood)
{
	Matrix ui = Zero_matrix(noa, nob);
	for(Matrix_vector::size_type b = 0; b < choice_likelihood.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < choice_likelihood[b].size1(); ++money_invested)
		{
			double max = 0.0;
			Matrix::size_type max_index = 0;
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				ui(money_invested,b) += ui_init(money_invested,money_returned)*choice_likelihood[b](money_invested,money_returned); //expected values
			}
		}
	}
	
	return ui;
}

Matrix_vector initialize_choice_likelihood(const Matrix_vector& utpi_init)
{	
	Matrix_vector choice_likelihood(nob, Zero_matrix(noa, 5)); //describes the likelihood of the trustee to choose a certain response (how much money he returns) as perceived by the investor conditional on belief
	for(Matrix_vector::size_type b = 0; b < choice_likelihood.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < choice_likelihood[b].size1(); ++money_invested)
		{
			double sum = 0.0;
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				sum += exp(1/temperature*utpi_init[b](money_invested, money_returned));
			}
			
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				choice_likelihood[b](money_invested, money_returned) = exp(1/temperature*utpi_init[b](money_invested, money_returned))/sum;
			}
		}
	}
	
	return choice_likelihood;
}

Index_vector initialize_max_ui_index(const Matrix& ui)
{
	Index_vector max_ui_index(nob,0);
	for(Index_vector::size_type b = 0; b < nob; ++b)
	{
		double max = 0.0;
		Matrix::size_type max_index = 0;
		for(Matrix::size_type money_invested = 0; money_invested < noa; ++money_invested)
		{
			if(max < ui(money_invested, b))
			{
				max = ui(money_invested, b);
				max_index = money_invested;
			}
		}
		max_ui_index[b] = max_index;
	}
	
	return max_ui_index;
}

Matrix initialize_investor_probabilitites(const Index_vector& max_ui_index)
{
	Matrix investor_probabilities = Zero_matrix(nob, noa);
	for(Matrix::size_type b = 0; b < investor_probabilities.size1(); ++b)
	{	
		boost::numeric::ublas::matrix_row<Matrix> row(investor_probabilities, b);
		greedy_probabilities(row.begin(), row.end(), max_ui_index[b]);
	}
	
	return investor_probabilities;
}	


boost::array<int, global_time_horizon-1> custom_sort(boost::array<int, global_time_horizon-1> hist, int time)
{
	boost::array<int, global_time_horizon-1> sorted_hist;
	for(int ind=0; ind < (global_time_horizon-1); ++ind)
	{		
		sorted_hist[ind]=0;
	}

	boost::array<int, global_time_horizon-1> calc_hist;	
	for(int ind=0; ind < (global_time_horizon-1); ++ind)
	{
		calc_hist[ind]=hist[ind];
	}	

	int max_ind;
	for(int index = time; 0<=index ; --index)
	{
		for(int run =0; run <= index; ++run) //max search not a min search
		{
			max_ind =(sorted_hist[index] > calc_hist[run] ? max_ind:run);
			sorted_hist[index] = (sorted_hist[index] > calc_hist[run] ? sorted_hist[index]:calc_hist[run]);
		}
		calc_hist[max_ind]=calc_hist[index];
		max_ind=0;
	}
	
	return sorted_hist;
}

Value_Node* build_sequence(boost::array<int, global_time_horizon-1> hist, int time, Value_Node* root)
{
	Value_Node* node = root; 
	Value_Node* old_node;
	
	for(int traverse=0; traverse <= time ; ++traverse)
	{
		old_node = node;
		node = old_node->get_history_child(hist[traverse]);
		if(!node)
		{
			node = new Value_Node(global_time_horizon-1-traverse);
			old_node->set_history_child(node, hist[traverse]);
		}
		
	}

	return node;
}

int mini(int no_one, int no_two)
{
	int min = ( no_one < no_two ? no_one:no_two);
	return min;
}

double augmented_ui(const int action , boost::array<Matrix, nob> ui_init_system, boost::array<int, global_time_horizon-1> hist,  boost::array<double, nob> probabilities, Value_Node* current_node, Value_Node* root, int belief, int time, const Matrix_vector& investor_choice_likelihood, const int y)
{
	double action_value =0.0;
	boost::array<double,noa> ui_aug;
	int act;
	boost::array<int ,global_time_horizon-1> temp_hist;
	for(int response =0; response < (nor(action)); ++response)
	{
		act = (action==0 ? 0:((action-1)*noa + 1 +response));
		if(time < (global_time_horizon-2) && y >0)
		{
			for(int tu=0; tu <= time; ++tu)
			{
				temp_hist[tu]=hist[tu]; 
			}		
			temp_hist[time+1]=act;
			temp_hist = custom_sort(temp_hist,time+1);				
			Value_Node* node = build_sequence(temp_hist, time+1, root);		
			if(!node)
			{
				cout << "about to crash" << endl;
				assert(false);
			}
			int outlook = y-1;
			ui_aug[response] = ui_init_system[belief](action,response)+(node->get_expectation(belief, outlook));
		}
		else
		{
			ui_aug[response] = ui_init_system[belief](action,response);
		}

		for(int beliefs=0; beliefs < nob ; ++beliefs)
		{
			action_value += ui_aug[response]*investor_choice_likelihood[beliefs](action, response)*probabilities[beliefs]; 
		}
		
	}

	return action_value;
}

Value_Node* level_0_investor( int const& time_horizon
							, boost::array<boost::array<double,nob>,3> const& investor_belief_parameters						
							, MEMORY_POOL<Value_Node>& mempool)
{

	ofstream ofs ("saved_0_3_investor_high_large.bin", ios::out | ios::binary);
	Value_Node* root = new Value_Node(global_time_horizon); 	
	Value_Node* current_node;
	Matrix_vector utpi_init = initialize_utpi_init();
	Matrix_vector investor_choice_likelihood = initialize_choice_likelihood(utpi_init);	
	boost::array<Matrix, nob> ui_init_system;
	
 	for(int system=0; system < nob; ++system)
	{ 
		ui_init_system[system] = initialize_ui_init(system);
 	}	
	
 	boost::array<int, global_time_horizon-1> current_hist; 
	for(int t = 0; t < (global_time_horizon-1); ++t)
	{
		current_hist[t] = 0;
	}	
	
	int last_action;
	int last_response;
	
	boost::array<double,nob> zero_beliefs;
	boost::array<double,noa> Qvalue;

	for(int run = 0; run < nob; ++run)
	{
		zero_beliefs[run] = investor_belief_parameters[2][run];
	}
	
	boost::array<double, nob> probabilities;
	
	boost::array<boost::array<int, global_time_horizon>,ActionResponsePairs> path_numbers;
	boost::array<boost::array<int, global_time_horizon>,ActionResponsePairs+1> correction_factors;	
	int count=0;	
	int ncount=0; 
	path_numbers[0][0]=ActionResponsePairs;
	for(int act=0; act<ActionResponsePairs; ++act)
	{
		correction_factors[act][0] = -act;
	}	
	
	for(int act=1; act<ActionResponsePairs; ++act)
	{
		path_numbers[act][0]= path_numbers[0][0] +correction_factors[act][0];
		count +=path_numbers[act][0];	
		ncount -= path_numbers[act-1][0];
		correction_factors[act][1] = ncount;	
	}
	
	if(global_time_horizon>1)
	{
	path_numbers[0][1]= path_numbers[0][0]+ count;
	correction_factors[0][1]=0;
	}

	
	for(int t =1; t < (global_time_horizon-1); ++t)
	{	
		count=0;
		ncount=0;
		for(int act=1; act<ActionResponsePairs; ++act)
		{
			path_numbers[act][t]= path_numbers[0][t] +correction_factors[act][t];
			count +=path_numbers[act][t];	
			ncount -= path_numbers[act-1][t];
			correction_factors[act][t+1] = ncount;
		}
		path_numbers[0][t+1] = path_numbers[0][t]+count;
		correction_factors[0][t+1]=0;	
	}
	for(int t = global_time_horizon-2; 0 <= t; --t) 
	{
		for(int paths = 1; paths <= path_numbers[0][t]; ++paths)
		{
			for(int j = t; 0 < j; --j)
			{
				if(current_hist[j]%ActionResponsePairs == 0 && paths >1) 
				{
					current_hist[j-1]=current_hist[j-1]+1;
					
					for(int o=j; o <= t; ++o)
					{
						current_hist[o]=current_hist[j-1];
					}
				}
				else
				{
					break;
				}
			}
			
			current_node = build_sequence(current_hist,t, root); 
			
			for(int run =0; run <nob; ++run)
			{
				zero_beliefs[run]=investor_belief_parameters[2][run];
			}			
			
			for(int belief=0; belief < nob; ++belief)
			{
				for(int time =0; time <= t; ++time)
				{
					int act=current_hist[time];
					if(act==0)
					{
						last_action = 0;
						last_response =0;
					}
					else
					{
						last_action = ((int) (act-1)/(noa) +1); 
						last_response =  ((act-1) % (noa));
						zero_beliefs[belief] +=	 investor_choice_likelihood[belief](last_action, last_response); 						
					}

				}
			}			

			probabilities = Dirichlet_Multinomial_probabilities(zero_beliefs);							
			for(int y=0; y < (global_time_horizon-t-1);++y)
			{
			
				for(int belief=0; belief < nob; ++belief) 
				{			
					double sum =0.0;
					double value=0.0;
					double expectation =0.0;
					for(int action= 0; action < noa; ++ action)	
					{
						Qvalue[action]= augmented_ui(action, ui_init_system, current_hist, probabilities, current_node, root, belief, t, investor_choice_likelihood, y); 				
						sum +=exp(1/temperature*Qvalue[action]);
					}								

					for(int action= 0; action < noa; ++ action)	
					{	
						value = exp(1/temperature*Qvalue[action])/sum;	
						expectation += Qvalue[action]*value;
						current_node->set_payoff(belief,action, value,y); 
					}

					current_node->set_expectation(belief, expectation,y); 

				}		
			}
			current_hist[t] += 1; 
		}
		
		for(int s= 0; s <= global_time_horizon-2; ++s)
		{
			current_hist[s]=0; 
		}
		
	}	

	current_node = root;

	int tick=0;
	long long unsigned int tock =0;
	probabilities = Dirichlet_Multinomial_probabilities(investor_belief_parameters[2]);		

	for(int y=0; y < (global_time_horizon); ++y)
	{	
		for(int belief=0; belief < nob; ++belief) 
		{	
			double sum =0.0;
			double value=0.0;
			double expectation =0.0;
			for(int action= 0; action < noa; ++ action)	
			{
				Qvalue[action]= augmented_ui(action,ui_init_system, current_hist ,probabilities, root, root, belief, -1, investor_choice_likelihood, y); 
				sum +=exp(1/temperature*Qvalue[action]);
			}								
			
			for(int action= 0; action < noa; ++ action)	
			{	
				value = exp(1/temperature*Qvalue[action])/sum;
				ofs.write( reinterpret_cast<char*>( &value ), sizeof value );
				expectation += Qvalue[action]*value;
				root->set_payoff(belief,action, value,y); 
				++tock;
			}
					
		}		
	}	
	++tick;
	double store =0.0;
	boost::array<boost::array<double,noa>,nob> temporary_payoffs;
		
	for(int t = 0; t <= global_time_horizon-2; ++t) 
	{	
		for(int paths = 1; paths <= path_numbers[0][t]; ++paths)
		{	
			for(int j = t; 0 < j; --j)
			{

				if(current_hist[j]%ActionResponsePairs == 0 && paths >1) 
				{
					current_hist[j-1]=current_hist[j-1]+1;
					
					for(int o=j; o <= t; ++o)
					{
						current_hist[o]=current_hist[j-1];
					}
				}
				else
				{
					break;
				}
			}
			current_node = build_sequence(current_hist,t, root);	
			for(int y=0; y < (global_time_horizon-t-1);++y)
			{					
				for(int belief=0; belief < nob; ++belief) 
				{				
					for(int action= 0; action < noa; ++ action)	
					{	
						store = current_node->get_payoff(belief,action, y);
						ofs.write( reinterpret_cast<char*>( &store ), sizeof store );
						++tock;
					}
					
				}		
			}
				
			++tick;			
			current_hist[t] += 1; 
		}
			
		for(int s= 0; s <= global_time_horizon-2; ++s)
		{
			current_hist[s]=0; 
		}
	}


	ofs.close();
	
	return root;
}
