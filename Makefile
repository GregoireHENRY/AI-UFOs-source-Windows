# ==== COMPILER FLAGS ==========================================================
GNU := g++
LFLAGS := -g -Ofast -Wall -Wextra
RFLAGS :=
INCLUDES := ../SFML/include
LIBRARIES := ../SFML/lib
LINKS := sfml-graphics \
         sfml-audio \
		 sfml-window \
		 sfml-system \
		 opengl32

# ==== PROJECT FILES ===========================================================
NAME := AI-UFOs
PATH_SRC := ./src/
PATH_OBJ := ./obj/
OBJS := main \
        tools \
		sfmltools \
		Graphics \
		Ufo \
		Flag \
		user \
		bot
ADD := icon64

# ==== APPLY SETUP =============================================================
OBJSO := $(addsuffix .o, $(OBJS))
OBJSF := $(addprefix $(PATH_OBJ), $(OBJSO))
ADDO := $(addsuffix .o, $(ADD))
ADDF := $(addprefix $(PATH_OBJ), $(ADDO))
INCLUDES := $(addprefix -I , $(INCLUDES))
LIBRARIES := $(addprefix -L , $(LIBRARIES))
LINKS := $(addprefix -l, $(LINKS))
LIBFLAGS := $(LINKS) $(LIBRARIES) $(INCLUDES)

# ==== PROCESS =================================================================
process: lazy \
	     builder
lazy: lazy_src \
	  lazy_usr

# ==== SUB-PROCESS =============================================================
lazy_src:
	lzz src/*.lzz -sx cc -hx hh -o src
lazy_usr:
	lzz *.AI -sx cc -hx hh -o src

builder: $(OBJSF)
	$(GNU) $(LFLAGS) -o $(NAME) $^ $(ADDF) $(LIBFLAGS) $(RFLAGS)

$(PATH_OBJ)%.o: $(PATH_SRC)%.cc
	$(GNU) $(LFLAGS) -o $@ -c $< $(LIBFLAGS) $(RFLAGS)
