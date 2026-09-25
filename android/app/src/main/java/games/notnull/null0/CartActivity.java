package games.notnull.null0;

import android.app.NativeActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Process;
import android.view.View;
import android.view.Window;
import android.view.WindowInsets;
import android.view.WindowInsetsController;
import android.view.WindowManager;

// runs a cart: the engine (libnull0.so) is a NativeActivity, and android.c
// calls the getters below over JNI to find out what to run
public class CartActivity extends NativeActivity {
  static final String EXTRA_CART = "cart";
  static final String EXTRA_CONTROLLER = "controller";

  static Intent intent(Context context, String cartPath, boolean controller, boolean portrait) {
    Class<?> activity = portrait ? CartActivityPortrait.class : CartActivityLandscape.class;
    return new Intent(context, activity)
      .putExtra(EXTRA_CART, cartPath)
      .putExtra(EXTRA_CONTROLLER, controller);
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    // go fullscreen before the native window exists - raylib sizes itself
    // once, and doesn't handle the surface changing size later
    fullscreen();
    getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    super.onCreate(savedInstanceState);
  }

  @Override
  public void onWindowFocusChanged(boolean hasFocus) {
    super.onWindowFocusChanged(hasFocus);
    if (hasFocus) {
      fullscreen();
    }
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
    // the engine keeps its state in globals, so this process can't run a
    // second cart. it's a separate process (android:process=":cart"), so
    // just end it - the launcher is unaffected
    Process.killProcess(Process.myPid());
  }

  @SuppressWarnings("deprecation")
  private void fullscreen() {
    Window window = getWindow();
    // the insets controller hangs off the decor view, which doesn't exist yet
    // in onCreate unless asked for
    window.getDecorView();
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
      window.getAttributes().layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
    }
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
      window.setDecorFitsSystemWindows(false);
      WindowInsetsController controller = window.getInsetsController();
      if (controller != null) {
        controller.hide(WindowInsets.Type.systemBars());
        controller.setSystemBarsBehavior(WindowInsetsController.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE);
      }
    } else {
      // the LAYOUT_ flags keep the surface full-size whether the bars are
      // showing or not
      window.getDecorView().setSystemUiVisibility(
        View.SYSTEM_UI_FLAG_LAYOUT_STABLE
          | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
          | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
          | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
          | View.SYSTEM_UI_FLAG_FULLSCREEN
          | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }
  }

  // called from native (android.c)
  public String getCartPath() {
    return getIntent().getStringExtra(EXTRA_CART);
  }

  // called from native (android.c)
  public boolean getShowController() {
    return getIntent().getBooleanExtra(EXTRA_CONTROLLER, true);
  }
}
