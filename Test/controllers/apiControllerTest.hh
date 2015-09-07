<?hh // strict

require_once BASE_PATH.'/Test/traits/loginTrait.hh';

use \Application\Controllers\v1\apiController as apiController;
use \Application\Models\ApiKey                as ApiKey;
use \Application\Models\BlowFish              as BlowFish;
use \Application\Models\Company               as Company;

class apiControllerTest extends \PHPUnit_Framework_TestCase
{
  
  use loginTrait;
  
  protected ?apiController $controller = null;
  
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
    $this->controller = new apiController();
  }
  
  public function test_responds_only_to_json(): void
  {
    $this->assertTrue( $this->controller->canRespondTo('.json'),
      "apiController is unable to serve JSON responses by default."
    );
    $this->assertFalse( $this->controller->canRespondTo('.html'),
      "apiController must only serve JSON responses."
    );    
  }
  
  public function test_index_action_api_info(): void
  {
    $this->controller->index();
    $this->assertEquals( $this->controller->version, API_VERSION,
      "apiController#index does not provide the currently defined version in Config/Constants."
    );
    $this->assertEquals( $this->controller->copyright, COPY_RIGHT,
      "apiController#index does not provide the currently defined copyright in Config/Constants."
    );
  }
  
  public function test_before_filter_excluded_require_login_actions(): void
  {
    $this->assertEquals($this->controller->getFilter('Before')['require_login']['except'], ['index','login','unauthorized'],
      "apiController::before_filter.require_login should only contain 3 actions."
    );
  }
  
  public function test_unauthorized_action_creates_error_message(): void
  {
    $this->controller->unauthorized();
    $this->assertTrue(array_key_exists('message', $this->controller->error),
      "apiController#unauthorized does not create an error with index 'message.'"
    );
  }
  
  public function test_login_action_errors_with_invalid_credentials(): void
  {
    $this->mock_invalid_login_request(); 
    $this->assertTrue(array_key_exists('message', $this->controller->error),
      "apiController#login did not execute unauthorized action with invalid API credentials."
    );
  }
  
  public function test_login_action_registers_session(): void
  {
    $this->mock_valid_login_request();
    $this->assertEquals($_SESSION['API\User']['key'], ApiKey::first()->key,
      "apiController#login failed to register the API key in _SESSION.API\User.key."
    );
  }
  
  public function test_login_action_response(): void
  {
    $this->mock_valid_login_request();
    $this->assertTrue(is_string($this->controller->session_id),
      "apiController#login failed to respond with a session_id"
    );
    $this->assertEquals(ApiKey::first()->key, $this->controller->key,
      "apiController#login failed to respond with the proper ApiKey"
    );
    $this->assertEquals(ApiKey::first()->last_updated, $this->controller->last_login,
      "apiController#login failed to respond with the ApiKeys last_updated attribute"
    );
    $this->assertEquals(ApiKey::first()->ip_addr, $this->controller->last_ip,
      "apiController#login failed to respond with the ApiKeys last_ip attribute"
    );
  }
  
  public function test_login_action_updates_ip_addr(): void
  {
    $this->mock_valid_login_request();
    $this->assertEquals(ApiKey::first()->ip_addr,'fake_ip',
      "apiController#login failed to update the ApiKey last login ip "
    );
  }
  
  public function test_require_login_valid_session(): void
  {
    $this->mock_valid_login_request();
    $this->controller->require_login();
    $this->assertTrue(strlen($this->controller->csrf_token) == 128,
      "apiController#require_login failed to generate a valid csrf_token for valid session"
    );
  }
  
}