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
      $this->validated = true; 
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