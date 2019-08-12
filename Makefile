CC:=g++
ifneq (,$(findstring Darwin,$(shell uname)))
	exist = $(shell if [ -e '/usr/local/bin/g++-9' ]; then echo "exist"; else echo "notexist"; fi;)
	ifeq ($(exist),exist)
		CC:=g++-9
	else
		CC:=g++-8
	endif
endif
OMPFLG=-fopenmp
HASHFLG=-Wno-deprecated
BUILDFLG=-w -ffunction-sections -fdata-sections -fmodulo-sched -msse
EXE_TAL=bin/MS-single-to-table
EXE_T2S=bin/MS-table-to-single
EXE_CMP=bin/MS-comp-taxa
EXE_CPD=bin/MS-comp-taxa-dynamic

tax:
	$(CC) -o $(EXE_TAL) src/taxa_sel.cpp $(HASHFLG) $(BUILDFLG) $(OMPFLG)
	$(CC) -o $(EXE_T2S) src/table2single.cpp $(HASHFLG) $(BUILDFLG) $(OMPFLG)
	$(CC) -o $(EXE_CMP) src/comp_sam.cpp $(HASHFLG) $(BUILDFLG) $(OMPFLG)
	$(CC) -o $(EXE_CPD) src/comp_sam_dynamic.cpp $(HASHFLG) $(BUILDFLG) $(OMPFLG)

clean:
	rm -rf bin/* src/*.o
