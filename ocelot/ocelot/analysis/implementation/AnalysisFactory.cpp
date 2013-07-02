/*! \file   AnalysisFactory.cpp
	\date   Wednesday October 3, 2012
	\author Gregory Diamos <gdiamos@nvidia.com>
	\brief  The source file for the AnalysisFactory class.
	
*/

// Ocelot Includes
#include <ocelot/analysis/interface/AnalysisFactory.h>

#include <ocelot/analysis/interface/DataflowGraph.h>
#include <ocelot/analysis/interface/DivergenceAnalysis.h>
#include <ocelot/analysis/interface/AffineAnalysis.h>
#include <ocelot/analysis/interface/ControlTree.h>
#include <ocelot/analysis/interface/DominatorTree.h>
#include <ocelot/analysis/interface/PostdominatorTree.h>
#include <ocelot/analysis/interface/StructuralAnalysis.h>
#include <ocelot/analysis/interface/ThreadFrontierAnalysis.h>
#include <ocelot/analysis/interface/LoopAnalysis.h>
#include <ocelot/analysis/interface/ConvergentRegionAnalysis.h>
#include <ocelot/analysis/interface/SimpleAliasAnalysis.h>
#include <ocelot/analysis/interface/CycleAnalysis.h>
#include <ocelot/analysis/interface/SafeRegionAnalysis.h>
#include <ocelot/analysis/interface/ControlDependenceAnalysis.h>
#include <ocelot/analysis/interface/DataDependenceAnalysis.h>
#include <ocelot/analysis/interface/DependenceAnalysis.h>

namespace analysis 
{

Analysis* AnalysisFactory::createAnalysis(const std::string& name,
	const StringVector& options)
{
	Analysis* analysis = nullptr;

	if(name == "ControlTreeAnalysis")
	{
		analysis = new ControlTree;
	}
	else if(name == "DominatorTreeAnalysis")
	{
		analysis = new DominatorTree;
	}
	else if(name == "PostDominatorTreeAnalysis")
	{
		analysis = new PostdominatorTree;
	}
    else if(name == "DataflowGraphAnalysis"
    	|| name == "StaticSingleAssignment"
    	|| name == "MinimalStaticSingleAssignment"
    	|| name == "GatedStaticSingleAssignment")
	{
		auto dfg = new DataflowGraph;
		
		if(name == "DataflowGraphAnalysis")
		{
			dfg->setPreferredSSAType(analysis::DataflowGraph::None);
		}
		else if(name == "StaticSingleAssignment")
		{
			dfg->setPreferredSSAType(analysis::DataflowGraph::Default);
		}
		else if(name == "MinimalStaticSingleAssignment")
		{
			dfg->setPreferredSSAType(analysis::DataflowGraph::Minimal);
		}
		else if(name == "GatedStaticSingleAssignment")
		{
			dfg->setPreferredSSAType(analysis::DataflowGraph::Gated);
		}
		
		analysis = dfg;
	}
	else if(name == "DivergenceAnalysis")
	{
		analysis = new DivergenceAnalysis;
	}
	else if(name == "AffineAnalysis")
	{
		analysis = new AffineAnalysis;
	}
	else if(name == "StructuralAnalysis")
	{
		analysis = new StructuralAnalysis;
	}
	else if(name == "ThreadFrontierAnalysis")
	{
		analysis = new ThreadFrontierAnalysis;
	}
	else if(name == "LoopAnalysis")
	{
		analysis = new LoopAnalysis;
	}
	else if(name == "ConvergentRegionAnalysis")
	{
		analysis = new ConvergentRegionAnalysis;
	}
	else if(name == "SafeRegionAnalysis")
	{
		analysis = new SafeRegionAnalysis;
	}
	else if(name == "CycleAnalysis")
	{
		analysis = new CycleAnalysis;
	}
	else if(name == "SimpleAliasAnalysis")
	{
		analysis = new SimpleAliasAnalysis;
	}
	else if(name == "ControlDependenceAnalysis")
	{
		analysis = new ControlDependenceAnalysis;
	}
	else if(name == "DataDependenceAnalysis")
	{
		analysis = new DataDependenceAnalysis;
	}
	else if(name == "DependenceAnalysis")
	{
		analysis = new DependenceAnalysis;
	}

	if(analysis != nullptr)
	{
		analysis->configure(options);
	}
	
	return analysis;
}

}

