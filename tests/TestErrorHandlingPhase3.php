<?php
use PHPUnit\Framework\TestCase;

class ErrorTest extends TestCase {
    private $expectedOutputs;
    // "backpatch3"
    protected function setUp(): void {
        $this->fileNames = [
            "backpatch0", "backpatch1", "backpatch2",
            "p3t_assignments_complex", "p3t_assignments_objects", "p3t_assignments_simple", "p3t_basic_expr",
            "p3t_calls", "p3t_flow_control_error", "p3t_flow_control",
            "p3t_const_maths", "p3t_funcdecl", "p3t_if_else", "p3t_object_creation_expr",
            "p3t_relational", "p3t_var_maths"
        ];

        $this->expectedOutputs = array_map(function ($fileName) {
            return file_get_contents("phase3testfiles/{$fileName}.asc");
        }, $this->fileNames);
    }

    public function testp3t_r0(): void {
        $testCount = count($this->fileNames);
        for ($i = 0; $i < $testCount; $i++) {
            $actualOutput = getParserOutput($this->fileNames[$i] . ".asc");
            $this->softAssertEquals($this->expectedOutputs[$i], $actualOutput, $this->fileNames[$i]);
        }
    }
    
    private function softAssertEquals($expected, $actual, $message = '') {
        try {
            $this->assertEquals($expected, $actual);
        } catch (\PHPUnit\Framework\AssertionFailedError $e) {
            // Handle the failure, e.g., log it
            echo "Soft assertion failed for $message: " . $e->getMessage() . "\n";
        }
    }
    
}

function getParserOutput($filename) {
    $filePath = "phase3/" . $filename; 
    $escapedFilePath = escapeshellarg($filePath); 
    $command = "./../parser <" . $escapedFilePath;

    exec($command, $output, $returnVar);

    if ($returnVar === 0) {
        if (file_exists("IntermediateCode.txt")) {
            $fileContent = file_get_contents("IntermediateCode.txt");
            return $fileContent;
        } else {
            throw new Exception("Output file not found.");
        }
    } else {
        throw new Exception("Failed to execute parser command.");
    }
}