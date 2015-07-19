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
  
  $route->addPost('authorize','/login')->addValues(
    array(
      'controller' => 'auth',
      'action'     => 'login'
    )
  );
  
  $route->addValues(array(
    'controller'=>'test',
    'action'=>'index'
  ));
  
  $route->addGet('test','/test');
   
},['format'=>'.json']);