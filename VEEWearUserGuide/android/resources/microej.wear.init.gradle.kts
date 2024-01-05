settingsEvaluated {

   allprojects {
      repositories {
		google()
        mavenCentral()
      }
   }

   /**
    * Plugins repositories
    */
   pluginManagement {
      repositories {
		google()
        mavenCentral()
        gradlePluginPortal()
      }
   }
}
