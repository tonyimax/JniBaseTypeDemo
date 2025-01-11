package com.example.jnibasetypedemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.jnibasetypedemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jnibasetypedemo' library on application startup.
    static {
        System.loadLibrary("jnibasetypedemo");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
        CheckJNIBaseType();

        int[] ints = new int[]{1,2,3,4,5,6,7,8};
        int sum = JNIReadIntArrayData(ints);
        for (int x:JNIGetIntArrayDate()){
            System.out.println("===>get int val from JNI return IntArray： " +x);
        }
    }

    /**
     * A native method that is implemented by the 'jnibasetypedemo' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void CheckJNIBaseType();

    public native int JNIReadIntArrayData(int[] arrInt);

    public native int[] JNIGetIntArrayDate();
}