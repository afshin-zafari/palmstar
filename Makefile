

HEADER_DIR=./include
SOURCE_DIR=./src
OUT_DIR = ./out

COMPILER=g++-7
LINKER=g++

APP_NAME=palmmain

LINK_FLAGS= -lrt  -lstdc++ -Wl,--allow-multiple-definition
COMP_FLAGS= -I$(HEADER_DIR) -std=c++17 -O2
#########################################################
sources    :=$(notdir $(shell ls -Sr $(SOURCE_DIR)/*.cpp))
objnames   :=$(sources:%.cpp=%.o)
headers   :=$(notdir $(shell ls -Sr $(HEADER_DIR)/*.hpp))
objects    :=$(addprefix $(OUT_DIR)/,$(objnames))	

all: $(OUT_DIR)/$(APP_NAME)

$(OUT_DIR)/$(APP_NAME): $(objects) 
	$(info )
	$(info Link objects.)
	$(LINKER)  $(objects) $(LINK_FLAGS) -o $(OUT_DIR)/$(APP_NAME)
	$(info )

$(OUT_DIR)/%.o:$(SOURCE_DIR)/%.cpp 
	$(info Compile the source file: $@)
	@$(COMPILER) -c -o $@ -MMD $< $(COMP_FLAGS) 


	

clean: 
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/*.d $(OUT_DIR)/$(APP_NAME) 
-include $(OUT_DIR)/*.d