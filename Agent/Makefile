Sources=main.cpp agent.cpp tcp_server.cpp remoTestMessage.cpp
Executable=Agent

CFlags=-c -g -std=c++11 -pthread
LDFlags=
ObjectDir=src/
SourceDir=src/
BinDir=

CC=c++
RM=rm

Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: $(CSources) $(CExecutable)

$(CExecutable): $(CObjects)
	$(CC) $(LDFlags) $(CObjects) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) $(CFlags) $< -o $@

clean:
	$(RM) $(CObjects) $(CExecutable)