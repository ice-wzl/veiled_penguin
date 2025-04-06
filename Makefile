CXX = g++
CXXFLAGS = -std=c++17 -lstdc++fs
SRC = veiledpenguin.cpp
TARGET_DYNAMIC = veiledpenguin
TARGET_STATIC = veiledpenguin-static

all: $(TARGET_DYNAMIC) $(TARGET_STATIC)

$(TARGET_DYNAMIC): $(SRC)
	$(CXX) $(SRC) -o $(TARGET_DYNAMIC) $(CXXFLAGS)

$(TARGET_STATIC): $(SRC)
	$(CXX) $(SRC) -o $(TARGET_STATIC) $(CXXFLAGS) -static -static-libstdc++

clean:
	rm -f $(TARGET_DYNAMIC) $(TARGET_STATIC)
