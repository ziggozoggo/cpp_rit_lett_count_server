CC          := g++
CSTANDARTS  := -std=c++17 -lstdc++
CWARNS      := -Wall -Werror -Wextra
CFLAGS      := $(CSTANDARTS) $(CWARNS) -I.
GCOV_FLAGS  := -fprofile-arcs -ftest-coverage
LIBS=-lm

BUILD_DIR		:= build
BUILD_DIR_CL 	:= $(BUILD_DIR)/client
BUILD_DIR_SR 	:= $(BUILD_DIR)/server

CLIENT_MODULES  := client $(wildcard core/*)
SERVER_MODULES 	:= server $(wildcard server/*)

CLIENT_SRC	:= $(foreach sdir,$(CLIENT_MODULES),$(wildcard $(sdir)/*.cpp))
SERVER_SRC	:= $(foreach sdir,$(SERVER_MODULES),$(wildcard $(sdir)/*.cpp))

CLIENT_OBJ	:= $(addprefix $(BUILD_DIR_CL)/,$(notdir $(CLIENT_SRC:%.cpp=%.o)))
SERVER_OBJ	:= $(addprefix $(BUILD_DIR_SR)/,$(notdir $(SERVER_SRC:%.cpp=%.o)))

vpath %.cpp $(CLIENT_MODULES) $(SERVER_MODULES)

TARGET_CL := build/client_run
TARGET_SR := build/server_run

TEST_DIR := unit_tests
TEST_EXE := s21_containers_test.exe

.PHONY: all server client 
.DELETE_ON_ERROR:

all: server client

client: $(TARGET_CL)

server: $(TARGET_SR)

$(TARGET_CL): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $@ $(LIBS)

$(TARGET_SR): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $@ $(LIBS)

$(BUILD_DIR_CL)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(BUILD_DIR_SR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

.PHONY: clean clean_obj 

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so *run
	cd $(BUILD_DIR_CL) && rm -rf *.o *.a *.exe *.so
	cd $(BUILD_DIR_SR) && rm -rf *.o *.a *.exe *.so
	rm -rf *.o *.a *.exe *.so

clean: clean_obj 

.PHONY: clang_check clang

clang_check:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -n {} \;
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} \;
	rm .clang-format