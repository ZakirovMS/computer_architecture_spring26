CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -I"FMOD/api/core/inc" -I"FMOD/api/studio/inc"
LDFLAGS = -L"FMOD/api/core/lib/x86_64" -L"FMOD/api/studio/lib/x86_64" -lfmod -lfmodstudio
TARGET = myprogram
SOURCES = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)

run: $(TARGET)
	LD_LIBRARY_PATH="FMOD/api/core/lib/x86_64:FMOD/api/studio/lib/x86_64" ./$(TARGET)

.PHONY: all clean run