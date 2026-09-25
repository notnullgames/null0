package games.notnull.null0;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.OpenableColumns;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.RadioGroup;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// pick a cart to run, and the settings for running it. carts are copied into
// app storage (files/carts), so they show up here again next time
public class LauncherActivity extends Activity {
  private static final int REQUEST_OPEN = 1;
  private static final String PREF_CONTROLLER = "controller";
  private static final String PREF_PORTRAIT = "portrait";

  private SharedPreferences prefs;
  private ArrayAdapter<String> adapter;
  private final List<File> carts = new ArrayList<>();

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.launcher);
    prefs = getSharedPreferences("null0", MODE_PRIVATE);

    Switch controller = findViewById(R.id.controller);
    controller.setChecked(prefs.getBoolean(PREF_CONTROLLER, true));
    controller.setOnCheckedChangeListener((view, checked) -> prefs.edit().putBoolean(PREF_CONTROLLER, checked).apply());

    RadioGroup orientation = findViewById(R.id.orientation);
    orientation.check(prefs.getBoolean(PREF_PORTRAIT, false) ? R.id.portrait : R.id.landscape);
    orientation.setOnCheckedChangeListener((group, id) -> prefs.edit().putBoolean(PREF_PORTRAIT, id == R.id.portrait).apply());

    findViewById(R.id.open).setOnClickListener(view -> {
      Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT)
        .addCategory(Intent.CATEGORY_OPENABLE)
        .setType("*/*");
      startActivityForResult(intent, REQUEST_OPEN);
    });

    ListView list = findViewById(R.id.carts);
    list.setEmptyView(findViewById(R.id.empty));
    adapter = new ArrayAdapter<>(this, R.layout.cart_item);
    list.setAdapter(adapter);
    list.setOnItemClickListener((parent, view, position, id) -> play(carts.get(position)));
    list.setOnItemLongClickListener((parent, view, position, id) -> {
      confirmDelete(carts.get(position));
      return true;
    });

    handleIntent(getIntent());
  }

  @Override
  protected void onResume() {
    super.onResume();
    refresh();
  }

  @Override
  protected void onNewIntent(Intent intent) {
    super.onNewIntent(intent);
    handleIntent(intent);
  }

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    super.onActivityResult(requestCode, resultCode, data);
    if (requestCode == REQUEST_OPEN && resultCode == RESULT_OK && data != null && data.getData() != null) {
      importAndPlay(data.getData());
    }
  }

  // a .null0 opened from somewhere else (file manager, browser download)
  private void handleIntent(Intent intent) {
    if (intent != null && Intent.ACTION_VIEW.equals(intent.getAction()) && intent.getData() != null) {
      importAndPlay(intent.getData());
      // don't import it again on rotation/recreate
      setIntent(new Intent(this, LauncherActivity.class));
    }
  }

  private File cartDir() {
    File dir = new File(getFilesDir(), "carts");
    dir.mkdirs();
    return dir;
  }

  private void refresh() {
    File[] files = cartDir().listFiles();
    carts.clear();
    if (files != null) {
      carts.addAll(Arrays.asList(files));
    }
    // most recently played first
    carts.sort((a, b) -> Long.compare(b.lastModified(), a.lastModified()));
    adapter.clear();
    for (File cart : carts) {
      adapter.add(cartName(cart));
    }
  }

  private static String cartName(File cart) {
    String name = cart.getName();
    int dot = name.lastIndexOf('.');
    return dot > 0 ? name.substring(0, dot) : name;
  }

  private void play(File cart) {
    cart.setLastModified(System.currentTimeMillis());
    boolean controller = prefs.getBoolean(PREF_CONTROLLER, true);
    boolean portrait = prefs.getBoolean(PREF_PORTRAIT, false);
    startActivity(CartActivity.intent(this, cart.getAbsolutePath(), controller, portrait));
  }

  private void confirmDelete(File cart) {
    new AlertDialog.Builder(this)
      .setTitle(getString(R.string.delete_title, cartName(cart)))
      .setMessage(R.string.delete_message)
      .setPositiveButton(R.string.delete, (dialog, which) -> {
        cart.delete();
        refresh();
      })
      .setNegativeButton(android.R.string.cancel, null)
      .show();
  }

  // copy the cart into app storage (a content:// uri may not be readable
  // later, and the engine wants a plain file), then run it
  private void importAndPlay(Uri uri) {
    String name = safeName(displayName(uri));
    File dest = new File(cartDir(), name);
    new Thread(() -> {
      boolean ok = copy(uri, dest);
      runOnUiThread(() -> {
        if (ok) {
          refresh();
          play(dest);
        } else {
          dest.delete();
          Toast.makeText(this, getString(R.string.import_failed, name), Toast.LENGTH_LONG).show();
        }
      });
    }).start();
  }

  private boolean copy(Uri uri, File dest) {
    try (InputStream in = getContentResolver().openInputStream(uri);
         OutputStream out = new FileOutputStream(dest)) {
      if (in == null) {
        return false;
      }
      byte[] buf = new byte[64 * 1024];
      int n;
      while ((n = in.read(buf)) > 0) {
        out.write(buf, 0, n);
      }
      return true;
    } catch (Exception e) {
      return false;
    }
  }

  private String displayName(Uri uri) {
    if ("content".equals(uri.getScheme())) {
      try (Cursor c = getContentResolver().query(uri, new String[] {OpenableColumns.DISPLAY_NAME}, null, null, null)) {
        if (c != null && c.moveToFirst() && !c.isNull(0)) {
          return c.getString(0);
        }
      } catch (Exception e) {
        // fall through to the path
      }
    }
    String last = uri.getLastPathSegment();
    return last == null ? "cart" : last;
  }

  // the name picks the cart's save dir, so keep it a plain filename
  private static String safeName(String name) {
    name = name.substring(name.lastIndexOf('/') + 1).replaceAll("[^A-Za-z0-9._-]", "_");
    if (!name.endsWith(".null0") && !name.endsWith(".wasm")) {
      name = name + ".null0";
    }
    return name;
  }
}
