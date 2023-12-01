package com.picoreur.runtime;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

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
}