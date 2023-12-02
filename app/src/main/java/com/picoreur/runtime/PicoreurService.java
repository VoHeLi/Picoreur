package com.picoreur.runtime;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

import androidx.core.app.NotificationCompat;

import java.io.File;
import java.io.FileWriter;

public class PicoreurService extends Service {

    static {
        System.loadLibrary("runtime");
    }

    // Declare a native method sayHello() that receives no arguments and returns void
    private native void loadRuntimeJNI();

    private static final String CHANNEL_ID = "PicoreurCanal";

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        afficherNotification();
        loadRuntimeJNI();

        writeLoaderToApp();

        return START_STICKY;
    }

    public void writeLoaderToApp(){
        Log.d("PICOREUR", "Before writing...");
        String libDir = getApplicationInfo().nativeLibraryDir;
        String runtime_path = libDir + "/libruntime.so";

        String jsonData = "{\n\t\"file_format_version\": \"1.0.0\",\n\t\"runtime\": {\n\t\t\"name\": \"picoreur_runtime\",\n\t\t\"library_path\": \"" + runtime_path;
        jsonData += "\"\n\t}\n}";

        Log.d("PICOREUR", "Writing : \n" + jsonData);

        writeFileOnInternalStorage(getApplicationContext(), "picoreur_runtime.json", jsonData);
    }

    public void writeFileOnInternalStorage(Context mcoContext, String sFileName, String sBody){
        try {
            File gpxfile = new File("/storage/emulated/0", sFileName);
            FileWriter writer = new FileWriter(gpxfile);
            writer.append(sBody);
            writer.flush();
            writer.close();

            Log.d("PICOREUR", "Successfully wrote manifest file to : " + gpxfile.getAbsolutePath());
        } catch (Exception e){
            Log.e("PICOREUR", "Error when writing runtime manifest :" + e.toString());
        }
    }

    private void afficherNotification() {
        NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, "PicoreurCanal", NotificationManager.IMPORTANCE_DEFAULT);
            notificationManager.createNotificationChannel(channel);
        }

        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_launcher_foreground)
                .setContentTitle("Picoreur Runtime Service")
                .setContentText("Picoreur OpenXR Runtime Service for Standard Loader.")
                .setPriority(NotificationCompat.PRIORITY_DEFAULT);

        Notification notification = builder.build();
        startForeground(/*ID unique de la notification*/1, notification);
    }

    public String getNativeDir() {
        // Implementation
        return getApplicationContext().getApplicationInfo().nativeLibraryDir;
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d("PICOREUR", "Binding...");
        return null;
    }
}
