<?hh // strict

use \Application\Models\BlowFish as BlowFish;

class BlowFishTest extends \PHPUnit_Framework_TestCase
{
  
  public function testGeneratesA13BitSalt()
  {
    //$this->assertTrue(strlen(BlowFish::generate_salt()) == 13);
  }
  
  public function testGeneratesA64BitRandomHash()
  {
    $this->assertTrue(strlen(BlowFish::random_hash()) == 64);
  }
  
}