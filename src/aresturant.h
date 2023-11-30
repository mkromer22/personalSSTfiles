
//
// Created by mckrome on 11/3/23.
//

#ifndef PIZZAPROJECT_RESTURANT_H
#define PIZZAPROJECT_RESTURANT_H

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/eli/elementinfo.h>
#include <sst/core/subcomponent.h>
#include <queue>



#include "orderGenerator.h"





namespace SST {

    namespace PizzaProject {
        class orderEvent : public SST::Event {
        public:
            orderEvent() : SST::Event() {}

            orderEvent(std::string order, int distance)
                    : SST::Event(), orderInformation(order), orderDistance(distance) {};

            void serialize_order(SST::Core::Serialization::serializer &ser) override {
                Event::serialize_order(ser);
                ser & orderInformation;
                ser & orderDistance;
            }

            int getDistance() {
                return orderDistance;
            }

            void setDistance(int d) {
                orderDistance = d;
            }

            std::string getOrder() {
                return orderInformation;
            }

            void setOrder(std::string o) {
                orderInformation = o;
            }

            ImplementSerializable(SST::PizzaProject::orderEvent);

        private:
            std::string orderInformation;
            int orderDistance;


        };



        class resturant : public SST::Component {
        public:
            resturant(SST::ComponentId_t id, SST::Params &params);

            ~resturant();

            void setup();

            void finish();



            void handleOrderEvent(SST::Event *ev);

            bool tick(SST::Cycle_t currentCycle);

            SST_ELI_REGISTER_COMPONENT(
                    resturant,
            "PizzaProject",
            "resturant",
            SST_ELI_ELEMENT_VERSION(1,0,0),
            "Pizza Project main resturant hub",
            COMPONENT_CATEGORY_UNCATEGORIZED
            );

            SST_ELI_DOCUMENT_PARAMS(
            { "simulationTime", "how long the simulation will run (in hours)", "12" }
            );
            SST_ELI_DOCUMENT_SUBCOMPONENT_SLOTS(
            { "pizzaOven", "Slot for a pizza oven", "SST::PizzaProject::pizzaOven" }
            );

            SST_ELI_DOCUMENT_STATISTICS(
            { "totalOrders", "Total number of pizza's ordered", "pizzas", 3 },
            { "totalBaked", "Total number of pizza's baked", "pizzas", 3 },
            {"daysWithTooManyPizzas", "Number of days with more than 10 pizzas at the end of the day waiting to be delivered", "days", 3}
            );

            SST_ELI_DOCUMENT_PORTS(
            { "driver%d", "port to connect to a driver component", {"sst.PizzaProject.orderEvent"} },
            { "orderGenerator", "port to connect to the order generator component", {"sst.PizzaProject.orderEvent"} },
            );

        private:


            SST::Output output;
            Statistic<int> *totalOrders;
            Statistic<int> *totalBaked;
            Statistic<int> *daysWithTooManyPizzas;



            SST::Link *orderGenerator;



            std::queue<orderEvent *> orders;
            std::queue<orderEvent *> pizzas;

            int runTime;

            struct data{
                int totalPizzasMade;
                int totalPizzasOrdered;

            };

            data dailyReport;




        };
    }
}


#endif //PIZZAPROJECT_RESTURANT_H
