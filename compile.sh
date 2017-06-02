g++ -ggdb `pkg-config --cflags opencv` -o `basename fuzzykmeans.cpp .cpp` fuzzykmeans.cpp `pkg-config --libs opencv`
