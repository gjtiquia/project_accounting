MAIN = main.cpp useful_functions.cpp 
MODES_1 = mode1_add.cpp mode2_delete.cpp mode3_edit.cpp mode4_view.cpp 
MODES_2 = mode5_report.cpp mode6_budget_monitoring.cpp mode7_trend.cpp

OBJECTS = $(MAIN)$(MODES_1)$(MODES_2)

main: $(OBJECTS)
	g++ $(OBJECTS) -o main
