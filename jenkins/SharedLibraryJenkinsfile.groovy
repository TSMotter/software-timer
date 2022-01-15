@Library('pipeline-library') _
import politie.jenkins.*

def builder = new JenkinsPipelineBootstrap().createBuilder()

boolean shouldRunTests = "${params.executeTests}"

echo "db1: params.executeTests: ${params.executeTests} // shouldRunTests: ${shouldRunTests}"

builder.sharedLibTestScriptedPipeline(executeTests: "${shouldRunTests}") 
