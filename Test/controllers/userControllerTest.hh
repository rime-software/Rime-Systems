<?hh // strict

require_once BASE_PATH.'/Test/traits/loginTrait.hh';

use \Application\Controllers\v1\userController as userController;
use \Application\Models\ApiKey                 as ApiKey;
use \Application\Models\Company                as Company;
use \Application\Models\BlowFish               as BlowFish;

class userControllerTest extends \PHPUnit_Framework_TestCase
{
  use loginTrait;
  
  protected ?userController $controller = null;

  public static function setUpBeforeClass(): void
  {
    
    Company::create([
      'name'   => 'Rime Test',
      'addr_1' => 'Nowhere',
      'city'   => 'New York',
      'state'  => 'NY'
    ]);
    
    $salt = BlowFish::generate_salt();
    
    ApiKey::create([
      'company_id' => Company::first()->id,
      'key'        => BlowFish::random_hash(),
      'salt'       => $salt,
      'secret'     => BlowFish::crypt_salted_string('password',$salt),
      'is_active'  => true
    ]);

  }
  
  public static function tearDownAfterClass(): void
  {
    Company::first()->delete();
    ApiKey::first()->delete();
  }
  
  protected function setUp(): void
  {
    $this->controller = new userController();
    $this->mock_valid_login_request();
  }
  
  public function test_current_user_action_session(): void
  {
    $this->controller->current_user();
    $this->assertTrue(
      $this->controller->current_user instanceof ApiKey
    );
  }
  
}