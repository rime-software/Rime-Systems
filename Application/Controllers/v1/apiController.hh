<?hh // strict

namespace Application\Controllers\v1;
use \Rime\ActionController\Controller\BaseController as Base;
use \Rime\System\Framework\Rime                      as Rime;
use \Application\Models\ApiKey                       as ApiKey;
use \Application\Models\BlowFish                     as BlowFish;

class apiController extends Base
{
  private mixed $Rime = null;
  
  static $before_filter = array(
    'require_login' => [
      'except' => ['index','login','unauthorized']
    ] 
  );
  
  public function __construct()
  {
    $this->Rime = Rime::getInstance();
    $this->respondTo( ($format) ==> {
      $format->json = true;
    });
  }
  
  public function index(): void
  {
    $this->version    = API_VERSION;
    $this->copyright  = COPY_RIGHT;
  }
  
  public function login(): void
  {
    $api_key = ApiKey::find_by_key(Rime::filter_post('key',FILTER_SANITIZE_STRING));

    if($api_key && $api_key->validate_secret(Rime::filter_post('secret')))
    {
      $session = $this->Rime->sessionFactory->newInstance($_COOKIE);
      $api_session = $session->getSegment('API\User');
      $api_session->set('key',$api_key->key);
      $api_session->set('session_id',$session->getId());
      $session->commit();
      
      $this->session_id = $api_session->get('session_id');
      $this->key        = $api_session->get('key');
      $this->last_login = $api_key->last_updated;
      $this->last_ip    = $api_key->ip_addr;
      
      $api_key->ip_addr = $_SERVER['REMOTE_ADDR'];
      $api_key->save();
    }
    else
    {
      $this->unauthorized();
    }
  }
  
  public function unauthorized(): void
  {
    $this->error = [
      'message' => 'A valid API Key and pass code must be provided to access this api.'
    ];
  }
  
  protected function require_login(): void
  {
    $this->require_login = true;
  }
  
}