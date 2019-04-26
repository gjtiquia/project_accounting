MAIN = main.cpp useful_functions.cpp 
MODES_1 = mode_add.cpp mode_delete.cpp mode_edit.cpp mode_view.cpp 
MODES_2 = mode_report.cpp mode_budget_monitoring.cpp mode_trend.cpp

OBJECTS = $(MAIN)$(MODES_1)$(MODES_2)

main: $(OBJECTS)
	g++ $(OBJECTS) -o main
