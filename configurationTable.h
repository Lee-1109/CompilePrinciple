/**
 * 参数配置文件表
 */
#ifndef COMPILE_CONFIGURATIONTABLE_H
#define COMPILE_CONFIGURATIONTABLE_H
#endif
#ifndef IOSTREAM
#define IOSTREAM
#include"iostream"
#include"fstream"
#endif

#ifndef STRING
#define STRING
#include"string"
#include"cstdio"
#include"cstring"
#include"cstdlib"
#endif

#define KeyWord_MAX 34
#define ArithmeticOperator_MAX 5
#define RelationOperator_MAX 9
#define AssignmentOperator_MAX 2
#define BorderOperator_MAX  36
#define Identifier_Max    1000
#define Digit_Max 1000
using namespace std;
#ifndef STRUCT_NODE
#define STRUCT_NODE
typedef struct {
    int type;
    string value;
    string describe;
}node;
#endif

node lexical[100]; //词法分析器的分析结果
int Lexical_Num=0;  //词法分析器的结果数量
string word="";		//字符串,当前词
char ch;			//每次读进来的一个字符
int line=1;			//行数
int col=1;			//列数
bool isScan;        //文件是否在扫描
int type;			//单词的类型
int Identifier_num=0;//自定义标识符数
int Digit_num=0;    //数据表个数
/**
 * 标识符表
 */
char IdentifierTable[Identifier_Max][40] = {};

/**
 * 常数表
 */
char DigitTable[Digit_Max][40] = {};


/**
 * 关键字表
 * "if"11, "int"12, "for"13, "while"14 "do"15, "return"16, "break"17, "continue"18, "else"19, "float"20
 */
static char KeyWord[KeyWord_MAX][20] = {
        "main", "case", "char", "const", "long",
        "default", "extern", "double", "register", "enum",
        "if","int", "for","while" , "do",
        "return","break","continue","else", "float",
        "short", "signed", "sizeof","static","struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "goto","begin","end"
};

/**
 * 算术运算符表
 */
static char ArithmeticOperator[ArithmeticOperator_MAX][4] = {
        "+", "-", "*", "/","++"
};
/**
 * 关系运算符表
 * 4:运算符 "="45, ">"46, "<"47, ">="48, "<="49, "!="50, "&&"51, "||"52,"=="54
 */
static char RelationOperator[RelationOperator_MAX][4] = {
        ">","<", ">=","<=","!=",
        "&&","||","==","<>"

};
/**
 * 赋值运算符表
 */
static char  AssignmentOperator[AssignmentOperator_MAX][4]={
        "=",":="
};
/**
 * 界符表
 * ','61, ';'62, '{'63, '}'64, '('65, ')'66
 */
static char BorderOperator[BorderOperator_MAX][4] = {
        ",", ";", "{", "}", "(", ")","^", "#", "[", "]", "."
};