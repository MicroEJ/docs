settingsEvaluated {

   val userHome = System.getProperty("user.home")

   allprojects {
      repositories {
         /* Local Repository for Maven/Gradle modules */
         maven {
            name = "localRepository"
            url = uri("${userHome}/.microej/repository")
         }
         /* Local Repository for Ivy modules */
         ivy {
            name = "localRepositoryIvy"
            url = uri("${userHome}/.microej/repository")
            patternLayout {
               artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
               ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
               setM2compatible(true)
            }
         }
         /* MicroEJ Central repository for Maven/Gradle modules */
         maven {
             name = "microEJForgeCentral"
             url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
         }
         /* MicroEJ Developer repository for Maven/Gradle modules */
         maven {
             name = "microEJForgeDeveloper"
             url = uri("https://forge.microej.com/artifactory/microej-developer-repository-release")
         }
         /* MicroEJ SDK 6 repository for Maven/Gradle modules */
         maven {
             name = "microEJForgeSDK6"
             url = uri("https://forge.microej.com/artifactory/microej-sdk6-repository-release/")
         }
         /* MicroEJ Central repository for Ivy modules */
         ivy {
             name = "microEJForgeCentralIvy"
             url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
             patternLayout {
                 artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                 ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                 setM2compatible(true)
             }
         }
         /* MicroEJ Developer repository for Ivy modules */
         ivy {
             name = "microEJForgeDeveloperIvy"
             url = uri("https://forge.microej.com/artifactory/microej-developer-repository-release")
             patternLayout {
                 artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                 ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                 setM2compatible(true)
             }
         }
         /* MicroEJ SDK 6 repository for Ivy modules */
         ivy {
             name = "microEJForgeSDK6Ivy"
             url = uri("https://forge.microej.com/artifactory/microej-sdk6-repository-release/")
             patternLayout {
                 artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                 ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                 setM2compatible(true)
             }
         }
      }

      /**
       * Publish repositories
       */
      pluginManager.withPlugin("maven-publish") {
         configure<PublishingExtension> {
            repositories {
               maven {
                  name = "localRepository"
                  url = uri("${userHome}/.microej/repository")
               }
            }
         }
      }
   }


   /**
    * Plugins repositories
    */
   pluginManagement {
      repositories {
         /* MicroEJ Central repository for Maven/Gradle modules */
         maven {
             name = "microEJForgeCentral"
             url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
         }
         /* MicroEJ Developer repository for Maven/Gradle modules */
         maven {
             name = "microEJForgeDeveloper"
             url = uri("https://forge.microej.com/artifactory/microej-developer-repository-release")
         }
         /* MicroEJ SDK 6 repository for Maven/Gradle modules */
         maven {
             name = "microEJForgeSDK6"
             url = uri("https://forge.microej.com/artifactory/microej-sdk6-repository-release/")
         }
         /* MicroEJ Central repository for Ivy modules */
         ivy {
             name = "microEJForgeCentralIvy"
             url = uri("https://forge.microej.com/artifactory/microej-central-repository-release")
             patternLayout {
                 artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                 ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                 setM2compatible(true)
             }
         }
         /* MicroEJ Developer repository for Ivy modules */
         ivy {
             name = "microEJForgeDeveloperIvy"
             url = uri("https://forge.microej.com/artifactory/microej-developer-repository-release")
             patternLayout {
                 artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                 ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                 setM2compatible(true)
             }
         }
         /* MicroEJ SDK 6 repository for Ivy modules */
         ivy {
             name = "microEJForgeSDK6Ivy"
             url = uri("https://forge.microej.com/artifactory/microej-sdk6-repository-release/")
             patternLayout {
                 artifact("[organisation]/[module]/[revision]/[artifact]-[revision](-[classifier])(.[ext])")
                 ivy("[organisation]/[module]/[revision]/ivy-[revision].xml")
                 setM2compatible(true)
             }
         }
      }
   }
}
