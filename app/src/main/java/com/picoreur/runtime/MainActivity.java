package com.picoreur.runtime;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("runtime");
    }

    // Declare a native method sayHello() that receives no arguments and returns void
    private native void sayHello();

    public static Intent intent;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sayHello();

        // Démarrer le service
        /*intent = new Intent(this, PicoreurService.class);
        startService(intent);*/
        intent = new Intent(this, PicoreurService.class);
        //intent.setAction("org.khronos.openxr.OpenXRRuntimeService");
        startService(intent);


        finish();
    }


    /*public void test(){
        if (ContextCompat.checkSelfPermission(this, "android.permission.QUERY_ALL_PACKAGES") != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{"android.permission.QUERY_ALL_PACKAGES"}, PackageManager.PERMISSION_GRANTED);
        }
    }*/
}