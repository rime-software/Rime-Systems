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


$router->setNamespace('v1','/api/v1',function($route){
  
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