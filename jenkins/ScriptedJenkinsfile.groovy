
// ref: https://www.jenkins.io/doc/book/pipeline/syntax/

/* 
  Environment variables provided by Jenkins server are listed at: 
  http://localhost:8080/env-vars.html/
*/

// SCRIPTED PIPELINE
timestamps
{
  node ('master') 
  {
    try
    {
      checkout changelog: true, poll: true, scm: [
              $class           : 'GitSCM',
              branches         : [[name: '*/master']],
              userRemoteConfigs: [[credentialsId: '223a0d9a-70b6-4b80-8a5a-628f5fa22fe8', url: 'git@github.com:TSMotter/SoftwareTimer.git' ]]
      ]

      stage("Build") 
      {
        withEnv(["MY_VERSION=${env.BUILD_NUMBER}"])
        {
          echo "Building version: ${MY_VERSION}"
          sh 'rm -rf build'
          sh 'cmake -S . -B build -D TARGET_GROUP=release'
          sh 'cmake --build build -j 2'
        }
      }

      if (params.executeTests) 
      {
        stage("UnityTest") 
        {
          echo "Unity Testing"
          sh 'rm -rf build'
          sh 'cmake -S . -B build -D TARGET_GROUP=test'
          sh 'cmake --build build -j 2'
          sh 'make test -C ./build/ ARGS=\'-VV\''
        }
      }

      stage("StaticAnalysis") 
      {
        echo "Static analysis"
        sh 'cppcheck --enable=all --suppress=missingIncludeSystem .'
      }
    }
    catch (Exception e)
    {
      echo "Caught exception: ${e}";
    }
    finally
    {
      cleanWs()
      dir("${env.WORKSPACE}@tmp")
      {
        deleteDir()
      }
      dir("${env.WORKSPACE}@script")
      {
        deleteDir()
      }
    }
  }
}