<?hh //strict
  
namespace Application\Controllers\v1;
use \Rime\ActionController\Controller\BaseController as Base;

class authController extends Base
{
  
  public function __construct()
  {
    $this->respondTo( ($format) ==> {
      $format->json = true;
    });
  }
  
  public function login(): void
  {
    
  }
}