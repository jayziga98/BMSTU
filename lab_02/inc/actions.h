#ifndef __ACTIONS_H__

#define __ACTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"
#include "errors_actions.h"

#define FILENAME_LEN 40
#define DATE_LEN 20
#define PRINT_TIME_WIDTH 80
#define PRINT_MEM_WIDTH 60

int handle_action(int com, contacts_t *contacts, keys_t *keys);
void print_menu();
void print_abonent_help();
int exec_command1(contacts_t *contacts, keys_t *keys);
int exec_command2(contacts_t *contacts, keys_t *keys);
void exec_command3(contacts_t *contacts);
void exec_command4(contacts_t *contacts);
int exec_command5(contacts_t *contacts, keys_t *keys);
int exec_command6(contacts_t *contacts, keys_t *keys);
int exec_command7(contacts_t *contacts);
void exec_command8(keys_t *keys);
void exec_command9(keys_t *keys);
void exec_command10(keys_t *keys);
void exec_command11(keys_t *keys);
void exec_command12(contacts_t *contacts);
void exec_command13(contacts_t *contacts);
void exec_command14(contacts_t *contacts, keys_t *keys);
void exec_command15(contacts_t *contacts, keys_t *keys);
void exec_command16(contacts_t *contacts, keys_t *keys);
void exec_command17(contacts_t *contacts, keys_t *keys);
void exec_command18();

#endif // #ifndef __ACTIONS_H__