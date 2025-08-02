#include <iostream>
#include <format>
#include <cstddef>

constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}





struct MyStruct1 {

    short d;       // 2 byte
    double c;      // 8 byte
    int b;         // 4 byte
    char a;        // 1 byte
    char e;        // 1 byte


};//24 byte


struct MyStruct2 {

	double c;      // 8 byte
    int b;         // 4 byte
    short d;       // 2 byte
    char a;        // 1 byte
    char e;        // 1 byte


};//16 byte



int main() {
    print( "Struct1 boyutu : {} byte\n", sizeof(MyStruct1));
    print( "Struct2 boyutu : {} byte\n", sizeof(MyStruct2));

    print( "Offset  a: {}  byte\n", offsetof(MyStruct2, a)) ;
    print( "Offset  b: {}  byte\n", offsetof(MyStruct2, b)) ;
    print( "Offset  c: {}  byte\n", offsetof(MyStruct2, c)) ;
    print( "Offset  d: {}  byte\n", offsetof(MyStruct2, d)) ;
    print( "Offset  e: {}  byte\n", offsetof(MyStruct2, e)) ;


    MyStruct1 array1[2048];
    MyStruct2 array2[2048];
    print( "Struct1 array boyutu : {} Kb\n", sizeof(array1)/1024u);
    print( "Struct2 array boyutu : {} Kb\n", sizeof(array2)/1024u);








    return 0;
}

