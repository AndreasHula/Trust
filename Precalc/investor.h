#ifndef INVESTOR_H_INCLUDE_GUARD
#define INVESTOR_H_INCLUDE_GUARD
#include "memorypool.h"
#include "global.h"

Matrix initialize_ui_init(int investor_guilt);
Matrix_vector initialize_utpi_init();
Matrix initialize_investor_utility(Matrix const& ui_init, Matrix_vector const& choice_likelihood);
Matrix_vector initialize_choice_likelihood(const Matrix_vector& utpi_init);
Index_vector initialize_max_ui_index(const Matrix& ui);
Matrix initialize_investor_probabilitites(const Index_vector& max_ui_index);

Value_Node* level_0_investor(  int const& time_horizon
							, boost::array<boost::array<double,nob>,3> const& investor_belief_parameters						
							, MEMORY_POOL<Value_Node>& mempool);							
											
#endif