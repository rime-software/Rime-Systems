<?hh
  
use \Application\Controllers\v1\authController as authController;

class authControllerTest extends \PHPUnit_Framework_TestCase
{
  protected ?authController $controller = null;
  
  protected function setUp(): void
  {
    $this->controller = new authController();
  }
  
  public function testIsPresent(): void
  {
    $this->assertTrue(!is_null($this->controller));
  }
  
  public function testHasLoginAction(): void
  {
    $this->assertTrue(method_exists($this->controller,'login'));
  }
}