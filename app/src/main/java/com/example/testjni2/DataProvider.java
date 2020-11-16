package com.example.testjni2;

public class DataProvider {

    //************Java 调 C***********************
    //两数相加，处理完后，结果返回到Java层
    public native int add(int x, int y);
    //c层获取到s后，尾部+hello，结果返回到Java层
    public native String sayHelloInC(String s);
    //c层获取到int数组后，每个元素+10，结果返回到Java层
    public native int[] modifyIntArray(int[] arr);

    //**************C 调 Java*********************
    public void helloFromJNI(){
        System.out.println("hello from java");
    }

    public int add2(int x,int y){
        System.out.println("add2    "+ (x+y));
        return x+y;
    }

    public void printString(String s){
        System.out.println("java   "+s);
    }

    public static void staticPrintString(String s){
        System.out.println("static java   "+s);
    }


    public native void callHelloFromJNI();
    public native void callAdd2(int x,int y);
    public native void callPrintString(String s);
    public native void callStaticPrintString();



}
