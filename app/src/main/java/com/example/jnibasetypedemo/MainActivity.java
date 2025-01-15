package com.example.jnibasetypedemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.jnibasetypedemo.databinding.ActivityMainBinding;

import java.util.Arrays;


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

        Animal[] animals = new Animal[30];
        for (int i = 0; i < 30; i++) {
            Animal ani = new Animal();
            ani.setName("animal name"+(i+1));
            animals[i]=ani;
        }
        getAnimalsNameFromJNI(animals);

        OneKeyVideoExport obj= getOneKeyVideoExportObjectFromJNI();
        System.out.println("===> percent:"+obj.percent +" mode:"+ obj.assaint_mode+" state:"+obj.assaint_state);
    }

    /**
     * A native method that is implemented by the 'jnibasetypedemo' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void CheckJNIBaseType();

    public native int JNIReadIntArrayData(int[] arrInt);

    public native int[] JNIGetIntArrayDate();



    public native boolean getBoolValueFromJNI();

    public native byte getByteValueFromJNI();

    public native char getCharValueFromJNI();

    public native short getShortValueFromJNI();

    public native int getIntValueFromJNI();

    public native long getLongValueFromJNI();

    public native float getFloatValueFromJNI();

    public native double getDoubleValueFromJNI();

    public native String getStringValueFromJNI();

    public native Object getObjectValueFromJNI();

    public native void getAnimalsNameFromJNI(Animal[] animals);

    public native OneKeyVideoExport getOneKeyVideoExportObjectFromJNI();


}