.PHONY: clean all

TRICKIES = WaterOnBars
all: $(TRICKIES)

$(TRICKIES): $(TRICKY=$(.TARGET))

CXX      = g++
CXXFLAGS = -Wall -std=c++17 -O3

$(TRICKY): $(TRICKY).cpp
	# note: I could have written $(CXX) $(CXXFLAGS) $< -o $@
	# but I would never do that; guess why (yes, readibility)
	$(CXX) $(CXXFLAGS) $(TRICKY).cpp -o $(TRICKY)

clean:
	rm -f $(TRICKIES)
