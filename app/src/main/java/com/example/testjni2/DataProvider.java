package com.example.testjni2;

public class DataProvider {
    //两数相加，处理完后，结果返回到Java层
    public native int add(int x, int y);
    //c层获取到s后，尾部+hello，结果返回到Java层
    public native String sayHelloInC(String s);
    //c层获取到int数组后，每个元素+10，结果返回到Java层
    public native int[] modifyIntArray(int[] arr);

}
