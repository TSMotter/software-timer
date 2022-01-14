
// ref: https://www.jenkins.io/doc/book/pipeline/syntax/

/* 
  Environment variables provided by Jenkins server are listed at: 
  http://localhost:8080/env-vars.html/
*/

// DECLARATIVE PIPELINE
pipeline {
  agent any
  
  // User defined environment variables can be defined using this
  environment {
    // MY_VERSION is a user-defined env. var and BUILD_NUMBER is a Jenkins env. var
    MY_VERSION = "${BUILD_NUMBER}"
  }

  parameters {
    booleanParam(name: 'executeTests', defaultValue: true, description: 'Should execute tests?')
  }

  stages {

    stage("Build") {
      //  Run 'build' stage only when this expression is true
      when {
        expression {
          BRANCH_NAME == 'master'
        }
      }
      steps {
        echo "Building version: ${MY_VERSION}"
        sh 'rm -rf build'
        sh 'cmake -S . -B build -D TARGET_GROUP=release'
        sh 'cmake --build build -j 2'
      }
    }

    stage("UnityTest") {
      when {
        expression {
          params.executeTests
        }
      }
      steps {
        echo "Unity Testing"
        sh 'rm -rf build'
        sh 'cmake -S . -B build -D TARGET_GROUP=test'
        sh 'cmake --build build -j 2'
        sh 'make test -C ./build/ ARGS=\'-VV\''
      }
    }

    stage("StaticAnalysis") {
      steps {
        echo "Static analysis"
        sh 'cppcheck --enable=all --suppress=missingIncludeSystem .'
      }
    }
  }

  /*
    The post section defines one or more additional steps that are run 
    upon the completion of a Pipeline’s or stage’s run (depending on the 
    location of the post section within the Pipeline).
  */
  post {
    always {
      /* 
        This logic will always be executed after the
        previous *stages* block. Doesn't matter if it fails 
        of succeeds 
      */
      echo 'dummy \'post always\' block'
    }

    success {
      /*
        Only if previous *stages* block succeeds
      */
      echo 'dummy \'post success\' block'
    }

    failure {
      /*
        Only if previous *stages* block fails
      */
      echo 'dummy \'post failure\' block'
    }
  }
}