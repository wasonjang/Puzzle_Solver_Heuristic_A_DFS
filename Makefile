CXX=g++
CXXFLAGS=-g -Wall 
BIN_DIR = bin

$(BIN_DIR)/puzzle: $(BIN_DIR)/puzzle.o $(BIN_DIR)/board.o $(BIN_DIR)/puzzle_solver.o $(BIN_DIR)/puzzle_heur.o $(BIN_DIR)/puzzle_move.o
	$(CXX) $(CXXFLAGS) $(DEFS) $(BIN_DIR)/puzzle.o $(BIN_DIR)/board.o $(BIN_DIR)/puzzle_solver.o $(BIN_DIR)/puzzle_heur.o $(BIN_DIR)/puzzle_move.o -o $@

$(BIN_DIR)/puzzle.o: puzzle.cpp board.h puzzle_heur.h puzzle_solver.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle.cpp
$(BIN_DIR)/board.o: board.cpp board.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c board.cpp
$(BIN_DIR)/puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h heap.h board.h  puzzle_move.h puzzle_heur.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_solver.cpp
$(BIN_DIR)/puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h board.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_heur.cpp
$(BIN_DIR)/puzzle_move.o: puzzle_move.cpp puzzle_move.h board.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_move.cpp

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

clean: 
	rm -rf $(BIN_DIR)