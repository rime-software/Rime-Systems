<?hh // strict

use \Rime\ActionDispatch\Dispatcher as Dispatcher;

$router = (new Dispatcher\Factory\RouterFactory)->newInstance();

$router->addGet('home','/')->addValues(
	array(
		'controller'=>'index',
		'action'=>'index',
		'template'=>'master',
		'format'=>'.html'
	)
);

$router->addGet('test','/test')->addValues(
	array(
		'controller'=>'index',
		'action'=>'test',
		'template'=>'master',
		'format'=>'.html'
	)
);


//---------------------------
// V1 API
$router->setNamespace('v1','/api/v1',function($route){
  
  //---------------------------
  // User Routes
  
  $route->addValues(array(
    'controller' => 'user',
    'action'     => 'current_user'
  ));
  
  $route->addGet('current_user','/me');
  
  //---------------------------
  // Authentication / Index Controller
   
  $route->addValues(array(
    'controller' => 'api',
    'action'     => 'index'
  ));
  
  $route->add('api_info','');
  
  $route->add('gateway','/{action}')->addValues(
    array(
      'action' => 'login'
    )
  );
   
},['format'=>'.json']);