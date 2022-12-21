# Пути к файлам
INC := ./inc
OUT := ./out
SRC := ./src
UNIT := ./unit_tests

# Исходные файлы
SRCS = $(wildcard $(SRC)*.c)
UNIT_SRCS = $(wildcard $(UNIT)*.c)

# Общие объектные файлы
OBJS := $(OUT)/date.o $(OUT)/phone_number.o $(OUT)/contact.o $(OUT)/my_time.o $(OUT)/contacts.o $(OUT)/actions.o
UNIT_OBJS := $(OUT)/check_unit_date.o $(OUT)/check_unit_phone_number.o $(OUT)/check_unit_contact.o $(OUT)/check_unit_my_time.o $(OUT)/check_unit_contacts.o $(OUT)/check_unit_actions.o

# Компилятор
CC := gcc

# Опции компилятора
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
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

debug: CLAGS += -Og -ggdb
debug: app.exe

coverage: CFLAGS += --coverage 
coverage: func
coverage: 
	gcov $(SRC)/main.c

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
	$(RM) *.exe $(OUT)/* func_tests/scripts/*.txt *.txt *.gcov *.gcno *.gcda *.log