.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
PERF    = perf
######################################
# Project Name (generate executable with this name)
TARGET = cs296_exe_27

# Project Paths
PROJECT_ROOT := $(CURDIR)
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs
BINDIR = $(PROJECT_ROOT)/mybins
DOCDIR = $(PROJECT_ROOT)/doc
LIBDIR = $(PROJECT_ROOT)/mylib

EXTSRCDIR =$(EXTERNAL_ROOT)/src
EXTINCDIR =$(EXTERNAL_ROOT)/include
EXTLIBDIR = $(EXTERNAL_ROOT)/lib
# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL
STAT_TARGET=$(LIBDIR)/libCS296test.a
DYN_TARGET=$(LIBDIR)/libCS296test.so
SHAREDLIB = TRUE
# Compiler and Linker flags
CPPFLAGS =-g -p -O3 -Wall -fno-strict-aliasing -fPIC
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
CPPFLAGS1=-g -p -Wall -fno-strict-aliasing -fPIC
CPPFLAGS1+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
PLT := $(wildcard $(PROJECT_ROOT)/scripts/*.gpt)
GNU := $(wildcard $(PROJECT_ROOT)/scripts/*.gnu)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJP := $(filter-out $(OBJDIR)/main.o,$(OBJS))
OBJSHELP := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJPHELP := $(filter-out $(OBJDIR)/main.o,$(OBJSHELP))

.PHONY: all setup doc clean distclean data plot

all: setup exe exelib
setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p myobjs 
	@mkdir -p mybins 
	@mkdir -p mylib
	@if test -e ./external/src/Box2D/Box2D/Box2D.h ; \
	then echo "Installed already!"; \
	else cd "$(EXTSRCDIR)"; \
	tar xvzf Box2D.tgz; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296; \
	cmake ../; \
	make; \
	make install; \
	fi;

exe: $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) $(CPPFLAGS) -o $(BINDIR)/$(TARGET) -pg $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c  $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err
#---------------------------------------------------------------------------------------------------------------
exehelp: $(OBJSHELP)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) $(CPPFLAGS1) -o $(BINDIR)/$(TARGET) -pg $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

#-include -include $(OBJSHELP:.o=.d)

$(OBJSHELP): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS1) -c  $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err
#---------------------------------------------------------------------------------------------------------------
$(STAT_TARGET): $(OBJS)
	@if [[ "$(SHAREDLIB)" = "FALSE" ]]; \
	then ar -cvq $(LIBDIR)/libCS296test.a $(OBJP); \
	$(ECHO) "Static"; \
	fi;
	@$(ECHO) "Done"

$(DYN_TARGET): $(OBJS)
	@if [[ "$(SHAREDLIB)" = "TRUE" ]]; \
	#then  $(CC) -shared -Wl,-soname,$(CURDIR)/mylib/libCS296test.so -o $(CURDIR)/mylib/libCS296test.so $(OBJP) -lc; \
	then $(CC) -shared -Wl,-soname,$(CURDIR)/mylib/libCS296test.so -o $(CURDIR)/mylib/libCS296test.so $(OBJP) -lc; \
	$(ECHO) "Dynamic mode"; \
	fi;

exelib: $(DYN_TARGET) $(STAT_TARGET)
	@if [[ "$(SHARED_LIB)" = "TRUE" ]]; \
	then $(CC) -o $(BINDIR)/cs296_27_exelib $(LDFLAGS) -L $(EXTLIBDIR)/ $(OBJDIR)/main.o $(LIBDIR)/libCS296test.so $(LIBS); \
	else $(CC) -o $(BINDIR)/cs296_27_exelib $(LDFLAGS) -L $(LIBDIR)/ -L $(EXTLIBDIR)/ $(OBJDIR)/main.o -lCS296test $(LIBS); \
	fi;
doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	#@firefox doc/html/index.html
	@$(ECHO) "Done"

report:

	@$(ECHO) "Generating Report ...  "
	
	@cd ./doc; \
	latex cs296_report_27; \
	bibtex cs296_report_27; \
	latex cs296_report_27; \
	latex cs296_report_27; \
	dvipdf cs296_report_27.dvi cs296_report_27.pdf; \
	latex lab06; \
	bibtex lab06; \
	latex lab06; \
	latex lab06; \
	dvipdf lab06.dvi lab06.pdf;
	@$(ECHO) "Done"
data:
	@mkdir -p data
	@$(ECHO) "Generating data ...  "
	@cd scripts;\
	bash g27_gen_data.sh;\
	echo -n "Finished script 1.";\
	bash g27_gen_data_csv.sh;\
	echo -n "Finished script 2.";\
	bash g27_gen_csv.sh;\
	echo -n "Finished script 3.";\
	bash g27_gen_data_random.sh;\
	echo -n "Finished script 4.";
	@$(ECHO) "Done"
plot:
	@mkdir -p plots
	@$(ECHO) "Generating plots ...  "
	@cd scripts;\
	chmod +x $(PLT);\
	bash plot1.sh;\
	echo -n "Finished intializing.\n";\
	gnuplot> load "g27_plot01.gpt";\
	echo -n "Finished plot 1.\n";\
	gnuplot g27_plot02.gpt;\
	echo -n "Finished plot 2.\n";\
	gnuplot g27_plot03.gpt;\
	echo -n "Finished plot 3.\n";\
	gnuplot g27_plot04.gpt;\
	echo -n "Finished plot 4.\n";\
	gnuplot g27_plot05.gpt ;\
	echo -n "Finished plot 5.\n";\
	rm plot_loop.gnu plot_random.gnu plot_cumul.gnu plot_allvars.gnu plot_step.gnu;
	@$(ECHO) "Done"

release_prof: 
	@$(ECHO) "Compiling using debug mode..."
	@mkdir -p myobjs 
	@mkdir -p mybins 
	@mkdir -p mylib
	@if test -e ./external/src/Box2D/Box2D/Box2D.h ; \
	then cd "$(EXTSRCDIR)"; \
	cd Box2D; \
	cd build296; \
	cmake -DCMAKE_BUILD_TYPE=Release ../. ; \
	make; make install; \
	else cd "$(EXTSRCDIR)"; \
	tar xvzf Box2D.tgz; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296; \
	cmake -DCMAKE_BUILD_TYPE=Release ../. ; \
	make; \
	make install; \
	fi;
	@make exe;
	@$(ECHO) "Profiling"
	@ cd mybins; \
	#$(PERF) record ./$(TARGET) 10000; \
	#$(PERF) report > g27_debug_prof.dat; \
	#$(RM) -rf *.data *data.old; \
	./$(TARGET) 100000; \
	gprof $(TARGET) gmon.out > g27_release_prof.dat; \
	gprof $(TARGET) | .././gprof2dot.py | dot -Tpng -o release.png; \
	rm gmon.out;\
	cd ..;
	@$(ECHO) "Done"

debug_prof: 
	@$(ECHO) "Compiling using debug mode..."
	@mkdir -p myobjs 
	@mkdir -p mybins 
	@mkdir -p mylib
	@if test -e ./external/src/Box2D/Box2D/Box2D.h ; \
	then cd "$(EXTSRCDIR)"; \
	cd Box2D; \
	cd build296; \
	cmake -DCMAKE_BUILD_TYPE=Debug ../. ; \
	make; make install; \
	else cd "$(EXTSRCDIR)"; \
	tar xvzf Box2D.tgz; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296; \
	cmake -DCMAKE_BUILD_TYPE=Debug ../. ; \
	make; \
	make install; \
	fi;
	@make exehelp;
	@$(ECHO) "Profiling"
	@ cd mybins; \
	#$(PERF) record ./$(TARGET) 10000; \
	#$(PERF) report > g27_release_prof.dat; \
	#$(RM) -rf *.data *data.old; \
	./$(TARGET) 100000; \
	gprof $(TARGET) gmon.out > g27_debug_prof.dat; \
	gprof $(TARGET) | .././gprof2dot.py | dot -Tpng -o debug.png; \
	rm gmon.out;\
	cd ..;
	@$(ECHO) "Done"


clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) $(LIBDIR) $(BINDIR) *~ $(DEPS) $(SRCDIR)/*~ $(CURDIR)/*.pdf $(CURDIR)/*.dvi $(CURDIR)/*.aux
	@$(RM) -rf $(CURDIR)/doc/*.pdf $(CURDIR)/doc/*.dvi $(CURDIR)/doc/*.aux $(CURDIR)/doc/*.log
	@$(RM) -rf $(CURDIR)/doc/html
	@$(RM) -rf ./plots
	@$(RM) -rf ./data
	@$(RM) -rf load ./scripts/load ./scripts/fit.log
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(OBJDIR) $(LIBDIR) $(BINDIR)
	@$(RM) -rf ./external/include/*
	@$(RM) -rf ./external/lib/*
	@$(RM) -rf ./external/src/Box2D
	
	@$(ECHO) "Done"	