<?hh // strict

use \Application\Models\ApiKey                       as ApiKey;

trait loginTrait
{
  private function mock_invalid_login_request(): void
  {
    $_POST['key']    = ApiKey::first()->key;
    $_POST['secret'] = "invalid";
    
    $logged_in = $this->controller->login();
    
    $this->assertFalse($logged_in);
    
  }
  
  private function mock_valid_login_request(): void
  {
    $_POST['key']    = ApiKey::first()->key;
    $_POST['secret'] = "password";
    $_SESSION        = array();
    $_SERVER         = array();
    $_COOKIE         = array();
    
    $_SERVER['REMOTE_ADDR'] = "fake_ip";
    $this->controller->login();
  }
}