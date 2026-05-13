CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC = src/main.cpp \
      src/scheduler.cpp \
      src/metrics.cpp \
      src/simulation.cpp \
      src/schedulers/fcfs.cpp \
      src/schedulers/sjf.cpp \
      src/schedulers/rr.cpp \
      src/schedulers/mlfq.cpp

TARGET = kronos

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
