TARGET = http_server
CXX = g++
CXXFLAGS = -Wall -pedantic -Wno-long-long -O2 -g -std=c++11
LDFLAGS = -pthread
DOCDIR = ./doc
DOCCONF = doxygen.config
OBJ = ./src/config/CConfig.o ./src/config/CParserINI.o ./src/content/CAbstractContent.o ./src/content/CDirContent.o ./src/content/CEmptyContent.o ./src/content/CExternalContent.o ./src/content/CFileContent.o ./src/content/CHTMLGenerator.o ./src/content/CPathResolver.o ./src/content/CStringContent.o ./src/globals.o ./src/logger/CLogger.o ./src/logger/ELogFlags.o ./src/main.o ./src/network/CPortObtainer.o ./src/network/CSocketIO.o ./src/requests/CRequest.o ./src/requests/CRequestParser.o ./src/requests/EMethodType.o ./src/requests/response_generators/CAbstractGenerator.o ./src/requests/response_generators/CErrorGenerator.o ./src/requests/response_generators/CGetGenerator.o ./src/requests/response_generators/CHeadGenerator.o ./src/requests/response_generators/COptionsGenerator.o ./src/signals/signals.o ./src/threads/CPortThread.o ./src/threads/CRunnable.o ./src/threads/CSignalThread.o ./src/threads/CThreadPool.o ./src/threads/CWorkerThread.o ./src/threads/primitives/CMutex.o ./src/threads/primitives/CSem.o 

all: compile doc

compile: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJ) $(DOCDIR) *.d
	find . -type f -name "*.d" -delete
	find . -type f -name "*.d.tmp" -delete

doc:
	doxygen $(DOCCONF)

run:
	./$(TARGET)

valgrind:
	valgrind --leak-check=yes ./$(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@

-include $(OBJS:.o=.d)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM $(CXXFLAGS) $*.cpp > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d

