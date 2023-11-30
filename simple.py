import sst
import sys

simTime = 5170
mainResturant = sst.Component("MainResturant", "PizzaProject.resturant")
mainResturant.addParams({
    "simulationTime": simTime

})

pizzaGenerator = sst.Component("pizzaGenerator", "PizzaProject.orderGenerator")
pizzaGenerator.addParams({
    "frequency": "120s",
    "probability": 10

})
genLink = sst.Link("genLink")
genLink.connect((pizzaGenerator, "resturant", "1ns"), (mainResturant, "orderGenerator", "1ns"))



sst.setStatisticLoadLevel(0)
sst.enableAllStatisticsForAllComponents()