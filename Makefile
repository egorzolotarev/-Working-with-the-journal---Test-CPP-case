CXX = gcc
CXXFLAGS = -std=c++17 -fPIC
LDFLAGS = -lstdc++ -lpthread -Wl,-rpath,'$$ORIGIN/../lib'

LIB_SRC_DIR = libjournal/src
LIB_INC_DIR = libjournal/include
APP_SRC_DIR = app/src
OBJ_DIR = build/obj
LIB_DIR = build/lib
APP_DIR = build/app

.PHONY: all lib app clean

all: lib app

# Билдится либа
lib: $(LIB_DIR)/libjournal.so

$(LIB_DIR)/libjournal.so: $(OBJ_DIR)/Journal.o $(OBJ_DIR)/FileWriter.o | $(LIB_DIR)
	$(CXX) -shared -o $@ $^

$(OBJ_DIR)/Journal.o: $(LIB_SRC_DIR)/Journal.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INC_DIR) -c $< -o $@

$(OBJ_DIR)/FileWriter.o: $(LIB_SRC_DIR)/FileWriter.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INC_DIR) -c $< -o $@

$(LIB_DIR):
	mkdir -p $@

# Билдится приложение
app: $(APP_DIR)/run_app

$(APP_DIR)/run_app: $(OBJ_DIR)/App.o $(LIB_DIR)/libjournal.so | $(APP_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIB_DIR)/libjournal.so $(LDFLAGS)

$(OBJ_DIR)/App.o: $(APP_SRC_DIR)/App.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INC_DIR) -c $< -o $@

build/app:
	mkdir -p $@

build build/obj:
	mkdir -p $@

clean:
	rm -rf build