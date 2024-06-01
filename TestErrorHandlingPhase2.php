<?php
use PHPUnit\Framework\TestCase;

class ErrorTest extends TestCase {
    private $expectedOutputs;
    
    protected function setUp(): void {
        $this->expectedOutputs = [file_get_contents("test 2014/erro0.out"),file_get_contents("test 2014/erro1.out"),
        file_get_contents("test 2014/erro2.out"),file_get_contents("test 2014/erro3.out"),file_get_contents("test 2014/erro4.out"),
        file_get_contents("test 2014/erro5.out"),file_get_contents("test 2014/erro6.out"),file_get_contents("test 2014/erro7.out"),
        file_get_contents("test 2014/erro8.out"),file_get_contents("test 2014/erro9.out"),file_get_contents("test 2014/erro10.out"),
        file_get_contents("test 2014/erro11.out")];
    }

    public function testError0(): void {
        for ($i=0; $i < 12; $i++) { 
            $actualOutput = getParserOutput("Error".$i.".asc");  
            $this->assertEquals($this->expectedOutputs[$i], $actualOutput);
        }
    }
}

function getParserOutput($filename) {
    $command = "./parser <\"test 2014\"/" . escapeshellarg($filename);

    exec($command, $output, $returnVar);

    if ($returnVar === 0) {
        return implode("\n", $output); 
    } else {
        throw new Exception("Failed to execute parser command.");
    }
}
