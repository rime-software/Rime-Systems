<?hh // strict

use \Application\Controllers\indexController as indexController;

class indexControllerTest extends \PHPUnit_Framework_TestCase
{
  protected ?indexController $controller = null;
  
  protected function setUp(): void
  {
    $this->controller = new indexController();
  }
  
  public function testIsPresent(): void
  {
    $this->assertTrue(!is_null($this->controller));
  }
  
  public function testHasIndexAction(): void
  {
    $this->assertTrue(method_exists($this->controller,'index'));
  }
}