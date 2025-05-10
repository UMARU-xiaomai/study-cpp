CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: pipe/shm_example socket/socket_example message_queue/mq_example shared_memory/shm_example

pipe/pipe_example: pipe/pipe_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

socket/socket_example: socket/socket_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

message_queue/mq_example: message_queue/mq_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

shared_memory/shm_example: shared_memory/shm_example.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f pipe/pipe_example socket/socket_example message_queue/mq_example shared_memory/shm_example 