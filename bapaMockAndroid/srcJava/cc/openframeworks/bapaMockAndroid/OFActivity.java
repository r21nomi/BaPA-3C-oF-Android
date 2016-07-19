package cc.openframeworks.bapaMockAndroid;

import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;

import cc.openframeworks.OFAndroid;


public class OFActivity extends cc.openframeworks.OFActivity{

    public static String ID = "id";

    private OFAndroid ofApp;
    private int id;
    private LocationManager locationManager;
    private Location location;

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
        locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
//        locationManager.requestLocationUpdates(
//                LocationManager.GPS_PROVIDER,
//                TimeUnit.SECONDS.toMillis(3),
//                10,
//                new LocationListener() {
//                    @Override
//                    public void onLocationChanged(Location location) {
//                        OFActivity.this.location = location;
//                    }
//
//                    @Override
//                    public void onStatusChanged(String provider, int status, Bundle extras) {
//
//                    }
//
//                    @Override
//                    public void onProviderEnabled(String provider) {
//
//                    }
//
//                    @Override
//                    public void onProviderDisabled(String provider) {
//
//                    }
//                });
    }

    @Override
    public void onDetachedFromWindow() {

    }

    @Override
    protected void onResume() {
        super.onResume();
        ofApp.resume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        ofApp.pause();
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
}
