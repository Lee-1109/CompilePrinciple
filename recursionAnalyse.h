/**
                 *                          编译原理实验二 递归下降分析法
                 * 18045221-李扬
                 * (1)<程序> ——> begin <语句串> end
                 * (2)<语句串> ——> <语句>{；<语句>} 说明： { }表示可选，即语句串可以只有一条语句，也可以有多个语句；语句之间用分号分隔。
                 * (3)<语句>——> <赋值语句> |<选择语句> | <循环语句>
                 * (4.1)<赋值语句>——> ID:＝<表达式>  说明：ID表示标识符
                 * (4.2)<选择语句>--> if ( 布尔 ) <语句> else <语句>
                 * (4.3)<循环语句>--> while(布尔) <语句>
                 * (5)  <表达式>——>  <项>｛＋<项> | —项>｝ 说明；{ }表示可选，即表达式可以只有一项，也可以有<项>＋<项> 或者<项>—<项>的形式。
                 * (6)<项>——> <因子>{*<因子> | /<因子>} 说明；{ }表示可选，即项可以只有一个因子，也可以有<因子>*<因子> 或者<因子>/<因子>的形式。
                 * (7)<因子>——> ID | NUM | (<表达式>)
                 * (8)<布尔> --> <表达式>  <  <表达式> | <表达式> <= <表达式> | <表达式> > <表达式> |  <表达式> >= <表达式>| <表达式>
                 *  S-->begin A end
                 *  A-->B|B;B
                 *  B->C1 | C2 |C3
                 *  C1--> ID := E
                 *  C2-->if ( H ) B else B
                 *  C3-->while ( H ) B
                 *  E-->F|F+F|F-F
                 *  F-->G|G*G|G/G
                 *  G-->ID|NUM|E
                 *  H--> E < E | E<=E | E > E | E >= E | E
                 *  产生式说明：
                 *  S 开始符号 A 语句串 B 语句 C 赋值语句 E 表达式  F项  G 因子  H 布尔表达式 ID 为自定义标识符
                 *  12.24 添加中间代码的生成
*/
#ifndef COMPILE_RECURSIONANALYSE
#define COMPILE_RECURSIONANALYSE
#include"lexical.h"
#endif
int i=0,flag=1;
void S();
void A();
void B();
void C1();
void C2();
void C3();
void E();
void F();
void G();
void H();//布尔表达式的产生式
void ERROR();
bool isID();
bool isNUM();
/**
 * 开始递归分析
 */
void doAnalyse(){
    S();
    if (flag==1){
        cout<<"SUCCESS:是文法给定的句子"<<endl;
    } else
        cout<<"ERROR:不是文法给定的句子"<<endl;
}
//   S-->begin A end
void S(){
    if (lexical[i].type=33){
        i++;
        A();
        i++;
        if(lexical[i].type==34){//是END 后读判断是否是#标志
            i++;
            if(lexical[i].value!="#") ERROR();//不是是文法给定的句
        }else ERROR();
    }else ERROR();
}
//A-->B|B;B
void A(){
    B();
    i++;//后移一位判断是否是';'号
    if(lexical[i].value==";"){
        i++;
        B();
    }
    else i--;//后退一位
}
//B-->C1 | C2 | C3
//  (4.1)C1  <赋值语句>——> ID:＝<表达式>  说明：ID表示标识符
//* (4.2) C2 <选择语句>--> if ( 布尔 ) <语句> else <语句> #NEW
//* (4.3) C3 <循环语句>--> while(布尔) <语句> #NEW
void B(){
    if(isID())
        C1();
    else if(lexical[i].value=="if")
        C2();
    else if(lexical[i].value=="while")
        C3();
    else ERROR();//不是文法给定的句子
}
//C1--> ID := E
void C1(){
    if(isID()){
        i++;
        if(lexical[i].value==":="){
            i++;
            E();
        } else ERROR();
    } else ERROR();//表示语法出错
}

//C2-->if ( H ) B else B
void C2(){
    if(lexical[i].value=="if"){
        i++;
        if(lexical[i].value=="("){
            i++;
            H();
            i++;
            if(lexical[i].value==")"){
                i++;
                B();
                i++;
                if(lexical[i].value=="else"){
                    i++;
                    B();
                }
                else ERROR();//语法出错
            }else ERROR();
        }else ERROR();
    }else ERROR();
}
// C3-->while ( H ) B
void C3(){
    if(lexical[i].value=="while"){
        i++;
        if(lexical[i].value=="("){
            i++;
            H();
            i++;
            if(lexical[i].value==")"){
                i++;
                B();
            }else ERROR();
        }else ERROR();
    } else ERROR();
}

// *  E-->F|F+F|F-F
void E(){
    F();
    i++;
    if(lexical[i].value=="+" ||lexical[i].value=="-"){
        i++;
        F();
    } else i--;
}
// *  F-->G|G*G|G/G
void F(){
    G();
    i++;//向后读取一位 判断是否符合文法
    if(lexical[i].value=="*" ||lexical[i].value=="/"){
        i++;
        G();
    } else i--;//回退
}
// *  G-->ID|NUM|E
void G(){
    if(isID() || isNUM() ){
        return;
    }
    else{
        E();
    }
}

//布尔表达式的产生式  *H-->E < E | E<=E | E > E | E>= E | E
void H(){
    E();
    i++;
    if(lexical[i].value=="<" || lexical[i].value=="<=" || lexical[i].value==">" ||lexical[i].value==">=" ){
        i++; E();
    }
}

/**
 * 表示错误 将错误标志置1
 * */
void ERROR(){
    flag=0;
}
/**
 * 判断是否是标识符
 * @return
 */
bool isID(){
    for(int j=0;j<Identifier_num;j++){
        if(lexical[i].value==IdentifierTable[j])
            return true;
    }
    return false;
}
/**
 * 判断是否是数字常量
 * @return
 */
bool isNUM(){
    for(int j=0;j<Digit_num;j++){
        if(lexical[i].value==DigitTable[j])
            return true;
    }
    return false;
}