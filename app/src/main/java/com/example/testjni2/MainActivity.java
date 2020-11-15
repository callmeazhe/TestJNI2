package com.example.testjni2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    DataProvider mDataPro;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mDataPro = new DataProvider();

    }

    public void click1(View view) {
        int result = mDataPro.add(5, 5);
        Toast.makeText(view.getContext(), "result   " + result, Toast.LENGTH_LONG).show();
    }

    public void click2(View view) {
        String result = mDataPro.sayHelloInC("aaaaaaaa");
        Toast.makeText(view.getContext(), "result   " + result, Toast.LENGTH_LONG).show();

    }

    public void click3(View view) {
        int[] arr = {1, 2, 3, 4, 5};
        mDataPro.modifyIntArray(arr);

        StringBuilder stringBuilder = new StringBuilder();

        for (int i : arr) {
            stringBuilder.append(i);
        }
        Toast.makeText(view.getContext(), "result   " + stringBuilder.toString(), Toast.LENGTH_LONG).show();

    }

}