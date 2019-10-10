package com.realxie.alita;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Surface;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ActivityCompat.requestPermissions(this,
                new String[]{Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.INTERNET}, PackageManager.PERMISSION_GRANTED);

        // init vulkan context
        VulkanSurfaceView surfaceView = findViewById(R.id.MainView);
        initVulkanContextJNI(surfaceView.surfaceHolder.getSurface());

        setAssetManagerJNI((Context)this, getApplication().getAssets());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public static native void initVulkanContextJNI(final Object surface);

    private static native void setAssetManagerJNI(final Context pContext, final AssetManager pAssetManager);

    public static native  void nativeRenderJNI(float dt);
}
