<?hh // strict

namespace Application\Controllers\v1;
use \Rime\System\Framework\Rime                      as Rime;
use \Application\Models\ApiKey                       as ApiKey;

class userController extends apiController
{
  public function current_user(): void
  {
    $session = $this->Rime->sessionFactory->newInstance($_COOKIE);
    try
    {
      $this->current_user = ApiKey::find_by_key(
        $session->getSegment('API\User')->get('key')
      );
    }
    catch(\Exception $e)
    {
      $this->error = [
        'code'             => 500,
        'message'          => 'Invalid user session', 
        'internal_message' => $e->getMessage()
      ];
    }
  }
}

