//
// Created by mckrome on 11/3/23.
//

#include "aresturant.h"


using namespace SST;
using namespace SST::PizzaProject;

resturant::resturant(SST::ComponentId_t id, SST::Params &params) : SST::Component(id){
    std::cout<<"Making the Pizza Resturant"<<std::endl;
    output.init("Pizza resturant is up and running", 1, 0, SST::Output::STDOUT);

    runTime = params.find<int>("simulationTime", 3);

    registerAsPrimaryComponent();
    primaryComponentDoNotEndSim();

    totalOrders = registerStatistic<int>("totalOrders");
    totalBaked = registerStatistic<int>("totalBaked");
    daysWithTooManyPizzas = registerStatistic<int>("daysWithTooManyPizzas");



    orderGenerator = configureLink("orderGenerator", new SST::Event::Handler<resturant>(this, &resturant::handleOrderEvent));
    if(!orderGenerator){
        //output.fatal(CALL_INFO, -1, "Failed to configure 'generator port'\n");
    }

    std::string clock = "60s";

    registerClock(clock, new SST::Clock::Handler<resturant>(this, &resturant::tick));




}
resturant::~resturant(){

}

void resturant::setup(){

    dailyReport.totalPizzasMade = 0;
    dailyReport. totalPizzasOrdered = 0;
}
void resturant::finish(){

}

void resturant::handleOrderEvent(SST::Event *ev) {

    SST::PizzaProject::orderEvent *ord = dynamic_cast<SST::PizzaProject::orderEvent *>(ev);
    if(ord != nullptr){
        orders.push(ord);
        totalOrders->addData(1);
        dailyReport.totalPizzasOrdered++;
    }
    delete ev;

}


bool resturant::tick(SST::Cycle_t currentCycle) {

    if (runTime * 60 >= currentCycle) {

        if ((currentCycle % 1440) == 0) {
            std::cout << "-----------------------------------------------------------------" << std::endl;
            std::cout << "                Daily report        Day " << int(currentCycle / 1440) << std::endl;
            std::cout << "Total Pizzas Ordered: " << dailyReport.totalPizzasOrdered << std::endl;
            std::cout << "Total Pizzas Made: " << dailyReport.totalPizzasMade << std::endl;
            std::cout << "There are " << orders.size() << " pizzas waiting to be made" << std::endl;
            std::cout << "There are " << pizzas.size() << " pizzas waiting to be delivered" << std::endl;
            dailyReport.totalPizzasMade = 0;
            dailyReport.totalPizzasOrdered = 0;
        }
    }


    if(runTime * 60 <= currentCycle) {

            primaryComponentOKToEndSim();
            return true;


    }


    return false;
}








