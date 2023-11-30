//
// Created by mckrome on 11/3/23.
//

#include "orderGenerator.h"


using namespace SST;
using namespace SST::PizzaProject;

orderGenerator::orderGenerator(SST::ComponentId_t id, SST::Params &params) : SST::Component(id) {
    output.init("orderGenerator-" + getName() + "->", 1, 0, SST::Output::STDOUT);
    std::cout<<"Making the order generator"<<std::endl;

    clock = params.find<std::string>("frequency", "120s");
    std::string clockVal = "120s";
    registerClock(clockVal, new SST::Clock::Handler<orderGenerator> (this, &orderGenerator::clockTick));

    resturant = configureLink("resturant");


}
orderGenerator::~orderGenerator() {

}

void orderGenerator::setup() {


}
void orderGenerator::finish() {

}

bool orderGenerator::clockTick(SST::Cycle_t CurrentCycle) {
    resturant->send(new SST::PizzaProject::orderEvent("Cheese Pizza", 15));
    return false;

}