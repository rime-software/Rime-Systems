<?hh // strict

namespace Application\Controllers;

class indexController extends applicationController
{
  public function index()
  { 
    $this->greeting = "See me in Application/Views/index/index.hh!";
    
    $this->respondTo( ($format) ==> {
      $format->json = true;
      $format->xml = true;
      $format->html = 'index.index';
    });
  }
  
  public function test(): void
  {
    $this->respondTo( ($format) ==> {
      $format->html = true;
    });
  }
}