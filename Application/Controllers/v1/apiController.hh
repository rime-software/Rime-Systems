<?hh // strict

namespace Application\Controllers\v1;
use \Application\Controllers\applicationController   as Base;
use \Rime\System\Framework\Rime                      as Rime;
use \Application\Models\ApiKey                       as ApiKey;

class apiController extends Base
{
  protected mixed $Rime = null;
  
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
  
  public function login(): bool
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
      return true;
    }
    else
    {
      $this->unauthorized();
    }
    return false;
  }
  
  public function logout(): void
  {
    $this->Rime->sessionFactory->newInstance($_COOKIE)->destroy();
    $this->redirect_to('/api/v1/index');
  }
  
  public function unauthorized(): void
  {
    $this->error = [
      'message' => 'A valid API Key and Secret must be provided to access this api.'
    ];
  }
  
  public function require_login(): void
  {
    $session = $this->Rime->sessionFactory->newInstance($_COOKIE);
    
    $api_session = $session->getSegment('API\User');
    if($api_session->get('session_id') && $api_session->get('key'))
    {
      $this->csrf_token = $session->getCsrfToken()->getValue();
    }
    else
    {
      $this->redirect_to('/api/v1/unauthorized',true,307);
    }
  }
  
}