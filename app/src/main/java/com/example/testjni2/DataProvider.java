package com.example.testjni2;

public class DataProvider {

    public native int add(int x,int y);
    public native String sayHelloInC(String s);
    public native int[] modifyIntArray(int[] arr);

}
