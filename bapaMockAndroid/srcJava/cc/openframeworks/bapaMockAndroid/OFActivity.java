package cc.openframeworks.bapaMockAndroid;

import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import cc.openframeworks.OFAndroid;


public class OFActivity extends cc.openframeworks.OFActivity{

    public static String ID = "id";

    private OFAndroid ofApp;
    private int id;

    private SensorManager mSensorManager = null;
    private SensorEventListener mSensorEventListener = null;

    private float[] mAccelerometerReading = null;
    private float[] mMagnetometerReading = null;
    private float mAzimuth;
    private float mPitch;
    private float mRoll;

    public static Intent createIntent(Context context, int id) {
        Intent intent = new Intent(context, OFActivity.class);
        intent.putExtra(ID, id);
        return intent;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        String packageName = getPackageName();

        id = getIntent().getIntExtra(ID, -1);

        ofApp = new OFAndroid(packageName,this);

        getWindow().getDecorView().setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
                        | View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
                        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);

        initSensor();
    }

    @Override
    public void onDetachedFromWindow() {
        // no-op
    }

    @Override
    protected void onResume() {
        super.onResume();
        ofApp.resume();
    }

    @Override
    protected void onStart() {
        super.onStart();

        mSensorManager.registerListener(
                mSensorEventListener,
                mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
                SensorManager.SENSOR_DELAY_UI
        );

        mSensorManager.registerListener(
                mSensorEventListener,
                mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),
                SensorManager.SENSOR_DELAY_UI
        );
    }

    @Override
    protected void onPause() {
        super.onPause();
        ofApp.pause();
    }

    @Override
    protected void onStop() {
        super.onStop();
        ofApp.stop();

        mSensorManager.unregisterListener(mSensorEventListener);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (OFAndroid.keyDown(keyCode, event)) {
            return true;
        } else {
            return super.onKeyDown(keyCode, event);
        }
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        if (OFAndroid.keyUp(keyCode, event)) {
            return true;
        } else {
            return super.onKeyUp(keyCode, event);
        }
    }

    // Menus
    // http://developer.android.com/guide/topics/ui/menus.html
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Create settings menu options from here, one by one or infalting an xml
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // This passes the menu option string to OF
        // you can add additional behavior from java modifying this method
        // but keep the call to OFAndroid so OF is notified of menu events

        if (OFAndroid.menuItemSelected(item.getItemId())){
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public boolean onPrepareOptionsMenu (Menu menu){
        // This method is called every time the menu is opened
        //  you can add or remove menu options from here
        return  super.onPrepareOptionsMenu(menu);
    }

    // This will be called from oF.
    public int getId() {
        return id;
    }

    // This will be called from oF.
    public float getAzimuth() {
        return mAzimuth;
    }

    private void initSensor() {
        mSensorManager = (SensorManager) getSystemService( Context.SENSOR_SERVICE );

        mSensorEventListener = new SensorEventListener() {
            @Override
            public void onSensorChanged (SensorEvent event) {
                switch (event.sensor.getType()) {
                    case Sensor.TYPE_ACCELEROMETER:
                        mAccelerometerReading = event.values.clone();
                        break;

                    case Sensor.TYPE_MAGNETIC_FIELD:
                        mMagnetometerReading = event.values.clone();
                        break;
                }

                if (mAccelerometerReading != null && mMagnetometerReading != null) {
                    // Get RotationMatrix
                    float[] inR = new float[9];
                    SensorManager.getRotationMatrix(
                            inR,
                            null,
                            mAccelerometerReading,
                            mMagnetometerReading
                    );

                    // Set world's coordinate system with device's one.
                    // See this article in detail.
                    // http://blogs.yahoo.co.jp/count_zero_blog/62278295.html
                    float[] outR = new float[9];
                    SensorManager.remapCoordinateSystem(
                            inR,
                            SensorManager.AXIS_X, SensorManager.AXIS_Z,
                            outR
                    );

                    // Get orientation.
                    float[] fAttitude = new float[3];
                    SensorManager.getOrientation(
                            outR,
                            fAttitude
                    );

                    mAzimuth = rad2deg(fAttitude[0]);
                    mPitch = rad2deg(fAttitude[1]);
                    mRoll = rad2deg(fAttitude[2]);

                    Log.d("sensor", "azimuth : " + mAzimuth + " , pitch : " + mPitch + ", roll : " + mRoll);
                }
            }

            @Override
            public void onAccuracyChanged (Sensor sensor, int accuracy) {
                // no-op
            }
        };
    }

    private float rad2deg(float rad) {
        return (float) (Math.toDegrees(rad) + 360) % 360;
    }
}
