<?hh // strict

namespace Application\Controllers;

class applicationController extends \Rime\ActionController\Controller\BaseController
{
  public function error($add_properties=[], $message="Forbidden"): void
  {
    $this->error = $message;
    foreach($add_properties as $key => $value)
    {
      $this->$key = $value;
    }
  }
}