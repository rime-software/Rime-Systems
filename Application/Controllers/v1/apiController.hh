<?hh // strict

namespace Application\Controllers\v1;
use \Rime\ActionController\Controller\BaseController as Base;
use \Rime\System\Framework\Rime                      as Rime;

class apiController extends Base
{
  
  private mixed $Rime = null;
  
  public function __construct()
  {
    $this->Rime = Rime::getInstance();
    $this->respondTo( ($format) ==> {
      $format->json = true;
    });
  }
  
  private function require_login(): void
  {
    
  }
  
}