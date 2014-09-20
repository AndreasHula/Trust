#release variables
#Directory for boost ("boostdirectory") and lib64 need to be adapted
FLAGS = -O3 -DNDEBUG -DBOOST_SYSTEM_STATIC_LINK=1 -DBOOST_THREAD_USE_LIB=1 -DDATE_TIME_INLINE
LINKING = -L"/boostdirectory/boost/boost_1_55_0" -lboost_thread -lboost_random -lboost_system -L"/usr/lib64" -lpthread -lrt -L"/usr/lib/gcc/x86_64-redhat-linux/4.4.6" -lstdc++

SOURCES = main.cpp RandomSingleton.cpp global.cpp
INCLUDES = -I"/boostdirectory/boost/boost_1_55_0"

EXECUTABLE = Estimate.exe
OBJ_DIR = objects

.PHONY: all clean
.SILENT:

OBJECTS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(basename $(notdir $(SOURCES)))))
DEPFILES = $(OBJECTS:.o=.d)

all: $(EXECUTABLE)

-include $(DEPFILES)

$(EXECUTABLE): $(OBJ_DIR) $(OBJECTS)
	@echo \>\> linking $(EXECUTABLE)
	g++ $(OBJECTS) $(FLAGS) -o $(EXECUTABLE) $(LINKING)


$(OBJ_DIR):
	mkdir $@

$(OBJECTS):
	g++ $(filter $(basename $(@F)).%, $(SOURCES)) $(FLAGS) $(INCLUDES) -MMD -MF $(@:.o=.d) -MT $@ -c -o $@

clean:
	del $(OBJ_DIR)
	del $(EXECUTABLE).exe
