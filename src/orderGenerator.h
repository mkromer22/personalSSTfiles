//
// Created by mckrome on 11/3/23.
//

#ifndef PIZZAPROJECT_ORDERGENERATOR_H
#define PIZZAPROJECT_ORDERGENERATOR_H

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/eli/elementinfo.h>
#include <sst/core/subcomponent.h>
#include <sst/core/rng/marsaglia.h>
#include "aresturant.h"

namespace SST {
    namespace PizzaProject {

        class orderGenerator : public SST::Component {
        public:
            orderGenerator(SST::ComponentId_t id, SST::Params &params);

            ~orderGenerator();

            void setup();

            void finish();

            bool clockTick(SST::Cycle_t CurrentCycle);

            SST_ELI_REGISTER_COMPONENT(
                    orderGenerator,
            "PizzaProject",
            "orderGenerator",
            SST_ELI_ELEMENT_VERSION(1,0,0),
            "Order generator for the pizza simulation",
            COMPONENT_CATEGORY_UNCATEGORIZED
            )

            SST_ELI_DOCUMENT_PARAMS(
            { "frequency", "how often the pizzas may be ordered in seconds", "120s" },
            { "probability", "The likelyhood of an order being generated every cycle (0-10)", "5" }

            )



            SST_ELI_DOCUMENT_PORTS(
            { "resturant", "Connection point to the resturant", {"sst.PizzaProject.orderEvent"} }
            )


        private:
            SST::Output output;
            SST::Link *resturant;
            SST::RNG::MarsagliaRNG *rng;


            std::string clock;
            int probability;


        };
    }
}



#endif //PIZZAPROJECT_ORDERGENERATOR_H
