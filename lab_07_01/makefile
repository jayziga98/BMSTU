# Пути к файлам
INC := ./inc
OUT := ./out
SRC := ./src
UNIT := ./unit_tests

# Создание папки объектных файлов
$(shell mkdir -p $(OUT))

# Исходные файлы
SRCS = $(wildcard $(SRC)*.c)
UNIT_SRCS = $(wildcard $(UNIT)*.c)

# Общие объектные файлы
OBJS := $(OUT)/binary_tree.o $(OUT)/arr_ints.o $(OUT)/actions.o $(OUT)/my_time.o $(OUT)/myrandom.o $(OUT)/scapegoat_tree.o $(OUT)/hash_table_open.o $(OUT)/list.o $(OUT)/prime.o

# Компилятор
CC := gcc

# Опции компилятора
CFLAGS := -I$(INC) -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
UNIT_FLAGS := $(shell pkg-config --cflags --libs check)
UNIT_LINKS := -lcheck -lm -lpthread

app.exe : $(OBJS) $(OUT)/main.o
	$(CC) $(CFLAGS) $^ -o $@

$(OUT)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.d : $(SRC)/%.c
	$(CC) $(CFLAGS) -M $< > $@

include $(SRCS: .c=.d)

unit_tests.exe : $(OBJS) $(UNIT_OBJS) $(OUT)/check_main.o 
	$(CC) $(CLFAGS) $(UNIT_FLAGS) $(UNIT_LINKS) $^ -o $@

$(OUT)/%.o : $(UNIT)/%.c
	$(CC) $(CFLAGS) $(UNIT_FLAGS) -c $< -o $@

%.d : $(UNIT)/%.c
	$(CC) $(CFLAGS) $(UNIT_FLAGS) -M $< > $@

include $(UNIT_SRCS: .c=.d)

.PHONY : clean check_scripts func unit clang valgrind coverage debug release

release: CFLAGS += -O2
release: app.exe

debug: CFLAGS += -Og -ggdb
debug: app.exe

coverage: CFLAGS += --coverage 
coverage: func
coverage: 
	gcov $(SRCS)

valgrind: export USE_VALGRIND = 5
valgrind: debug
valgrind: func

clang: CC := clang
clang: CFLAGS := -Weverything
clang: app.exe

unit: unit_tests.exe
	./unit_tests.exe

func: app.exe
	bash ./func_tests/scripts/func_tests.sh
	
check_scripts: 
	find ./func_tests/scripts/*.sh -exec "shellcheck" {} \;

clean : 
	$(RM) *.exe func_tests/scripts/*.txt *.gcov *.gcno *.gcda *.log
	$(RM) -r $(OUT)