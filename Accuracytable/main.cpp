#include "global.h"
#include "memorypool.h"


// Multiround Trustgame estimation by A.Hula, with eternal gratefulness to A.Morhammer 
// Current Version, 9.September.2014


Matrix initialize_trustee_utility(int trustee_guilt)
{
	Matrix ut = Zero_matrix(noa, 5);
	for(Matrix::size_type money_invested = 0; money_invested < ut.size1(); ++money_invested)
	{
		for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
		{
			int money_kept = 5*max_amount - 5*money_invested;
			int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6.0);
			int total_profit_investor = money_kept + money_returned;
			double believed_guilt = static_cast<double>(trustee_guilt);
			int total_profit_trustee = rbf*5*money_invested - money_returned;
			
			ut(money_invested,response) = (total_profit_trustee -  believed_guilt*(0.1*believed_guilt+0.3)  * max(total_profit_trustee - total_profit_investor, 0));			
		}
	}
	
	return ut;
}

Matrix initialize_trustee_probabilities(Matrix const& ut)
{
	Matrix trustee_probabilities = Zero_matrix(noa, 5);
	
	for(Matrix::size_type money_invested = 0; money_invested < trustee_probabilities.size1(); ++money_invested)
	{
		double sum = 0.0;
		for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
		{
			sum += exp(1.0/temperature*ut(money_invested, money_returned));
		}
		
		for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
		{
			trustee_probabilities(money_invested, money_returned) = exp(1.0/temperature*ut(money_invested, money_returned))/sum;
		}
	}
	
	return trustee_probabilities;
}

Matrix initialize_trustee_rollout_likelihood(Matrix const& trustee_probabilities, Index_vector const& max_ut_index)
{
	Matrix trustee_rollout_likelihood = Zero_matrix(noa, 5);
	for(Matrix::size_type money_invested = 0; money_invested < trustee_rollout_likelihood.size1(); ++money_invested)
	{	
		boost::numeric::ublas::matrix_row<Matrix> row(trustee_rollout_likelihood, money_invested);
		greedy_probabilities(row.begin(), row.begin()+nor(money_invested), max_ut_index[money_invested]);
	}
	
	return trustee_rollout_likelihood;
}

Index_vector initialize_max_ut_index(const Matrix& ut)
{
	Index_vector ut_max(noa, 0); //Matrix containing the max utility responses of the trustee to a given offer
	for(Index_vector::size_type money_invested = 0; money_invested < ut_max.size(); ++money_invested)
	{
		double max = 0.0;
		Matrix::size_type max_index = 0;
		for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
		{
			if(max < ut(money_invested, money_returned))
			{
				max = ut(money_invested, money_returned);
				max_index = money_returned;
			}
		}
		ut_max[money_invested] = max_index;
	}
	
	return ut_max;
}

Matrix initialize_offer_utility(Matrix_vector const& investor_choice_likelihood)
{
	Matrix_vector uipt_init(nob, Zero_matrix(noa, 5)); //utility of the investor as perceived by the trustee given a belief 
	for(Matrix_vector::size_type b = 0; b < uipt_init.size(); ++b)
	{
		for(Matrix::size_type money_invested = 0; money_invested < uipt_init[b].size1(); ++money_invested)
		{
			for(Matrix::size_type response = 0; response < nor(money_invested); ++response)
			{
				int money_kept = 5*max_amount - 5*money_invested;
				int money_returned = ceil(static_cast<double>(rbf*5*money_invested*response)/6);
				int total_profit_trustee = rbf *5* money_invested - money_returned;
				int total_profit_investor = money_kept + money_returned;
				double believed_guilt = static_cast<double>(b);
				uipt_init[b](money_invested, response) = (total_profit_investor -  believed_guilt*(0.1*believed_guilt+0.3) * max(total_profit_investor - total_profit_trustee, 0));
			}
		}
	}
	
	Matrix offer_utility = Zero_matrix(noa, nob);
	for(Matrix::size_type investor_guilt = 0; investor_guilt < nob; ++investor_guilt)
	{
		for(Matrix::size_type money_invested = 0; money_invested < noa; ++money_invested)
		{
			for(int trustee_guilt = 0; trustee_guilt < offer_utility.size2(); ++trustee_guilt)
			{
				for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
				{
					offer_utility(money_invested,investor_guilt) += 1.0/(nob) *
					                                                uipt_init[investor_guilt](money_invested,money_returned) *
																	investor_choice_likelihood[trustee_guilt](money_invested,money_returned);
				}
			}
			
		}
	}
	
	return offer_utility;
}

Matrix initialize_trustee_choice_likelihood(Matrix const& offer_utility)
{
	Matrix trustee_choice_likelihood = Zero_matrix(noa, nob);
	for(Matrix::size_type investor_guilt = 0; investor_guilt < trustee_choice_likelihood.size2(); ++investor_guilt)
	{
		double sum = 0.0;
		for(Matrix::size_type money_invested = 0; money_invested < trustee_choice_likelihood.size1(); ++money_invested)
		{
			sum += exp(1.0/temperature*offer_utility(money_invested, investor_guilt));
		}
		
		for(Matrix::size_type money_invested = 0; money_invested < trustee_choice_likelihood.size1(); ++money_invested)
		{
			trustee_choice_likelihood(money_invested, investor_guilt) = exp(1.0/temperature*offer_utility(money_invested, investor_guilt))/sum;
		}
	}
	
	return trustee_choice_likelihood;
}


boost::array<int, global_time_horizon> custom_sort(boost::array<int, global_time_horizon> hist, int time)
{
	boost::array<int, global_time_horizon> sorted_hist;
	for(int ind=0; ind < global_time_horizon; ++ind)
	{	
		sorted_hist[ind]=0;
	}

	boost::array<int, global_time_horizon> calc_hist;	
	for(int ind=0; ind < global_time_horizon; ++ind)
	{
		calc_hist[ind]=hist[ind];
	}	

	int max_ind;
	for(int index = time; 0<=index ; --index)
	{
		for(int run =0; run <= index; ++run) 
		{
			max_ind =(sorted_hist[index] > calc_hist[run] ? max_ind:run);
			sorted_hist[index] = (sorted_hist[index] > calc_hist[run] ? sorted_hist[index]:calc_hist[run]);
		}
		calc_hist[max_ind]=calc_hist[index];
		max_ind=0;
	}
	
	return sorted_hist;
}

int mini(int no_one, int no_two)
{
	int min = ( no_one < no_two ? no_one:no_two);
	return min;
}


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
			double believed_guilt = static_cast<double>(guilt);
			int total_profit_trustee = rbf*5*money_invested - money_returned;
			
			ui_init(money_invested,response) = (total_profit_investor -  believed_guilt*(0.1*believed_guilt+0.3)  * max(total_profit_investor - total_profit_trustee, 0));
		}
	}
	
	return ui_init;
}

Matrix_vector initialize_utpi_init()
{
    Matrix_vector utpi_init(nob, Zero_matrix(noa, 5)); //utility of the trustee as perceived by the investor given a belief (either 0 = greedy, or 1 = cooperative)
	for(Matrix_vector::size_type b = 0; b < utpi_init.size(); ++b)
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
				utpi_init[b](money_invested, response) = (total_profit_trustee -  believed_guilt*(0.1*believed_guilt+0.3) * max(total_profit_trustee - total_profit_investor, 0));
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
				sum += exp(1.0/temperature*utpi_init[b](money_invested, money_returned));
			}
			
			for(Matrix::size_type money_returned = 0; money_returned < nor(money_invested); ++money_returned)
			{
				choice_likelihood[b](money_invested, money_returned) = exp(1.0/temperature*utpi_init[b](money_invested, money_returned))/sum;
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

std::vector<double> investor_k( int const& present_time
					 , int const& planning_horizon
					 , boost::array<int,3> guilt_parameter
					 , int const& k1
					 , int const& simulations
					 , boost::array<boost::array<double, nob>, 3> const& belief_parameters
					 , boost::array<int, global_time_horizon> const& pastactions 
					 , boost::array<int, global_time_horizon> const& responses
					 , boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> const& path_numbers
					 , std::vector<double> const& array_pay
					 , boost::array<Matrix, nob> const& ui_init_system
					 , boost::array<Matrix, nob> const& ut_init_system
					 , boost::array<Matrix, nob> const& investor_probabilities_system
					 , boost::array<Matrix, nob> const& trustee_rollout_likelihood_system
					 , Matrix_vector const& investor_choice_likelihood
					 , Matrix const& trustee_choice_likelihood
					 , int factor);



std::vector<double> trustee_k(  int const& money_invested
					, int const& present_time
					, int const& planning_horizon
					, boost::array<int,3> guilt_parameter
					, int const& k2
					, int const& simulations
					, boost::array<boost::array<double, nob>, 3> const& belief_parameters
					, boost::array<int, global_time_horizon> const& pastactions 
					, boost::array<int, global_time_horizon> const& responses
					, boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> const& path_numbers
					, std::vector<double> const& array_pay
					, boost::array<Matrix,nob> const& ui_init_system
					, boost::array<Matrix, nob> const& ut_init_system
					, boost::array<Matrix, nob> const& investor_probabilities_system
					, boost::array<Matrix, nob> const& trustee_rollout_likelihood_system
					, Matrix_vector const& investor_choice_likelihood
					, Matrix const& trustee_choice_likelihood
					, int factor)
{
	
	MEMORY_POOL<True_node> mempool;
	True_node* root = new True_node(); 	
	boost::array<int,global_time_horizon> sorted_hist;
	boost::array<int, global_time_horizon> action;
	boost::array<int, global_time_horizon> response;
	std::vector<double> trustee_payoff (noa,0.0);
	int trustee_guilt = guilt_parameter[k2];	
	for(int t=0; t < global_time_horizon; ++t)
	{
		action[t] = pastactions[t];
	}


	
	for(int t=0; t < global_time_horizon; ++t)
	{
		response[t] = responses[t];
	}
	if( (k2==0) )
	{	
		for(int resp=0; resp < nor(money_invested); ++resp)
		{
			trustee_payoff[resp]=investor_choice_likelihood[trustee_guilt](money_invested, resp);
		}
		delete root;
	}
	else
	{

		True_node* origin = new True_node();
		True_node* current_node;
		True_node* Trustee_node_r;
		origin->set_child(money_invested, root);
		boost::array<int, global_time_horizon> sorted_hist;
		
		boost::array<boost::array<double,nob>,3> initial_beliefs;	
		boost::array<boost::array<double,nob>,3> beliefs;	

		for(unsigned int level=0; level < 3; ++level) 
		{
			for(unsigned int belief=0; belief < nob; ++belief)
			{
				initial_beliefs[level][belief] = belief_parameters[level][belief];
			}
		}
		
		std::vector<double> pay (noa,0.0);				
		boost::array<boost::array<double,noa>,nob> exp_payoffs;
				
		
		boost::array<True_node*,global_time_horizon> path;
		boost::array<double,global_time_horizon> value;
		boost::array<unsigned int, global_time_horizon> action_count;


		
		int last_action;
		int last_response;
		int act;
		int game;
		long long unsigned int summe;
		int max ;
		int old_max;
		long long unsigned int num_act;
		long long unsigned int counter;	
		int unvisited_action;
		int et;		
		boost::array<double,nob> belief_probability;
		double sum =0.0;
		for(int o = 0; o < nob; ++o)
		{
			sum += initial_beliefs[2-k2][o];
		}
		for(int o = 0; o < nob; ++o)
		{
			belief_probability[o] = initial_beliefs[2-k2][o]/sum;
		}
		int trustee_guilt_belief = softmax(belief_probability,17);
			
		path[present_time] = root;
		action[present_time] = money_invested;
		response[present_time]= softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], money_invested),2);
		value[present_time] = ut_init_system[trustee_guilt](action[present_time], response[present_time]);
		root->inc_action_count(response[present_time]);

					
		for(int i = present_time+1; i < planning_horizon; ++i)
		{
			last_action = softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),3);
			last_response = softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], last_action),4);
			value[present_time] += ut_init_system[trustee_guilt](last_action, last_response);
		}
					
		root->rollout_done();

		sum = 0.0;
		for( int i = present_time; i >= present_time; --i)
		{
			sum += value[i];
			path[i]->set_payoff(response[i], path[i]->get_payoff(response[i]) + (sum - path[i]->get_payoff(response[i]) ) / (path[i]->get_action_count(response[i])));
		}

		int local_simulations = simulations;
		
		for(int re=0; re < noa; ++re)	//do normal tree calculation except response is fixed (if available) at 1 of the 5 possible values
		{

			for(int j=0; j < 5*(planning_horizon-present_time+1); ++j) 
			{
			
				for(int level=0; level < 3; ++level)
				{
					for(int belief=0; belief < nob; ++belief)
					{
						beliefs[level][belief] = initial_beliefs[level][belief];
					}
				}
					
				trustee_guilt_belief = softmax(belief_probability,6);		
			
				current_node = origin;
				game = present_time;
				num_act=0;
				summe=0;
				max =0;
				old_max=0;
				
				Trustee_node_r = root;
				
				for(; game < planning_horizon; ++game)
				{
	
					if(!current_node)
					{	
						current_node = new True_node(); 
						Trustee_node_r-> set_child(response[game-1], current_node);					
						if(k2==1)
						{
							summe=0;
							max =0;
							old_max=0;
							num_act=0;
							counter=0;

							if(game>0)
							{
								for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
								{
									sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
								}				
								sorted_hist =custom_sort(sorted_hist, game-1);	
								for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
								{
									if(!(sorted_hist[hist_sum]==0))
									{
										max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
										if(sorted_hist[hist_sum] < old_max)
										{
											cout << "ERROR: sort didn't work" << endl;
										}										
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
										{
											for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
											{
												summe += path_numbers[up][(game)-hist_sum-1];
											}
										}
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
										{
											summe += sorted_hist[hist_sum]-old_max;
										}
										old_max = max;									
									}
								counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
								}
								num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
							}			
							
							for(int belief=0; belief < nob ; ++belief)
							{
								for(int possible_action =0; possible_action < noa; ++possible_action)
								{
									current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief);
								}
							}	
						}
					
						if(k2==2)
						{
							for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
							{
								guilt_parameter[1]=guilt_belief;
								pay = investor_k(game, planning_horizon , guilt_parameter, 1, factor*simulation_iterations/10*(planning_horizon-game), beliefs, action, response,
								path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor);					
								for(int i=0; i <noa ; ++i)
								{
									trustee_payoff[i]=pay[i];
								}						
								for(int possible_action =0; possible_action < noa; ++possible_action)
								{
									current_node->set_exp_payoffs(possible_action,trustee_payoff[possible_action],guilt_belief);
								}							
							}					
						}	
					}
					action[game]=money_invested;
			
					if(k2==0 && game > present_time)
					{
						action[game]= softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),7);
					}
						
						
					if(k2>0 && game >present_time)
					{
						exp_payoffs =current_node->get_exp_payoffs();
						action[game] =  softmax(exp_payoffs[trustee_guilt_belief],8);
					}			

					if(k2==2 && game > present_time) 
					{
						for(int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
						}
					}

					current_node->inc_action_count(action[game]);
					Trustee_node_r = current_node->get_child(action[game]);
					if(!Trustee_node_r)
					{

						Trustee_node_r = new True_node(); 			
						path[game]=Trustee_node_r;
						current_node->set_child(action[game], Trustee_node_r);
			

						response[game]= softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], action[game]),14);
						value[game] = ut_init_system[trustee_guilt](action[game], response[game]);
						for(int i = game + 1; i < planning_horizon; ++i)
						{
							last_action = softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),9);
							last_response = softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], last_action),16);
							value[game] += ut_init_system[trustee_guilt](last_action, last_response);
						}
							
						Trustee_node_r->inc_action_count(response[game]);					
						++game;
						break;		

					}
					else
					{
						if(action[game]==0)
						{
							response[game]=0;
						}
						else
						{

							unvisited_action = Trustee_node_r->get_next_free_child();

							
							if(unvisited_action == noa)
							{
								response[game] = re;
							}
							else
							{
								response[game] = unvisited_action;
							}	

						

						}
						if(k2==1 && !(action[game]==0)) 
						{
							for( int belief=0; belief<nob; ++belief)
							{				
								beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
							}
						}							
						if(k2==2  && !(action[game]==0))
						{
							for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
							{
								beliefs[1][guilt_belief]+=investor_choice_likelihood[guilt_belief](action[game], response[game]);
							}
						}						
						Trustee_node_r->inc_action_count(response[game]);
						value[game] = ut_init_system[trustee_guilt](action[game], response[game]);
						current_node = Trustee_node_r->get_child(response[game]);			
						
					}
					path[game]=Trustee_node_r;
				}
				
				sum = 0.0;
				for( int i = game-1; i >= present_time; --i)
				{
					sum += value[i];
					path[i]->set_payoff(response[i], path[i]->get_payoff(response[i]) + (sum - path[i]->get_payoff(response[i]) ) / (path[i]->get_action_count(response[i])));
				}
			}
		}
		
		for(int iteration = 0; iteration < local_simulations; ++iteration)
		{
			
			for(int level=0; level < 3; ++level)
			{
				for(int belief=0; belief < nob; ++belief)
				{
					beliefs[level][belief] = initial_beliefs[level][belief];
				}
			}
				
			trustee_guilt_belief = softmax(belief_probability,10);		
		
			current_node = origin;
			Trustee_node_r = root;
				
			game = present_time;

			for(; game < planning_horizon; ++game)
			{
	
				if(!current_node)
				{
					current_node = new True_node(); 
					Trustee_node_r-> set_child(response[game-1], current_node);			
					if(k2==1)
					{
						summe=0;
						max =0;
						old_max=0;
						num_act=0;
						counter=0;

						if(game>0)
						{
							for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
							{
								sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
							}				
							sorted_hist =custom_sort(sorted_hist, game-1);	
							for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
							{
								if(!(sorted_hist[hist_sum]==0))
								{
									max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
									if(sorted_hist[hist_sum] < old_max)
									{
										cout << "ERROR: sort didn't work" << endl;
									}										
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
									{
										for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
										{
											summe += path_numbers[up][(game)-hist_sum-1];
										}
									}
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
									{
										summe += sorted_hist[hist_sum]-old_max;
									}
									old_max = max;									
								}
								counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
							}
							num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
						}		
						
						for(int belief=0; belief < nob ; ++belief)
						{
							for(int possible_action =0; possible_action < noa; ++possible_action)
							{
								current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief); //planning horizon can remain
							}
						}	
					}
					
					if(k2==2)
					{
						for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
						{
							guilt_parameter[1]=guilt_belief;
							pay = investor_k(game, planning_horizon , guilt_parameter, 1, factor*simulation_iterations/10*(planning_horizon-game), beliefs, action, response,
							path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor);					
							for(int i=0; i <noa ; ++i)
							{
								trustee_payoff[i]=pay[i];
							}						
							for(int possible_action =0; possible_action < noa; ++possible_action)
							{
								current_node->set_exp_payoffs(possible_action,trustee_payoff[possible_action],guilt_belief);
							}							
						}					
					}	
				}			
				
				action[game]=money_invested;
		
				if(k2==0 && game > present_time)
				{
					action[game]=  softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),11);
				}
					
					
				if(k2>0 && game >present_time)
				{
					exp_payoffs =current_node->get_exp_payoffs();
					action[game] =  softmax(exp_payoffs[trustee_guilt_belief],12);
				}						
				if(k2==2 && game > present_time) 
				{
					for(int belief=0; belief<nob; ++belief)
					{				
						beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
					}
				}										

				current_node->inc_action_count(action[game]);
				Trustee_node_r = current_node->get_child(action[game]);
				if(!Trustee_node_r)
				{

					et = nor(action[game]);
					Trustee_node_r = new True_node(); 			
					path[game]=Trustee_node_r;
					current_node->set_child(action[game], Trustee_node_r);			

					response[game]=softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], action[game]),14);
					value[game] = ut_init_system[trustee_guilt](action[game], response[game]);	
					for(int i = game + 1; i < planning_horizon; ++i)
					{
						last_action = softmax(Matrix_column(trustee_choice_likelihood, trustee_guilt_belief),15);
						last_response = softmax(Matrix_row(trustee_rollout_likelihood_system[trustee_guilt], last_action),16);
						value[game] += ut_init_system[trustee_guilt](last_action, last_response);
					}
						
					Trustee_node_r->inc_action_count(response[game]);
					Trustee_node_r->rollout_done();
					++game;
					break;		

				}
				else
				{
					if(action[game]==0)
					{
						response[game]=0;
					}
					else
					{
						unvisited_action = Trustee_node_r->get_next_free_child();
						
						if(unvisited_action == noa)
						{
							response[game] = Trustee_node_r->get_next_exploration( game == present_time ? (iteration+5*(planning_horizon-present_time+1)+1) : (current_node->get_action_count(action[game])) );
						}
						else
						{
							response[game] = unvisited_action;
						}						

					}
					if(k2==1  && !(action[game]==0)) 
					{
						for(int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
						}
					}							
					if(k2==2   && !(action[game]==0))
					{
						for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
						{
							beliefs[1][guilt_belief]+=investor_choice_likelihood[guilt_belief](action[game], response[game]);
						}
					}								
					Trustee_node_r->inc_action_count(response[game]);
					value[game] = ut_init_system[trustee_guilt](action[game], response[game]);
					current_node = Trustee_node_r->get_child(response[game]);			
						
				}
				path[game]=Trustee_node_r;
						
			}
					
			sum = 0.0;
			for( int i = game-1; i >= present_time; --i)
			{
				sum += value[i];
				path[i]->set_payoff(response[i], path[i]->get_payoff(response[i]) + (sum - path[i]->get_payoff(response[i]) ) / (path[i]->get_action_count(response[i])));
			}
		}
		sum =0.0;
		for(int i =0; i<nor(money_invested); ++i)
		{
			trustee_payoff[i] = exp(1.0/temperature*(root-> get_payoff(i)));
			sum += trustee_payoff[i];
		}
		for(int i =0; i<nor(money_invested); ++i)
		{
			trustee_payoff[i] = trustee_payoff[i]/sum;
		}	
		delete origin;
	}
	mempool.DeleteAll();	
	return trustee_payoff;
}

std::vector<double> investor_k( int const& present_time
					 , int const& planning_horizon
					 , boost::array<int,3> guilt_parameter
					 , int const& k1
					 , int const& simulations
					 , boost::array<boost::array<double, nob>, 3> const& belief_parameters
					 , boost::array<int, global_time_horizon> const& pastactions 
					 , boost::array<int, global_time_horizon> const& responses
					 , boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> const& path_numbers
					 , std::vector<double> const& array_pay
					 , boost::array<Matrix, nob> const& ui_init_system
					 , boost::array<Matrix, nob> const& ut_init_system
					 , boost::array<Matrix, nob> const& investor_probabilities_system
					 , boost::array<Matrix, nob> const& trustee_rollout_likelihood_system
					 , Matrix_vector const& investor_choice_likelihood
					 , Matrix const& trustee_choice_likelihood
					 , int factor)
{	
	MEMORY_POOL<True_node> mempool;
	True_node* root = new True_node();
	std::vector<double> investor_payoff (noa,0.0);
	boost::array<int, global_time_horizon> action;
	boost::array<int, global_time_horizon> response;
	boost::array<int, global_time_horizon> sorted_hist;		
	int investor_guilt = guilt_parameter[k1];
		//prepare action
	for(int l=0; l < global_time_horizon; ++l)
	{
		action[l]=pastactions[l];
	}
		//prepare response
	for(int l=0; l < global_time_horizon; ++l)
	{
		response[l]=responses[l];
	}		
	if((k1==0) )
	{
		long long unsigned int summe=0;
		int max =0;
		int old_max=0;
		long long unsigned int num_act=0;
		int game = present_time;
		long long unsigned int counter=0;

		if(game>0)
		{
			for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
			{
				sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
			}				
			sorted_hist =custom_sort(sorted_hist, game-1);	
			for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
			{
				if(!(sorted_hist[hist_sum]==0))
				{
					max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
					if(sorted_hist[hist_sum] < old_max)
					{
						cout << "ERROR: sort didn't work" << endl;
					}										
					if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
					{
						for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
						{
							summe += path_numbers[up][(game)-hist_sum-1];
						}
					}
					if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
					{
						summe += sorted_hist[hist_sum]-old_max;
					}
					old_max = max;									
				}
				counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); 							
			}
			num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
		}		
		
		for(int act=0; act < noa; ++act)
		{
			investor_payoff[act] = array_pay[num_act + investor_guilt*noa + (planning_horizon-game-1)*noa*nob+act];
		}
		
		delete root;
	}
	else
	{
		std::vector<double> pay (noa,0.0);
	

		True_node* current_node;
		True_node* Trustee_node_r;
	
		int max_level =2;
		boost::array<boost::array<double,nob>,3> initial_beliefs;	
		boost::array<boost::array<double,nob>,3> beliefs;	

		for(unsigned int level=0; level < 3; ++level)  //level 2 uses everything
		{
			for(unsigned int belief=0; belief < nob; ++belief)
			{
				initial_beliefs[level][belief] = belief_parameters[level][belief];
			}
		}
			
	
		boost::array<True_node*,global_time_horizon> path;
		boost::array<double,global_time_horizon> value;
		boost::array<unsigned int, global_time_horizon> action_count;
		
		int game;
		int last_action;
		int last_response;
		int act;
		long long unsigned int summe;
		int max;
		int old_max;
		long long unsigned int num_act;
		long long unsigned int counter;
		int et;
		int unvisited_action;
		boost::array<boost::array<double,noa>,nob> exp_payoffs;		

		boost::array<double,nob> belief_probability;
		double sum =0.0;
		for(int o = 0; o < nob; ++o)
		{
			sum += initial_beliefs[2-k1][o];
		}
		for(int o = 0; o < nob; ++o)
		{
			belief_probability[o] = initial_beliefs[2-k1][o]/sum;			
		}
		int trustee_guilt_belief = softmax(belief_probability,17);
		

		
		path[present_time] = root;
		action[present_time] = softmax(row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),18);
		value[present_time] = ui_init_system[investor_guilt](action[present_time], softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[present_time]),19));
		root->inc_action_count(action[present_time]);
				
		for(int i = present_time+1; i < planning_horizon; ++i)
		{
			last_action = softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),20);
			last_response = softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], last_action),21);
			value[present_time] += ui_init_system[investor_guilt](last_action, last_response);
		}

		sum = 0.0;
		for( int i = present_time; i >= present_time; --i)
		{
			sum += value[i];
			path[i]->set_payoff(action[i], path[i]->get_payoff(action[i]) + (sum - path[i]->get_payoff(action[i]) ) / (path[i]->get_action_count(action[i])));
		}

		int local_simulations = simulations;
		boost::array<boost::array<double, noa>, nob> inv_exp_payoffs;	
		
		for(int ac= 0; ac < noa; ++ac)	
		{

			for(int j=0; j < 5*(planning_horizon-present_time+1); ++j) 
			{
			
				for(int level=0; level < 3; ++level)
				{
					for(int belief=0; belief < nob; ++belief)
					{
						beliefs[level][belief] = initial_beliefs[level][belief];
					}
				}
								
				trustee_guilt_belief = softmax(belief_probability,22);		
		
				current_node = root;
				
				game = present_time;
				for(; game < planning_horizon; ++game)
				{
					if(!current_node)
					{		
						current_node = new True_node();
						Trustee_node_r-> set_child(response[game-1], current_node);
						path[game] = current_node;
						action[game] = softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),90);
						value[game] = ui_init_system[investor_guilt](action[game], softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),23));
						current_node->inc_action_count(action[game]);
						
						for(int i = game + 1; i < planning_horizon; ++i)
						{
							last_action =softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),95);
							last_response = softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], last_action),24);
							value[game] += ui_init_system[investor_guilt](last_action, last_response);
						}					
						++game;
						break;
					}

					path[game] = current_node;		
					
					if(!(current_node->is_rolled_out()))
					{
						if(k1>1)
						{
							summe=0;
							max =0;
							old_max=0;
							num_act=0;
							counter=0;

							if(game>0)
							{
								for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
								{
									sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
								}				
								sorted_hist =custom_sort(sorted_hist, game-1);	
								for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
								{
									if(!(sorted_hist[hist_sum]==0))
									{
										max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
										if(sorted_hist[hist_sum] < old_max)
										{
											cout << "ERROR: sort didn't work" << endl;
										}										
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
										{
											for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
											{
												summe += path_numbers[up][(game)-hist_sum-1];
											}
										}
										if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
										{
											summe += sorted_hist[hist_sum]-old_max;
										}
										old_max = max;									
									}
									counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
								}
								num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
							}			
						
							for(int belief=0; belief < nob ; ++belief)
							{
								for(int possible_action =0; possible_action < noa; ++possible_action)
								{
									current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief);
								}
							}	
						}
						current_node-> rollout_done();
					}					

					int unvisited_action = current_node->get_next_free_child();				
					
					if(unvisited_action == noa)
					{
						action[game] = ac;
					}
					else
					{
						action[game] = unvisited_action;
					}
				
					if(k1==1) 
					{
						for(int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
						}
					}		

					if(k1>1)
					{
						exp_payoffs =current_node->get_exp_payoffs();
						for(int belief=0; belief<nob; ++belief)
						{
							beliefs[1][belief] += exp_payoffs[belief][action[game]]; 
						}
					}
					et = nor(action[game]);
		
					current_node->inc_action_count(action[game]);
					Trustee_node_r = current_node->get_child(action[game]);
					if(!Trustee_node_r)
					{
						Trustee_node_r = new True_node(); 

						current_node->set_child(action[game], Trustee_node_r);
						if(k1>0 && !(action[game]==0))
						{

							
							for(int guilt=0; guilt < nob; ++guilt)
							{
								guilt_parameter[k1-1] = guilt;
								pay = trustee_k( action[game], game, planning_horizon, guilt_parameter ,k1-1, factor*simulation_iterations/10*(planning_horizon-game), beliefs , action, response,
								path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor); //only calc trustee, include inf in trustee

								for(int i=0; i < noa; ++i)
								{	

									inv_exp_payoffs[guilt][i] =pay[i];
								}								
								for( int action_loc = 0; action_loc < noa; ++action_loc)
								{
									Trustee_node_r->set_exp_payoffs(action_loc,inv_exp_payoffs[guilt][action_loc],guilt);
								}							
								
							}	
						}
						
					}

					if(k1>0 && !(action[game]==0))
					{
						exp_payoffs =Trustee_node_r->get_exp_payoffs();
						response[game] = softmax(exp_payoffs[trustee_guilt_belief],25);
					}
					else
					{
						response[game]= (action[game]==0 ? 0 :  softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),26));
					}
					Trustee_node_r->inc_action_count(response[game]);
					
					if(k1==2  && !(action[game]==0) ) 
					{
						for( int belief=0; belief<nob; ++belief)
						{				
							beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
						}
					}			

					value[game] = ui_init_system[investor_guilt](action[game], response[game]);

					current_node = Trustee_node_r->get_child(response[game]);			
				
				}
				sum = 0.0;
				for( int i = game-1; i >= present_time; --i)
				{
					sum += value[i];
					path[i]->set_payoff(action[i], path[i]->get_payoff(action[i]) + (sum - path[i]->get_payoff(action[i]) ) / (path[i]->get_action_count(action[i])));
				}
				
			}		
			
		}
		
		for(unsigned int iteration = 0; iteration < local_simulations; ++iteration)
		{
		
			for(int level=0; level < 3; ++level)
			{
				for(int belief=0; belief < nob; ++belief)
				{
					beliefs[level][belief] = initial_beliefs[level][belief];
				}
			}

			trustee_guilt_belief = softmax(belief_probability,27);		
	
			current_node = root;
			
			game = present_time;
			for(; game < planning_horizon; ++game)
			{

				if(!current_node)
				{		
					current_node = new True_node();
					Trustee_node_r-> set_child(response[game-1], current_node);
					path[game] = current_node;
					action[game] = softmax(row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),28); 
					value[game] = ui_init_system[investor_guilt](action[game], softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),29));
					current_node->inc_action_count(action[game]);

					for(int i = game + 1; i < planning_horizon; ++i)
					{
						last_action = softmax(Matrix_row(investor_probabilities_system[investor_guilt], trustee_guilt_belief),30);
						last_response = softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], last_action),31);
						value[game] += ui_init_system[investor_guilt](last_action, last_response);
					}					
				
					++game;
					break;
				}

				path[game] = current_node;		

					if(k1>1 && !(current_node->is_rolled_out()))
					{
						summe=0;
						max =0;
						old_max=0;
						num_act=0;
						counter=0;

						if(game>0)
						{
							for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
							{
								sorted_hist[hist_sum]=(action[hist_sum]==0 ? 0:((action[hist_sum]-1)*noa + 1 +response[hist_sum]));
							}				
							sorted_hist =custom_sort(sorted_hist, game-1);	
							for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
							{
								if(!(sorted_hist[hist_sum]==0))
								{
									max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
									if(sorted_hist[hist_sum] < old_max)
									{
										cout << "ERROR: sort didn't work" << endl;
									}										
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
									{
										for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
										{
											summe += path_numbers[up][(game)-hist_sum-1];
										}
									}
									if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
									{
										summe += sorted_hist[hist_sum]-old_max;
									}
									old_max = max;									
								}
								counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
							}
							num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));
						}		
						
						for(int belief=0; belief < nob ; ++belief)
						{
							for(int possible_action =0; possible_action < noa; ++possible_action)
							{
								current_node->set_exp_payoffs(possible_action,array_pay[num_act + belief*noa + (planning_horizon-game-1)*noa*nob+possible_action],belief);
							}
						}	
						current_node->rollout_done();						
					}	
				
				unvisited_action = current_node->get_next_free_child();
				
			
				if(unvisited_action == noa)
				{
					action[game] = current_node-> get_next_exploration( game == present_time ? iteration+5*(planning_horizon-present_time+1)+1 : (Trustee_node_r->get_action_count(response[game-1])) );

				}
				else
				{
					action[game] = unvisited_action;
				}
				
				if(k1==1) 
				{
					for(int belief=0; belief<nob; ++belief)
					{				
						beliefs[2][belief] += trustee_choice_likelihood(action[game],belief);
					}
				}					

				if(k1==2)
				{
					exp_payoffs =current_node->get_exp_payoffs();
					for(int belief=0; belief<nob; ++belief)
					{
						beliefs[1][belief]+= exp_payoffs[belief][action[game]]; 
					}
				}
				et = nor(action[game]);
	
				current_node->inc_action_count(action[game]);
				Trustee_node_r = current_node->get_child(action[game]);
				if(!Trustee_node_r)
				{
	
					Trustee_node_r = new True_node(); 
					current_node->set_child(action[game], Trustee_node_r);
					if(k1>0 &&!(action[game]==0))
					{	
							
						for(int guilt=0; guilt < nob; ++guilt)
						{
							guilt_parameter[1] =guilt;
							pay = trustee_k( action[game], game, planning_horizon, guilt_parameter ,1, factor*simulation_iterations/10*(planning_horizon-game), beliefs , action, response,
							path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, factor); //only calc trustee, include inf in trustee
							for(int i=0; i <noa; ++i)
							{
								inv_exp_payoffs[guilt][i] =pay[i];
							}							
							for(int action_loc = 0; action_loc < noa; ++action_loc)
							{
								Trustee_node_r->set_exp_payoffs(action_loc,inv_exp_payoffs[guilt][action_loc],guilt);
							}																
						}										
					}
					
				}

				if(k1>0 && !(action[game]==0))
				{
					exp_payoffs =Trustee_node_r->get_exp_payoffs();
					response[game] = softmax(exp_payoffs[trustee_guilt_belief],33);
				}
				else
				{
					response[game]= (action[game]==0 ? 0 :  softmax(Matrix_row(investor_choice_likelihood[trustee_guilt_belief], action[game]),34));
				}
				Trustee_node_r->inc_action_count(response[game]);
				
				if(k1==2  && !(action[game]==0)) 
				{
					for(int belief=0; belief<nob; ++belief)
					{				
						beliefs[2][belief]+=investor_choice_likelihood[belief](action[game],response[game]);
					}
				}			

				value[game] = ui_init_system[investor_guilt](action[game], response[game]);

				current_node = Trustee_node_r->get_child(response[game]);			
			
			}

			sum = 0.0;
			for( int i = game-1; i >= present_time; --i)
			{
				sum += value[i];
				path[i]->set_payoff(action[i], path[i]->get_payoff(action[i]) + (sum - path[i]->get_payoff(action[i]) ) / (path[i]->get_action_count(action[i])));
			}
			
		}
		
		sum =0.0;
		for(int i =0; i<noa; ++i)
		{		
			investor_payoff[i] = exp(1.0/temperature*(root-> get_payoff(i)));		
			sum += investor_payoff[i];
		}
		for(int i =0; i<noa; ++i)
		{
			investor_payoff[i] = investor_payoff[i]/sum;		
		}	
	delete root;
	}
	mempool.DeleteAll();
	return investor_payoff;
}




int main(int argc, char* argv[])
{	

	static std::vector<double> array_pay(302401125,0.0);
	boost::array<boost::array<int, global_time_horizon+1>,ActionResponsePairs> path_numbers;
	boost::array<boost::array<int, global_time_horizon>,ActionResponsePairs+1> correction_factors;		
			
	int count=0;	
	int ncount=0; 
	path_numbers[0][0]=1;
	path_numbers[0][1]=ActionResponsePairs;
	for(int act=0; act<ActionResponsePairs; ++act)
	{
		correction_factors[act][0] = -act;
	}	
		
	for(int act=1; act<ActionResponsePairs; ++act)
	{
		path_numbers[act][1]= path_numbers[0][1] +correction_factors[act][0];
		count +=path_numbers[act][1];	
		ncount -= path_numbers[act-1][1];
		correction_factors[act][1] = ncount;	
	}
		
	if(global_time_horizon>1)
	{
		path_numbers[0][2]= path_numbers[0][1]+ count;
		correction_factors[0][1]=0;
	}

	for(int t =1; t < (global_time_horizon-1); ++t)
	{	
		count=0;
		ncount=0;	
		for(int act=1; act<ActionResponsePairs; ++act)
		{
			path_numbers[act][t+1]= path_numbers[0][t+1] +correction_factors[act][t];
			count +=path_numbers[act][t+1];	
			ncount -= path_numbers[act-1][t+1];
			correction_factors[act][t+1] = ncount;
			correction_factors[act][t+1] = ncount;
		}
		path_numbers[0][t+2] = path_numbers[0][t+1]+count;
		correction_factors[0][t+1]=0;	
	}					
		
	ifstream infile ("saved_0_3_investor_high_large.bin", ios::in | ios::binary);//|ios::ate);
	infile.seekg (0, ios::beg);	
	char * memblock;
	memblock= new char[1209604504];		
	ifstream::pos_type it =0;
	double store =0.0;
	long long unsigned int tick=0;

	infile.read( memblock,1209604504);	
	it=0;
	for(int t = -1; t <= global_time_horizon-2; ++t) 
	{	
		for(int paths = 1; paths <= path_numbers[0][t+1]; ++paths)
		{	
			for(int y=0; y < (global_time_horizon-t-1);++y) 
			{
				for(int belief=0; belief < nob; ++belief) 
				{			
					for(int action= 0; action < noa; ++ action)	
					{	
						store = *(double*)&memblock[it];
						array_pay[tick]=store; //fill in action likelihood
						it += 8;
						if(static_cast<int>(it) == 1209604504)
						{
							infile.seekg(it);
							infile.read(memblock,1209604446);
							it=0;
						}
						++tick;						
					}
				}	
			}		
		}			
	}
	infile.close();	
		
	delete[] memblock;	

	boost::array<double,noa>  investor_payoff;
	boost::array<double,noa>  trustee_payoff;	
	double sum =0.0;

	int d1;
	int d2;
	int no_sub;
	int start_id =0;
	int end_id;
	int plan;
	int condition;
	
	cout << "Enter Accuracy Condition (0 = discrepancy table calculation, 1 = million path converged example): ";
	cin >> condition;	

	boost::array<int,global_time_horizon> sorted_hist;
	static boost::array<boost::array<boost::array<int,global_time_horizon>,2>, 8100> Subject_Games;
	static boost::array<boost::array<int,2>,8100> Subject_Guilt;
	static boost::array<boost::array<int,2>,8100> Subject_ToM;
	static boost::array<boost::array<int,2>,8100> Subject_Planning;
	
	if(condition == 0)
	{
		cout << "Enter number of simulated subjects: ";
		cin >> no_sub;

		cout << "Enter planning horizon of interest (Integer, 2 to 9): ";
		cin >> plan;	

		for(int sub_id=0; sub_id < no_sub; ++sub_id)
		{
			Subject_Guilt[sub_id][0] = 2;	
			Subject_Planning[sub_id][0] = plan;	
			Subject_ToM[sub_id][0] = 2;
			Subject_Guilt[sub_id][1] = 0;
			Subject_Planning[sub_id][1] = 0;
			Subject_ToM[sub_id][1] = 0;			
		}		
		
		end_id = no_sub;
	}
	else
	{
		no_sub=7;
		for(int sub_id=0; sub_id < no_sub; ++sub_id)
		{
			Subject_Guilt[sub_id][0] = 2;	
			Subject_Planning[sub_id][0] = sub_id+2;	
			Subject_ToM[sub_id][0] = 2;
			Subject_Guilt[sub_id][1] = 0;
			Subject_Planning[sub_id][1] = 0;
			Subject_ToM[sub_id][1] = 0;			
		}			
		end_id=7;
	}
		
	
	boost::array<boost::array<double, nob>, 3> trustee_belief_parameters;	
	boost::array<boost::array<double, nob>, 3> investor_belief_parameters;

	int investor_planning;
	int trustee_planning;
	int WI_ToM;
	int WI_G;
	int WI_P;
	int WT_ToM;
	int WT_G;
	int WT_P;
	double Tlike_max;
	double Ilike_max;
	double like=0.0;
	double Tlike=0.0;
	int k1;
	int k2;	
	double expectation;
	int game;
	long long unsigned int summe;
	int max;
	int old_max;
	long long unsigned int num_act;
	long long unsigned int counter;	
	std::vector<double> holder(noa,0.0);
	boost::array<double,nob> probabilities;	
	Matrix ui_init;
	Matrix_vector utpi_init;
	Matrix_vector investor_choice_likelihood;
	Matrix ui;
	Index_vector max_ui_index;
	Matrix investor_probabilities;
	Matrix ut_init;
	Matrix offer_utility;
	Matrix trustee_choice_likelihood;
	Index_vector max_ut_index;
	Matrix trustee_probabilities;
	Matrix trustee_rollout_likelihood;
	boost::array<int, 3> guilt_parameter;
	boost::array<Matrix, nob> ui_init_system;	
	boost::array<Matrix, nob> investor_probabilities_system;	
	int start;
	for(int system=0; system < nob; ++system)
	{ 
		ui_init_system[system] = initialize_ui_init(system);
		ui = initialize_investor_utility(ui_init_system[system], investor_choice_likelihood);
		max_ui_index = initialize_max_ui_index(ui);
		investor_probabilities_system[system] = initialize_investor_probabilitites(max_ui_index); 		
	}				
	utpi_init = initialize_utpi_init();
	investor_choice_likelihood = initialize_choice_likelihood(utpi_init);	
	boost::array<Matrix, nob> ut_init_system;
	boost::array<Matrix,nob> trustee_rollout_likelihood_system;
	for(int system=0; system < nob; ++system)
	{ 
		ut_init_system[system] = initialize_trustee_utility(system);
		max_ut_index=initialize_max_ut_index(ut_init_system[system]);	
		trustee_probabilities=initialize_trustee_probabilities(ut_init_system[system]);	
		trustee_rollout_likelihood_system[system] =initialize_trustee_rollout_likelihood(trustee_probabilities, max_ut_index);		
	}		
	offer_utility=initialize_offer_utility(investor_choice_likelihood);
	trustee_choice_likelihood = initialize_trustee_choice_likelihood(offer_utility);	

	char OutputFile[40];
	char stra[80];
	
	cout << "Enter the accuracy & speed data output filename (no more than 20 characters): ";
	cin >> OutputFile;	
	strcpy (stra, OutputFile);
	strcat (stra, ".bin");	

	boost::array<boost::array<boost::array<double, nob>, 3>,global_time_horizon> store_trustee_belief_parameters;	
	boost::array<boost::array<boost::array<double, nob>, 3>,global_time_horizon> store_investor_belief_parameters;	

	ofstream ofs(stra, ofstream::out | ofstream::binary);	
	int iteration = 1;
	boost::array<int,8> multiplier;
	if(condition==0)
	{
		multiplier[0]=1;
		multiplier[1]=2;
		multiplier[2]=3;
		multiplier[3]=4;
		multiplier[4]=5;
		multiplier[5]=6;
		multiplier[6]=10;
		multiplier[7]=20;
	}
	else
	{
		iteration=8;
		multiplier[7]=400;
	}
	clock_t stop;	
	boost::array<double, 8100> calculationtime;	
	for(iteration; iteration < 9; ++iteration)
	{
		for(int sub_id= start_id; sub_id < end_id; ++sub_id)
		{
			//cout << sub_id <<endl;

			Tlike_max=1000.0;
			Ilike_max=1000.0;	

			d1 = Subject_Planning[sub_id][0];
			d2 = Subject_Planning[sub_id][1];
			like=0.0;
			Tlike =0.0;	
			for(int level=0; level < 3; ++level)  
			{
				for(int belief=0; belief < nob; ++belief)
				{
					investor_belief_parameters[level][belief] = 1.0;
					for(int time_step=0; time_step < global_time_horizon; ++time_step)
					{							
						store_investor_belief_parameters[time_step][level][belief]=investor_belief_parameters[level][belief];
					}
				}
			}
			for(int level=0; level < 3; ++level)  
			{
				for(int belief=0; belief < nob; ++belief)
				{
					trustee_belief_parameters[level][belief] = 1.0;
					for(int time_step=0; time_step < global_time_horizon; ++time_step)
					{							
						store_trustee_belief_parameters[time_step][level][belief]=trustee_belief_parameters[level][belief];	
					}
				}
			}	

			for(int time_step=0; time_step < 1; ++time_step)
			{
				if(time_step==0)
				{
					stop = clock();	
				}				
				investor_planning = mini(time_step+d1+1, global_time_horizon);	
				trustee_planning= mini(time_step+d2+1, global_time_horizon);
				guilt_parameter[Subject_ToM[sub_id][0]]=Subject_Guilt[sub_id][0];	
				holder = investor_k( time_step, investor_planning , guilt_parameter, Subject_ToM[sub_id][0], multiplier[iteration-1]*simulation_iterations/10*(investor_planning-time_step), investor_belief_parameters, Subject_Games[sub_id][0], Subject_Games[sub_id][1],
				path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, multiplier[(iteration-1)]);			
				for(int i=0; i <noa ; ++i)
				{
					ofs.write( reinterpret_cast<char*>( &holder[i] ), sizeof holder[i] );	
					//cout << holder[i] << endl;
					investor_payoff[i]=holder[i];
					//cout << investor_payoff[i] << endl;
				}
				if(time_step==0)
				{
					stop = clock() -stop;
					calculationtime[sub_id] = ((double) stop)/CLOCKS_PER_SEC;
				}					
				Subject_Games[sub_id][0][time_step]=softmax(investor_payoff,80);							

				if(Subject_ToM[sub_id][1]==0)
				{
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{	
						trustee_belief_parameters[2][guilt_belief]+=trustee_choice_likelihood(Subject_Games[sub_id][0][time_step], guilt_belief);
					}
				}
			
				if(Subject_ToM[sub_id][1]==1)
				{

					game = time_step;
					summe=0;
					max =0;
					old_max=0;
					num_act=0;
					counter=0;
					if(game>0)
					{
						for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
						{
							sorted_hist[hist_sum]=(Subject_Games[sub_id][0][hist_sum]==0 ? 0:((Subject_Games[sub_id][0][hist_sum]-1)*noa + 1 +Subject_Games[sub_id][1][hist_sum]));
						}				
						sorted_hist =custom_sort(sorted_hist, game-1);	
						for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
						{
							if(!(sorted_hist[hist_sum]==0))
							{
								max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
								if(sorted_hist[hist_sum] < old_max)
								{
									cout << "ERROR: sort didn't work" << endl;
								}										
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
								{
									for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
									{
										summe += path_numbers[up][(game)-hist_sum-1];
									}
								}
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
								{
									summe += sorted_hist[hist_sum]-old_max;
								}
								old_max = max;									
							}
							counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
						}
						num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));	
					}
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{
						trustee_belief_parameters[1][guilt_belief]+=array_pay[num_act + guilt_belief*noa + (trustee_planning-game-1)*noa*nob+Subject_Games[sub_id][0][time_step]];				
					}
				}

				if(Subject_ToM[sub_id][0]==2)
				{
					game = time_step;
					summe=0;
					max =0;
					old_max=0;
					num_act=0;
					counter=0;
					if(game>0)
					{
						for(int hist_sum= 0; hist_sum < (game) ; ++hist_sum)
						{
							sorted_hist[hist_sum]=(Subject_Games[sub_id][0][hist_sum]==0 ? 0:((Subject_Games[sub_id][0][hist_sum]-1)*noa + 1 +Subject_Games[sub_id][1][hist_sum]));
						}				
						sorted_hist =custom_sort(sorted_hist, game-1);	
						for(int hist_sum= 0; hist_sum <(game); ++hist_sum)
						{
							if(!(sorted_hist[hist_sum]==0))
							{
								max = (sorted_hist[hist_sum] > max ? sorted_hist[hist_sum]:max);
								if(sorted_hist[hist_sum] < old_max)
								{
									cout << "ERROR: sort didn't work" << endl;
								}										
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum < (game-1))
								{
									for(int up=old_max; up < sorted_hist[hist_sum]; ++up)
									{
										summe += path_numbers[up][(game)-hist_sum-1];
									}
								}
								if(!(sorted_hist[hist_sum]==old_max) && hist_sum == (game-1))
								{
									summe += sorted_hist[hist_sum]-old_max;
								}
								old_max = max;									
							}
							counter += path_numbers[0][(game)-hist_sum-1]*noa*nob*(global_time_horizon-(game-hist_sum-1)); //Need a min here								
						}
						num_act = counter+(summe)*noa*nob*(global_time_horizon-(game));	
					}
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{
						investor_belief_parameters[1][guilt_belief]+=array_pay[num_act + guilt_belief*noa + (investor_planning-game-1)*noa*nob+Subject_Games[sub_id][0][time_step]];								
					}		
				}
				if((Subject_Games[sub_id][0][time_step]==0))
				{
					Subject_Games[sub_id][1][time_step]=0;
				}
				if(!(Subject_Games[sub_id][0][time_step]==0))
				{
					sum =0.0;
					guilt_parameter[Subject_ToM[sub_id][1]]=Subject_Guilt[sub_id][1];
					holder = trustee_k( Subject_Games[sub_id][0][time_step],time_step, trustee_planning, guilt_parameter, Subject_ToM[sub_id][1], multiplier[iteration-1]*simulation_iterations/10*(trustee_planning-time_step), trustee_belief_parameters, 
					Subject_Games[sub_id][0], Subject_Games[sub_id][1], path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, multiplier[(iteration-1)]);
					for(int i=0; i <noa ; ++i)
					{							
						trustee_payoff[i]=holder[i];
					}

					Subject_Games[sub_id][1][time_step]=softmax(trustee_payoff,85);
				}
				if(!(Subject_Games[sub_id][0][time_step]==0))
				{						

					if(Subject_ToM[sub_id][0] ==2)
					{

						for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
						{
							guilt_parameter[1]=guilt_belief;
							holder = trustee_k(Subject_Games[sub_id][0][time_step],time_step, investor_planning, guilt_parameter, 1, multiplier[iteration-1]*simulation_iterations/10*(investor_planning-time_step), investor_belief_parameters,
							Subject_Games[sub_id][0], Subject_Games[sub_id][1], path_numbers, array_pay, ui_init_system, ut_init_system, investor_probabilities_system, trustee_rollout_likelihood_system, investor_choice_likelihood, trustee_choice_likelihood, multiplier[(iteration-1)]);
							for(int i=0; i <noa ; ++i)
							{									
								trustee_payoff[i]=holder[i];
							}
							investor_belief_parameters[0][guilt_belief] += trustee_payoff[Subject_Games[sub_id][1][time_step]];										
						}
					}
				}
				
				if( Subject_ToM[sub_id][0]==0  && !(Subject_Games[sub_id][0][time_step]==0))
				{
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{		
						investor_belief_parameters[2][guilt_belief]+=investor_choice_likelihood[guilt_belief](Subject_Games[sub_id][0][time_step], Subject_Games[sub_id][1][time_step]);
					}
				}						

				
				if(Subject_ToM[sub_id][1]==1  && !(Subject_Games[sub_id][0][time_step]==0))
				{

					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{			
						trustee_belief_parameters[2][guilt_belief] +=investor_choice_likelihood[guilt_belief](Subject_Games[sub_id][0][time_step], Subject_Games[sub_id][1][time_step]);
					}
				}
		
				if(Subject_ToM[sub_id][0] ==2  && !(Subject_Games[sub_id][0][time_step]==0))
				{
					for(int guilt_belief=0; guilt_belief < nob; ++guilt_belief)
					{			
						investor_belief_parameters[2][guilt_belief]+=investor_choice_likelihood[guilt_belief](Subject_Games[sub_id][0][time_step], Subject_Games[sub_id][1][time_step]);
					}								
				}

				for(int level=0; level < 3; ++level)  
				{
					for(int belief=0; belief < nob; ++belief)
					{					
						store_investor_belief_parameters[time_step][level][belief]=investor_belief_parameters[level][belief];					
						store_trustee_belief_parameters[time_step][level][belief]=trustee_belief_parameters[level][belief];	
					}
				}						
			}
			//cout << calculationtime[sub_id] << endl;
			//ofs.write( reinterpret_cast<char*>( &calculationtime[sub_id] ),  sizeof calculationtime[sub_id] );			
		}
	}	
	ofs.close();

}
