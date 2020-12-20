/**
 * 编译原理实验一 词法分析实验
 * 18045221-李扬
 */
#ifndef COMPILE_MORPHOLOGY_H
#define COMPILE_MORPHOLOGY_H
#include "configurationTable.h"
#endif
/**
 * 判断是否是数字
 * @param ch
 * @return
 */
bool isLetter(char var){
    if(var>='a'&& var<='z' || var>='A'&&var<='Z')
        return true;
    else
        return false;
}
/**
 * 判断是否是数字
 * @param var
 * @return
 */
bool isDigit(char var){
    if(var >= '0' && var <= '9')
        return true;
    else
        return false;
}
/**
 * 判断是否是算数运算符
 * @param var
 * @return
 */
bool isArithmeticOperator(char var){
    for(int i=0;i<ArithmeticOperator_MAX;i++){
        if(var == ArithmeticOperator[i][0])
            return true;
    }
    return false;
}
/**
 * 判断是否是关系运算符
 * @return
 */
bool isRelationOperator(char var){
    for(int i=0;i<RelationOperator_MAX;i++){
        if(var==RelationOperator[i][0])
            return true;
    }
    return false;
}
/**
 * 判断是否是赋值运算符
 * @param var
 * @return
 */
bool isAssignmentOperator(char var){
    for(int i=0;i<AssignmentOperator_MAX;i++){
        if(var==AssignmentOperator[i][0])
            return true;
    }
    return false;
}
/**
 * 判断是否是界符
 * @param var
 * @return
 */
bool isBorder(char var){
    for(int i=0;i<BorderOperator_MAX;i++){
        if (var == BorderOperator[i][0])
            return true;
    }
    return false;
}
/**
 * 判断是否是空白
 * @param var
 * @return
 */
bool isSpace(char var){
    if (var == ' ')
        return true;
    else
        return false;
}
/**
 * 判断是否是换行
 * @param var
 * @return
 */
bool isEnter(char var){
    if(var == '\n')
        return true;
    else
        return false;
}
/**
 * 判断是否是下划线
 * @param var
 * @return
 */
bool isUnderLine(char var){
    if (var=='_')
        return true;
    return false;
}
/**
 * 将字符加入待检查字中
 * @param var
 */
void addWord(char var){
    word+=var;
    col++;
}
/**
 * 扫描下一个符号
 */
void movePointer(FILE *fp){
    fseek(fp,-1,SEEK_CUR);
}
/**
 * 读取下一个
 */
void moveAfter(){
    col++;
}
/**
 * 扫描下一行
 */
void nextLine(){
    col=1;
    line++;
}


/**
 * 扫描单词
 * @param fp
 * @return
 */
int Scan(FILE *fp){
    ch=fgetc(fp);
    if(feof(fp)){
        isScan= false;
        return 0;
    }
    /**是空格 后移一位*/
    else if(isSpace(ch)){
        moveAfter();
        return 0;
    }
    /**是换行 执行换行*/
    else if(isEnter(ch)){
        nextLine();
        return 0;
    }
    /** 字母下划线开头 不是关键字就是标识符*/
    else if(isLetter(ch) || isUnderLine(ch)){
       addWord(ch);
       while( (ch=fgetc(fp)) && ( isLetter(ch) || isDigit(ch) || isUnderLine(ch)) ){
           addWord(ch);
       }
       /** 查关键字 匹配返回关键字标识号 从1-100*/
       for(int i=0;i<KeyWord_MAX;i++){
           if (word==KeyWord[i])
               return i+1;
       }
       /** 不是关键字 那就是标识符 将自定义标识符标号1000-2000*/
       //查自定义标识符表
       for(int i=0;i<Identifier_num;i++){
           if(Identifier_num!=0 && !strcmp(IdentifierTable[i],word.c_str())){
               movePointer(fp);
               return 1000+i+1;
           }
       }
       //表中无 就加入标识符表
       strcpy(IdentifierTable[Identifier_num],word.c_str());
       Identifier_num++;
        return 1000+Identifier_num;
   }
   /** 数字常量  返回值type大于等于2000*/
    else if(isDigit(ch)){
        addWord(ch);
        while ((ch=fgetc(fp)) && isDigit(ch)){
            addWord(ch);
        }
        //查数字常量表
        for(int i=0;i<Digit_num;i++){
            if(i!=0 && !strcmp( DigitTable[i],word.c_str() ) ){
                movePointer(fp);
                return 2000+i;
            }
        }
        //表中无 就加入常量表
        strcpy(DigitTable[Digit_num],word.c_str());
        Digit_num++;
        return 2000+Digit_num;
    }
   /**算数运算符 返回类型100-200*/
   else if (isArithmeticOperator(ch)){
       addWord(ch);
        while ((ch=fgetc(fp))&& isArithmeticOperator(ch)){
            addWord(ch);
        }
        for(int i=0;i<ArithmeticOperator_MAX;i++){
            if(word==ArithmeticOperator[i])
                return 100+i;
        }
   }
   /**关系运算符 大于等于200 小于300*/
   else if(isRelationOperator(ch)){
        addWord(ch);
        while ((ch=fgetc(fp))&& isRelationOperator(ch)){
            addWord(ch);
        }
        for(int i=0;i<RelationOperator_MAX;i++){
            if(word==RelationOperator[i])
                return 200+i;
        }
   }
   /**赋值运算符300--400 */
   else if(isAssignmentOperator(ch)){
        addWord(ch);
        while ((ch=fgetc(fp)) && isAssignmentOperator(ch)){
            addWord(ch);
        }
        for(int i=0;i<AssignmentOperator_MAX;i++){
            if(word==AssignmentOperator[i])
                return 300+i;
        }
   }
   /**界符  大于等于400 小于1000*/
   else if (isBorder(ch)){
       addWord(ch);
       for(int i=0;i<BorderOperator_MAX;i++){
           if(word==BorderOperator[i])
               return 400+i;
       }
    }
   /** 错误符号 返回类型-1*/
   else return -1;
}
/**
 * 进行词法分析并保存结果
 */
void doLexical(){
    FILE *fp=fopen("code.txt","r");
    if(fp==NULL)
        cout<<"文件未打开"<<endl;
    else{
        //文件开始扫描
        cout<<"开始词法分析"<<endl;
        isScan= true;
    }
    while (isScan){
        type=Scan(fp);
        if(type>=1000 && type<2000){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="自定义标识符";
            cout<<lexical[Lexical_Num].describe<<  lexical[Lexical_Num].type  <<  lexical[Lexical_Num].value  <<endl;
            Lexical_Num++;
            word.clear();
        } else if (type>=2000){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="数字常量";
            cout<<lexical[Lexical_Num].describe  <<  lexical[Lexical_Num].type  <<  lexical[Lexical_Num].value<<endl;
            Lexical_Num++;
            word.clear();
        }
        else if(type>=100 && type<200){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="算数运算符";
            cout<<lexical[Lexical_Num].describe  <<   lexical[Lexical_Num].type  <<     lexical[Lexical_Num].value<<endl;
            Lexical_Num++;
            word.clear();
        }
        else if(type>=200 && type<300){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="关系运算符";
            cout<<lexical[Lexical_Num].describe<<   lexical[Lexical_Num].type<<     lexical[Lexical_Num].value      <<endl;
            Lexical_Num++;
            word.clear();
        }
        else if(type>=300 && type<400){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="赋值运算符";
            cout<<lexical[Lexical_Num].describe<<       lexical[Lexical_Num].type<<     lexical[Lexical_Num].value<<endl;
            Lexical_Num++;
            word.clear();
        }
        else if (type>=400 && type<1000){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="界符";
            cout<<lexical[Lexical_Num].describe     <<       lexical[Lexical_Num].type<<        lexical[Lexical_Num].value      <<endl;
            Lexical_Num++;
            word.clear();
        }
        else if(type>0 && type<100){
            lexical[Lexical_Num].type=type;
            lexical[Lexical_Num].value=word;
            lexical[Lexical_Num].describe="关键字";
            cout<<lexical[Lexical_Num].describe <<  lexical[Lexical_Num].type   <<  lexical[Lexical_Num].value<<endl;
            Lexical_Num++;
            word.clear();
        }
        else if(type==-1){
            cout<<"ERROR,please check line"<<line<<" column:"<<col<<endl;
        }
    }
    if(!isScan){
       fclose(fp);
    }
}