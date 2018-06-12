#pragma once

#include <ff/pipeline.hpp>
#include <ff/node.hpp>
#include <ff/farm.hpp>
#include "Montecarlo.h"
#include "interval_number.h"
#include <string.h>
#include <fstream>
#include "function.h"

using namespace ff;

namespace Montecarlo{

// first stage
struct readStream : public ff_node_t<interval_number>{
    std::ifstream readStreamFile;
    func mainFunc;
    
    readStream(std::string f, func ffunc);
    interval_number * svc(interval_number *);
};
// second stage
interval_number * randomNumber(interval_number * intervalN, ff_node *const);
// third stage
interval_number * randomListNumber(interval_number * intervalN, ff_node *const);
// calculation MainTask
interval_number * calculateMonte(interval_number * intervalN, ff_node *const);

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

struct worker_farm: public ff_node_t<interval_number>{
    worker_farm();
    interval_number * svc(interval_number * intervalN);
    
};

interval_number * write_stage(interval_number * in, ff_node * const);
    
struct writer_lastStage: public ff_minode_t<interval_number>{
    interval_number * svc(interval_number * task);
};
}




