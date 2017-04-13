//  struct_inheritance.c

#include <stdio.h>
#include <stdlib.h>

//  父结构体
typedef struct struct1
{
    int value1;
    int value2;
} struct1;

//  子结构体
typedef struct struct2
{
    struct1 common;   //  第1个变量的数据类型必须是struct1
    int value3;
} struct2;

//  用struct1**作为参数类型
void process(struct1 **ps1)
{
    struct2 *ps2 = (struct2*) malloc(sizeof(*ps2));
    ps2->common.value1 = 20;
    ps2->common.value2 = 40;
    ps2->value3 = 60;  			//  设置了struct2.value3变量的值
*ps1 = (struct1*)ps2; 		//  这里的*ps1相当于指向struct2的指针
}
int main(int argc, char *argv[])
{
    struct2 *ps2;
    //  process函数的参数类型是struct1**，而这里使用强行转换传递了struct2**
    //  在process函数内部通过ps2返回了struct2.common的首地址，
//  根据这个首地址可以访问在struct2中定义的value3变量
    process((struct1**) &ps2);
    printf("struct1.value1=%d\nstruct2.value2=%d\nstruct1.value3=%d\n",
            ps2->common.value1, ps2->common.value2, ps2->value3);

    return 0;
}

