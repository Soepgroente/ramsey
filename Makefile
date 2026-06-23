EXECUTABLE	:=	ramsey
VISUALS		:=	visuals.out

CC			:=	c++
CPPFLAGS	=	-Wall -Wextra -Werror -std=c++20 $(HEADERS) -flto -O2 -ffast-math -march=native -DNDEBUG
#CPPFLAGS	+=	-g #-fsanitize=address #-DDEBUG

GUI_DIR		=	imgui
HEADERS		=	-Iinclude -I$(GUI_DIR) -I$(GUI_DIR)/backends -I/opt/homebrew/include

GUISOURCES	=	imgui.cpp \
				imgui_demo.cpp \
				imgui_draw.cpp \
				imgui_tables.cpp \
				imgui_widgets.cpp \
				backends/imgui_impl_glfw.cpp \
				backends/imgui_impl_opengl3.cpp \
				visualizerMain.cpp \
				Visualizer.cpp \
				VisualizerCallbacks.cpp \
				VisualizerDraw.cpp \
				VisualizerInitialize.cpp \

UNAME_S		=	$(shell uname -s)
LIBS		:=	-L/opt/homebrew/lib -lglfw -framework OpenGL -framework Cocoa -framework IOKit  

SRCS	 	:=	checkClusters.cpp \
				maths.cpp \
				preColor.cpp \
				solve.cpp \
				Stopwatch.cpp \
				utils.cpp \

SRC_DIR		:=	src
OBJ_DIR		:=	$(SRC_DIR)/obj
RES_DIR		:=	results

MAIN		=	main.cpp

_MAIN		=	$(addprefix $(OBJ_DIR)/,$(notdir $(MAIN:%.cpp=%.o)))

OBJECTS		=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:%.cpp=%.o)))
GUIOBJECTS	=	$(addprefix $(OBJ_DIR)/,$(notdir $(GUISOURCES:%.cpp=%.o)))

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl $(shell pkg-config --static --libs glfw3)

	CPPFLAGS += `pkg-config glfw3`
	HEADERS += -isystem /opt/homebrew/include -isystem /usr/local/include
endif

all: $(VISUALS) $(EXECUTABLE)

$(RES_DIR):
	mkdir -p $(RES_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): $(OBJ_DIR) $(RES_DIR) $(_MAIN) $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(_MAIN) $(HEADERS) -o $(EXECUTABLE)

$(VISUALS): $(OBJ_DIR) $(OBJECTS) $(GUIOBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(HEADERS) $(GUIOBJECTS) -o $(VISUALS) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : visualizer/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

$(OBJ_DIR)/%.o : $(GUI_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

$(OBJ_DIR)/%.o : $(GUI_DIR)/backends/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

reset:
	rm -rf $(RES_DIR)/*.txt

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(RES_DIR)/*.txt

fclean: clean
	rm -f $(EXECUTABLE)
	rm -f $(VISUALS)

re: fclean all

retest: fclean test

.PHONY: all clean fclean re test