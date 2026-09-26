import groovy.json.JsonSlurper

plugins {
  id("com.android.application")
}

// keep the app version in step with the engine's (package.json)
val pkg = JsonSlurper().parse(rootProject.file("../package.json")) as Map<*, *>
val engineVersion = pkg["version"] as String
val engineVersionCode = engineVersion.split(".").fold(0) { acc, part -> acc * 100 + part.toInt() }

android {
  namespace = "games.notnull.null0"
  compileSdk = 34
  ndkVersion = "27.2.12479018"

  defaultConfig {
    applicationId = "games.notnull.null0"
    minSdk = 24
    targetSdk = 34
    versionCode = engineVersionCode
    versionName = engineVersion

    ndk {
      // arm64 for devices, x86_64 for the emulator
      abiFilters += listOf("arm64-v8a", "x86_64")
    }

    externalNativeBuild {
      cmake {
        arguments += listOf("-DCMAKE_BUILD_TYPE=Release", "-DANDROID_STL=none")
        targets += "host"
      }
    }
  }

  // the host is the same CMake project the desktop and web builds use
  externalNativeBuild {
    cmake {
      path = file("../../CMakeLists.txt")
      version = "3.31.6"
    }
  }

  buildTypes {
    release {
      isMinifyEnabled = false
      // no release keystore in the repo: sign with the debug key so the apk
      // installs. swap this for a real signingConfig to publish
      signingConfig = signingConfigs.getByName("debug")
    }
  }

  compileOptions {
    sourceCompatibility = JavaVersion.VERSION_17
    targetCompatibility = JavaVersion.VERSION_17
  }
}
