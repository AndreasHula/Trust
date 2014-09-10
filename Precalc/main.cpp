#include "global.h"
#include "memorypool.h"
#include "investor.h"



int main(int argc, char* argv[])
{	
	

	boost::array<boost::array<double, nob>, 3> investor_belief_parameters;
	for(int level=0; level < 3; ++level)  
	{
		for(int belief=0; belief < nob; ++belief)
		{
			investor_belief_parameters[level][belief] = 1.0;
		}
	}

	
	MEMORY_POOL<Value_Node> mempool;


	Value_Node* tree_root = level_0_investor(global_time_horizon, investor_belief_parameters,  mempool);

	
	//investor resultate anzeigen
	cout << "\npayoff of root: " << endl;
	for(int i = 0; i < noa; ++i)
	{
		cout << i << ": " << tree_root->get_payoff(0,i,0) << "\n" << endl;
	}

}
