#ifndef _SQF_BASE_H_
#define _SQF_BASE_H_

#ifndef __bool_true_false_are_defined
#error "SQF_base.h" requires stdbool header "stdbool.h"
#endif // !__bool_true_false_are_defined

#ifndef _BASETYPE_H_
#error "SQF_base.h" has to be included after "basetype.h"
#endif // !_BASETYPE_H_

#ifndef _WSTRING_MAP_H_
#error "SQF_base.h" has to be included after "wstring_map.h"
#endif // !_WSTRING_MAP_H_

//Structure containing VM instructions
typedef unsigned char DATA_TYPE;
#define INST_NOP ((DATA_TYPE)0)
#define INST_COMMAND ((DATA_TYPE)1)
#define INST_VALUE ((DATA_TYPE)2)
#define INST_LOAD_VAR ((DATA_TYPE)3)
#define INST_STORE_VAR ((DATA_TYPE)4)
#define INST_SCOPE ((DATA_TYPE)5)
#define INST_STORE_VAR_LOCAL ((DATA_TYPE)6)
#define INST_ARR_PUSH ((DATA_TYPE)7)
#define INST_CODE_LOAD ((DATA_TYPE)8)
#define INST_POP ((DATA_TYPE)9)
#define INST_POP_EVAL ((DATA_TYPE)10)
#define INST_CLEAR_WORK ((DATA_TYPE)11)
#define INST_DEBUG_INFO ((DATA_TYPE)12)
#define INST_MOVE ((DATA_TYPE)13)
#define INST_SCOPE_DROPOUT ((DATA_TYPE)14)
typedef struct INST
{
	DATA_TYPE type;
	BASE data;
} INST;
typedef INST* PINST;

//Structure containing VM Commands (eg. +, -, *, /)
struct CMD;
typedef void(*CMD_CB)(void*, const struct CMD* self);
typedef struct CMD
{
	char type;
	unsigned char type_code;
	CMD_CB callback;
	char precedence_level;
	wchar_t* name;
	unsigned int name_len;
	wchar_t* description;
	unsigned int description_len;
	wchar_t* usage;
	unsigned int usage_len;
	wchar_t* examples;
	unsigned int examples_len;
} CMD;
typedef CMD* PCMD;
typedef const CMD* CPCMD;

//Basic instruction stack
typedef struct STACK
{
	PINST* data;
	unsigned int size;
	unsigned int top;
	bool allow_dbg;
} STACK;
typedef STACK* PSTACK;

typedef struct CMDCNT
{
	wsm_list* types;
	wsm_list* nullar;
	wsm_list* unary;
	wsm_list* binary;
} CMDCNT;
typedef CMDCNT* PCMDCNT;
//Structure containing all VM related informations
#define SQFVM_SCRIPTS_GROWTH 10
struct SCRIPT;
typedef struct SCRIPT* PSCRIPT;
typedef struct VM
{
	PSTACK stack;
	PSTACK work;

	PSCRIPT* scripts;
	unsigned int scripts_top;
	unsigned int scripts_size;

	PCMDCNT cmd_container;
	void(*error)(struct VM* vm, const wchar_t*, PSTACK);
	void(*warn)(struct VM* vm, const wchar_t*, PSTACK);
	unsigned char die_flag;
	unsigned long max_instructions;
	unsigned long instcount;
	unsigned char enable_instruction_limit;
	unsigned char is_suspending_environment;
	int(*print)(struct VM* vm, const wchar_t* format, ...);
	void* print_custom_data;

	unsigned char** sidemap;
	wsm_list* groupmap;
} VM;
typedef VM* PVM;

//Simple value structure containing a type command
typedef struct VALUE
{
	CPCMD type;
	BASE val;
} VALUE;
typedef VALUE* PVALUE;

//Scope structure containing required scope informations
struct NAMESPACE;
typedef struct SCOPE
{
	wchar_t* name;
	unsigned int name_len;

	wchar_t** varstack_name;
	VALUE** varstack_value;
	unsigned int varstack_size;
	unsigned int varstack_top;
	struct NAMESPACE* ns;
}SCOPE;
typedef SCOPE* PSCOPE;

typedef struct POPEVAL
{
	unsigned int ammount;
	unsigned char popon;
}POPEVAL;
typedef POPEVAL* PPOPEVAL;

typedef struct DBGINF
{
	unsigned int line;
	unsigned int col;
	unsigned long offset;
	unsigned long length;
	wchar_t* hint;
}DBGINF;
typedef DBGINF* PDBGINF;
typedef struct MOVE
{
	unsigned int line;
	unsigned int col;
	unsigned long offset;
}MOVE;
typedef MOVE* PMOVE;

void cb_cmdcnt_destroy(void* data);
PCMDCNT create_cmdcnt(void);
void destroy_cmdcnt(PCMDCNT cmdcnt);

PCMDCNT GET_PCMDCNT(void);

PVM sqfvm(unsigned int stack_size, unsigned int work_size, bool allow_dbg, unsigned long max_instructions);
void sqfvm_pushscript(PVM vm, PSCRIPT script);
void sqfvm_dropscript(PVM vm, PSCRIPT script);
void destroy_sqfvm(PVM vm);
int sqfvm_print(PVM vm, const wchar_t* format, ...);

void orig_error(PVM vm, const wchar_t* errMsg, PSTACK stack);
void orig_warn(PVM vm, const wchar_t* errMsg, PSTACK stack);
PSTACK create_stack(unsigned int size, bool allow_dbg);
void destroy_stack(PSTACK stack);
void resize_stack(PVM vm, PSTACK stack, unsigned int newsize);
void push_stack(PVM vm, PSTACK stack, PINST inst);
PINST pop_stack(PVM vm, PSTACK stack);
void insert_stack(PVM vm, PSTACK stack, PINST inst, int offset);
PINST copy_inst(PVM vm, const PINST instIn);
void copy_into_stack(PVM vm, PSTACK target, const PSTACK source);

void register_command(PVM vm, PCMD cmd);
#endif
